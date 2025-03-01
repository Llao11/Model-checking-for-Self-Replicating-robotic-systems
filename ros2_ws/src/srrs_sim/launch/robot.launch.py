# Copyright 2021 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.actions import RegisterEventHandler
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PathJoinSubstitution

from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.actions import LogInfo

def generate_launch_description():
    # Launch Arguments
    use_sim_time = LaunchConfiguration('use_sim_time', default=True)

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
    )


    # ROS-Ign bridge for service communication
    Node(
        package='ros_ign_bridge',
        executable='parameter_bridge',
        name='ignition_bridge',
        output='screen',
        parameters=[{
            'config': """
            [
                {
                    'ros_service_name': '/world/create_entity',
                    'ign_service_name': '/world/default/create',
                    'ros_service_type': 'ros_ign_interfaces/srv/SpawnEntity',
                    'ign_service_type': 'ignition.msgs.EntityFactory'
                },
                {
                    'ros_service_name': '/world/remove_entity',
                    'ign_service_name': '/world/default/remove',
                    'ros_service_type': 'ros_ign_interfaces/srv/DeleteEntity',
                    'ign_service_type': 'ignition.msgs.Entity'
                }
            ]
            """
        }]
    ),

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
            '-file', '/home/lao/Documents/Masterarbeit/git/SRRS_gazebo_sim/ros2_ws/install/srrs_sim/share/srrs_sim/sdf/voxel.sdf',
            '-x', '0.234', '-y', '0.234', '-z', '0.234',  # Set X, Y, Z coordinates
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
            # small base plate:
            # '-file', '/home/lao/Documents/Masterarbeit/git/SRRS_gazebo_sim/ros2_ws/install/srrs_sim/share/srrs_sim/sdf/voxel.sdf',
            # 
            # big base plate:
            '-file', '/home/lao/Documents/Masterarbeit/git/SRRS_gazebo_sim/ros2_ws/install/srrs_sim/share/srrs_sim/sdf/base10x10.sdf',
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

    world_path = PathJoinSubstitution([FindPackageShare("srrs_sim"), "sdf", "world1.sdf"])

    return LaunchDescription([
        # Launch gazebo environment
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                [PathJoinSubstitution([FindPackageShare('ros_gz_sim'),
                                       'launch',
                                       'gz_sim.launch.py'])]),
            launch_arguments=[('gz_args',['-r -v 3 /home/lao/Documents/Masterarbeit/git/SRRS_gazebo_sim/ros2_ws/install/srrs_sim/share/srrs_sim/sdf/world.sdf'])]
        ),
            
        # create the event so that joint_state_broadcaster_spawner started after the end of gz_spawn_robot process
        RegisterEventHandler(
            event_handler=OnProcessExit(
                target_action=gz_spawn_robot,
                on_exit=[joint_state_broadcaster_spawner],
            )
        ),
        position_controller_spawner1,
        position_controller_spawner2,
        position_controller_spawner3,
        position_controller_spawner4,
        position_controller_spawner5,
        bridge_clock,
        node_robot_state_publisher,
        # gz_spawn_base,
        gz_spawn_parts,
        gz_spawn_robot,
        
        # Launch Arguments
        DeclareLaunchArgument(
            'use_sim_time',
            default_value=use_sim_time,
            description='If true, use simulated clock'),
        LogInfo(msg="some info"),
    ])
