from launch import LaunchDescription
from launch.actions import ExecuteProcess, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
import os
import xacro

def generate_launch_description():
    # Get the package share directory
    pkg_share = FindPackageShare(package='box_robot').find('box_robot')
    urdf_path = os.path.join(pkg_share, 'urdf', 'box_robot.urdf')
    
    # Robot state publisher node
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': Command(['xacro ', urdf_path])}]
    )

    # Gazebo launch
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            FindPackageShare('gazebo_ros').find('gazebo_ros'),
            '/launch/gazebo.launch.py'
        ])
    )

    # Spawn robot
    spawn_robot = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=[
            '-entity', 'box_robot',
            '-topic', 'robot_description'
        ],
        output='screen'
    )

    # Joint controller node
    joint_controller = Node(
        package='box_robot',
        executable='joint_controller',
        name='joint_controller',
        output='screen'
    )

    return LaunchDescription([
        robot_state_publisher,
        gazebo,
        spawn_robot,
        joint_controller
    ])
