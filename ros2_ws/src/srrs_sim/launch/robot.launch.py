from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.actions import RegisterEventHandler, TimerAction
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import (
    Command,
    FindExecutable,
    LaunchConfiguration,
    PathJoinSubstitution,
)


from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.actions import LogInfo, ExecuteProcess
from launch.launch_context import LaunchContext


def generate_launch_description():
    # Launch Arguments
    use_sim_time = LaunchConfiguration("use_sim_time", default=True)

    # path to share sdf folder
    context = LaunchContext()
    sdf_path = PathJoinSubstitution([FindPackageShare("srrs_sim"), "sdf"]).perform(
        context
    )
    urdf_path = PathJoinSubstitution([FindPackageShare("srrs_sim"), "urdf"]).perform(
        context
    )

    # BRIDGE creation ==============================================================================================================

    bridge_config_path = PathJoinSubstitution(
        [
            FindPackageShare("srrs_sim"),
            "config",
            "bridge_config.yaml",
        ]
    )  # ros2 run ros_gz_bridge parameter_bridge   /attach_link@std_msgs/msg/Empty@gz.msgs.Empty   /detach_link@std_msgs/msg/Empty@gz.msgs.Empty

    bridge_node = Node(
        package="ros_gz_bridge",
        executable="parameter_bridge",
        parameters=[{"config_file": bridge_config_path}],
        output="screen",
    )

    bridge_clock = Node(
        package="ros_gz_bridge",
        executable="parameter_bridge",
        arguments=["/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock"],
        output="screen",
    )

    gui_control_node = Node(
        package="srrs_sim",
        executable="robot_controller_gui",
        # arguments=['/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock'],
        output="screen",
    )

    # ROBOT spawn ==============================================================================================================

    # Generate URDF via xacro
    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name="xacro")]),
            " ",
            PathJoinSubstitution([FindPackageShare("srrs_sim"), "urdf", "robot.xacro"]),
        ]
    )
    robot_description = {"robot_description": robot_description_content}
    robot_controllers = PathJoinSubstitution(
        [
            FindPackageShare("srrs_sim"),
            "config",
            "robot_controller.yaml",
        ]
    )
    node_robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="screen",
        parameters=[robot_description],
    )
    step = 0.134
    gz_spawn_robot = Node(
        package="ros_gz_sim",
        executable="create",
        output="screen",
        arguments=[
            "-topic",
            "robot_description",
            "-name",
            "robot",
            # '-x', '0.0', '-y', '0.0', '-z', f'{str(step)}',  # Set X, Y, Z coordinates
            "-x",
            f"{str(step * 4)}",
            "-y",
            f"{str(step * 4)}",
            "-z",
            "0.134",  # Set X, Y, Z coordinates
            # Set Yaw (rotation in radians)
            "-X",
            "0.0",
            "-Y",
            "0.0",
            "-Z",
            "0.0",
            "-allow_renaming",
            "false",
        ],
    )
    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["joint_state_broadcaster"],
    )
    position_controller_spawner1 = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "position_controller1",
            "--param-file",
            robot_controllers,
        ],
    )
    position_controller_spawner2 = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "position_controller2",
            "--param-file",
            robot_controllers,
        ],
    )
    position_controller_spawner3 = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "position_controller3",
            "--param-file",
            robot_controllers,
        ],
    )
    position_controller_spawner4 = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "position_controller4",
            "--param-file",
            robot_controllers,
        ],
    )
    position_controller_spawner5 = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "position_controller5",
            "--param-file",
            robot_controllers,
        ],
    )

    # BASE spawn ==============================================================================================================

    gz_spawn_base = Node(
        package="ros_gz_sim",
        executable="create",
        output="screen",
        arguments=[
            "-name",
            "base",
            # simple base plate:
            "-file",
            f"{sdf_path}/base.sdf",
            #
            # big base plate:
            # '-file', '/home/lao/Documents/Masterarbeit/git/SRRS_gazebo_sim/ros2_ws/install/srrs_sim/share/srrs_sim/sdf/base10x10.sdf',
            "-x",
            "0.0",
            "-y",
            "0.0",
            "-z",
            "0.0",  # Set X, Y, Z coordinates
            # Set Yaw (rotation in radians)
            "-X",
            "0.0",
            "-Y",
            "0.0",
            "-Z",
            "0.0",
            "-allow_renaming",
            "true",
        ],
    )

    # LAUNCH description create ==============================================================================================================

    LaunchDescriptionMain = LaunchDescription(
        [
            # Launch gazebo environment
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    [
                        PathJoinSubstitution(
                            [
                                FindPackageShare("ros_gz_sim"),
                                "launch",
                                "gz_sim.launch.py",
                            ]
                        )
                    ]
                ),
                # -r runs the simulation immediately, -v 3 sets the verbosity level.
                launch_arguments=[("gz_args", [f"-r -v 3 {sdf_path}/world.sdf"])],
            ),
            RegisterEventHandler(
                event_handler=OnProcessExit(
                    target_action=gz_spawn_base,
                    on_exit=[
                        TimerAction(
                            period=5.0,
                            actions=[
                                gz_spawn_robot,
                                # gz_spawn_parts,
                            ],
                        )
                    ],
                )
            ),
            RegisterEventHandler(
                event_handler=OnProcessExit(
                    target_action=gz_spawn_robot,
                    on_exit=[
                        TimerAction(
                            period=1.0,
                            actions=[
                                position_controller_spawner1,
                                position_controller_spawner2,
                                position_controller_spawner3,
                                position_controller_spawner4,
                                position_controller_spawner5,
                                joint_state_broadcaster_spawner,
                            ],
                        )
                    ],
                )
            ),
            gz_spawn_base,
            bridge_clock,
            node_robot_state_publisher,
            bridge_node,  # for attaching and detaching joints
            gui_control_node,
            # Launch Arguments
            DeclareLaunchArgument(
                "use_sim_time",
                default_value=use_sim_time,
                description="If true, use simulated clock",
            ),
            LogInfo(msg="some info"),
            # print robot sdf in Log output
            # LogInfo(msg=robot_description_content),
        ]
    )

    # PARTS SPAWN ==============================================================================================================
    # spawn parts locations:
    step = 0.134
    part_coordinates_int = [[5, 6, 1], [3, 6, 1], [5, 1, 1]]
    part_coordinates = [[elem * step for elem in row] for row in part_coordinates_int]
    bridge_topics = []
    part_xacro_path = PathJoinSubstitution(
        [FindPackageShare("srrs_sim"), "urdf", "part.xacro"]
    )
    # parent_model = "base"
    # parent_link = "base_link"
    for i, (x, y, z) in enumerate(part_coordinates):
        part_name = f"part{i + 1}"
        processed_urdf_path = f"temp_part{i + 1}.urdf"
        generate_part_urdf = ExecuteProcess(
            cmd=[
                "xacro",
                part_xacro_path,
                f"part_num:={i + 1}",
                # parent_model:={parent_model} parent_link:={
                # parent_link }",
                "-o",
                processed_urdf_path,
            ],
            shell=True,
        )
        gz_spawn_parts = Node(
            package="ros_gz_sim",
            executable="create",
            output="screen",
            arguments=[
                "-name",
                part_name,
                "-file",
                processed_urdf_path,
                # Set X, Y, Z coordinates
                "-x",
                str(x),
                "-y",
                str(y),
                "-z",
                str(z),  # Set Yaw (rotation in radians)
                "-X",
                "0.0",
                "-Y",
                "0.0",
                "-Z",
                "0.0",
                "-allow_renaming",
                "true",
            ],
        )
        # bridge topic to attach/detach of PARTS to END Blocks
        bridge_topics.append(
            f"/attach_link1_obj_{i + 1}@std_msgs/msg/Empty@gz.msgs.Empty"
        )
        bridge_topics.append(
            f"/detach_link1_obj_{i + 1}@std_msgs/msg/Empty@gz.msgs.Empty"
        )
        bridge_topics.append(
            f"/attach_link2_obj_{i + 1}@std_msgs/msg/Empty@gz.msgs.Empty"
        )
        bridge_topics.append(
            f"/detach_link2_obj_{i + 1}@std_msgs/msg/Empty@gz.msgs.Empty"
        )
        # bridge topic to send pose messages (COORDINATES)
        bridge_topics.append(
            f"/model/part{i + 1}/pose@geometry_msgs/msg/Pose@gz.msgs.Pose"
        )
        # bridge topic to attach/detach to a previous block (or base for the first one)
        # TODO: implement in control Node
        # bridge_topics.append(
        #     f"/attach_link_obj_obj{i + 1}@std_msgs/msg/Empty@gz.msgs.Empty"
        # )
        # bridge_topics.append(
        #     f"/detach_link_obj_obj{i + 1}@std_msgs/msg/Empty@gz.msgs.Empty"
        # )
        LaunchDescriptionMain.add_action(generate_part_urdf)
        LaunchDescriptionMain.add_action(
            RegisterEventHandler(
                event_handler=OnProcessExit(
                    target_action=generate_part_urdf,
                    on_exit=[
                        TimerAction(
                            period=0.5,
                            actions=[
                                gz_spawn_parts,
                            ],
                        )
                    ],
                )
            ),
        )
        # parent_model = part_name
        # parent_link = "part"

    gz_create__bridges = Node(
        package="ros_gz_bridge",
        executable="parameter_bridge",
        name="gz_ros_bridge",
        arguments=bridge_topics,
        # [
        # topic@ros_msg_type@gz_msg_type
        # bridge_topics,
        # Add more topic bridges as needed:
        # '/my_topic@std_msgs/msg/String@gz.msgs.StringMsg',
        # ],
        output="screen",
    )
    LaunchDescriptionMain.add_action(gz_create__bridges)

    # RETURN LaunchDescriptionMain ==============================================================================================================
    return LaunchDescriptionMain
