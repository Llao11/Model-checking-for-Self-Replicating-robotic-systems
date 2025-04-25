from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.actions import RegisterEventHandler,TimerAction
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PathJoinSubstitution

from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.actions import LogInfo
from launch.launch_context import LaunchContext

def generate_launch_description():
    # Launch Arguments
    use_sim_time = LaunchConfiguration('use_sim_time', default=True)

    # path to share sdf folder
    context = LaunchContext()
    sdf_path = PathJoinSubstitution([FindPackageShare("srrs_sim"), "sdf" ]).perform(context)

    # spawn parts locations:
    step = 0.134
    x = str(7 * step)
    y = str(7 * step)

    # Get URDF via xacro
    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name='xacro')]),
            ' ',
            PathJoinSubstitution(
                [FindPackageShare('srrs_sim'),
                 'urdf', 'robot.xacro']
            ),
        ]
    )
    
    robot_description = {'robot_description': robot_description_content} 
    
    robot_controllers = PathJoinSubstitution(
        [
            FindPackageShare('srrs_sim'),
            'config',
            'robot_controller.yaml',   
        ]
    )

    bridge_config_path = PathJoinSubstitution(
        [
            FindPackageShare('srrs_sim'),
            'config',
            'bridge_config.yaml',   
        ]
    )   # ros2 run ros_gz_bridge parameter_bridge   /attach_link@std_msgs/msg/Empty@gz.msgs.Empty   /detach_link@std_msgs/msg/Empty@gz.msgs.Empty 


    bridge_node = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        parameters=[{'config_file': bridge_config_path}],
        output='screen'
    )

    node_robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[robot_description]
    )

    gz_spawn_robot = Node(
        package='ros_gz_sim',
        executable='create',
        output='screen',
        arguments=[
            '-topic', 'robot_description',
            '-name', 'robot',
            '-x', '0.0', '-y', '0.0', '-z', '0.134',  # Set X, Y, Z coordinates
            '-X', '0.0','-Y', '0.0','-Z', '0.0',  # Set Yaw (rotation in radians)
            '-allow_renaming', 'true'
        ],
    )


    gz_spawn_parts = Node(
        package='ros_gz_sim',
        executable='create',
        output='screen',
        arguments=[
            '-name', 'voxel',
            # small base:
            # '-file', '/home/lao/Documents/Masterarbeit/git/SRRS_gazebo_sim/ros2_ws/install/srrs_sim/share/srrs_sim/sdf/base1x1.sdf',
            # 
            # big base:
            '-file', f'{sdf_path}/voxel.sdf',
            '-x', x, '-y', y, '-z', '0.134',  # Set X, Y, Z coordinates
            '-X', '0.0','-Y', '0.0','-Z', '0.0',  # Set Yaw (rotation in radians)
            '-allow_renaming', 'true'
        ]
    )

    gz_spawn_base = Node(
        package='ros_gz_sim',
        executable='create',
        output='screen',
        arguments=[
            '-name', 'base',
            # simple base plate:
            '-file', f'{sdf_path}/base.sdf',
            # 
            # big base plate:
            # '-file', '/home/lao/Documents/Masterarbeit/git/SRRS_gazebo_sim/ros2_ws/install/srrs_sim/share/srrs_sim/sdf/base10x10.sdf',
            '-x', '0.0', '-y', '0.0', '-z', '0.0',  # Set X, Y, Z coordinates
            '-X', '0.0','-Y', '0.0','-Z', '0.0',  # Set Yaw (rotation in radians)
            '-allow_renaming', 'true'
        ]
    )

    joint_state_broadcaster_spawner = Node(
        package='controller_manager',
        executable='spawner',
        arguments=['joint_state_broadcaster'],
    )
    position_controller_spawner1 = Node(
        package='controller_manager',
        executable='spawner',
        arguments=[
            'position_controller1',
            '--param-file',
            robot_controllers,
            ],
    )
    position_controller_spawner2 = Node(
        package='controller_manager',
        executable='spawner',
        arguments=[
            'position_controller2',
            '--param-file',
            robot_controllers,
            ],
    )
    position_controller_spawner3 = Node(
        package='controller_manager',
        executable='spawner',
        arguments=[
            'position_controller3',
            '--param-file',
            robot_controllers,
            ],
    )
    position_controller_spawner4 = Node(
        package='controller_manager',
        executable='spawner',
        arguments=[
            'position_controller4',
            '--param-file',
            robot_controllers,
            ],
    )
    position_controller_spawner5 = Node(
        package='controller_manager',
        executable='spawner',
        arguments=[
            'position_controller5',
            '--param-file',
            robot_controllers,
            ],
    )

    # Bridge
    bridge_clock = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        arguments=['/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock'],
        output='screen'
    )

    

    return LaunchDescription(
        [
        # Launch gazebo environment
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                [PathJoinSubstitution([FindPackageShare('ros_gz_sim'),
                                       'launch',
                                       'gz_sim.launch.py'])]),
            launch_arguments=[('gz_args',[f'-r -v 3 {sdf_path}/world.sdf'])] # -r runs the simulation immediately, -v 3 sets the verbosity level.
        ),    

        RegisterEventHandler(
                event_handler=OnProcessExit(
                    target_action=gz_spawn_base,
                    on_exit=[TimerAction(
                            period=5.0,
                            actions=[
                                gz_spawn_robot,
                                gz_spawn_parts]
                        )],
                )
            ),

        RegisterEventHandler(
                event_handler=OnProcessExit(
                    target_action=gz_spawn_robot,
                    on_exit=[TimerAction(
                            period=1.0,
                            actions=[
                                position_controller_spawner1,
                                position_controller_spawner2,
                                position_controller_spawner3,
                                position_controller_spawner4,
                                position_controller_spawner5,
                                joint_state_broadcaster_spawner,
                                ]
                        )],
                )
            ),

        gz_spawn_base,
        bridge_clock,
        node_robot_state_publisher,
        bridge_node, # for attaching and detaching joints
        
        # Launch Arguments
        DeclareLaunchArgument(
            'use_sim_time',
            default_value=use_sim_time,
            description='If true, use simulated clock'),

        
        LogInfo(msg="some info"),

        # print robot sdf in Log output
        # LogInfo(msg=robot_description_content),
    ])
