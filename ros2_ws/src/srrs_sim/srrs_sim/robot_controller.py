import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray
import math

from tf2_ros import Buffer, TransformListener

from moveit_msgs.msg import CollisionObject, AttachedCollisionObject,PlanningScene
from geometry_msgs.msg import Pose, Point, Quaternion
from shape_msgs.msg import SolidPrimitive
from tf2_ros import Buffer, TransformListener
from moveit_msgs.srv import GetPlanningScene
from std_msgs.msg import Header
import numpy as np


import sys

class RobotController(Node):
    def __init__(self):
        super().__init__('robot_controller')

        self.init_movit()


        # Separate publishers for each joint controller
        self.command_publisher1 = self.create_publisher(Float64MultiArray,'/position_controller1/commands',10)
        self.command_publisher2 = self.create_publisher(Float64MultiArray,'/position_controller2/commands',10)
        self.command_publisher3 = self.create_publisher(Float64MultiArray,'/position_controller3/commands',10)
        self.command_publisher4 = self.create_publisher(Float64MultiArray,'/position_controller4/commands',10)
        self.command_publisher5 = self.create_publisher(Float64MultiArray,'/position_controller5/commands',10)
        self.command_publishers = [self.command_publisher1,self.command_publisher2,self.command_publisher3,
                                   self.command_publisher4,self.command_publisher5]
                                   
        

        # Timer to periodically send commands
        self.timer_period = 3  # seconds
        self.timer = self.create_timer(self.timer_period, self.timer_callback)

        self.attach_box()
        self.attached = True

        # Separate command sequences for each joint
        self.command_sequences_deg = [
            [0.0,   90,    45,    0,   -45,    -90,    0.0],  # Joint 1
            [0.0,   45,    45,    0,   -45,    -90,    0.0],  # Joint 2
            [0.0,   45,    45,    0,   -45,     -90,    0.0],  # Joint 3
            [0.0,   90,    45,    0,   -45,    -90,    0.0],  # Joint 4
            [0.0,   90,    45,    0,   -45,     -90,    0.0],  # Joint 5
        ]
        self.command_sequences = [[element * math.pi/180.0 for element in sublist] for sublist in self.command_sequences_deg]
        
        self.command_sequences
        self.command_indices = [0] * len(self.command_sequences)

        self.get_logger().info("RobotController node has been started.")



        
    def timer_callback(self):
        # Publish commands for each joint separately
        for joint_index in range(len(self.command_sequences)):
            command = Float64MultiArray()
            command.data = [self.command_sequences[joint_index][self.command_indices[joint_index]]]
            
            # Publish to respective joint controller
            self.command_publishers[joint_index].publish(command)

            self.get_logger().info(f"Published command for joint {joint_index+1}: {command.data}")

            # Update index for the next command
            self.command_indices[joint_index] += 1
            if self.command_indices[joint_index] >= len(self.command_sequences[joint_index]):
                self.command_indices[joint_index] = 0  # Loop back to the beginning
                self.get_logger().info(f"Repeat sequence")
                self.send_request("world_to_base")

    

    def init_movit(self):

        # Create publisher for planning scene updates
        self.planning_scene_pub = self.create_publisher(
            PlanningScene,
            '/planning_scene',
            10
        )

        self.attached = False
        
        # Wait a bit before setting up the scene
        self.create_timer(2.0, self.setup_scene)
        self.get_logger().info('Box manipulator node initialized')


    def setup_scene(self):
        try:
            # Create planning scene message
            planning_scene = PlanningScene()
            planning_scene.is_diff = True

            # Create collision object for the target box
            voxel = CollisionObject()
            voxel.header.frame_id = "world"
            voxel.header.stamp = self.get_clock().now().to_msg()
            voxel.id = "voxel"
            
            # Define box dimensions
            box = SolidPrimitive()
            box.type = SolidPrimitive.BOX
            box.dimensions = [0.1, 0.1, 0.1]  # Size matches URDF
            
            # Set box pose
            pose = Pose()
            pose.position = Point(x=0.2, y=0.0, z=0.025)  # Position matches URDF
            pose.orientation = Quaternion(x=0.0, y=0.0, z=0.0, w=1.0)
            
            voxel.primitives = [box]
            voxel.primitive_poses = [pose]
            voxel.operation = CollisionObject.ADD

            # Add collision object to planning scene
            planning_scene.world.collision_objects = [voxel]

            # Publish planning scene update
            self.planning_scene_pub.publish(planning_scene)
            self.get_logger().info('Added target box to planning scene')

        except Exception as e:
            self.get_logger().error(f'Error setting up scene: {str(e)}')
            

    def attach_box(self):
        """Attach the target box to the end-effector"""

        try:

             # Create planning scene message
            planning_scene = PlanningScene()
            planning_scene.is_diff = True

            # Create attached collision object
            attached_object = AttachedCollisionObject()
            attached_object.object.header.frame_id = "world"
            attached_object.object.header.stamp = self.get_clock().now().to_msg()
            attached_object.object.id = "voxel"
            attached_object.link_name = "block14_fix"  # Replace with your end-effector link name
            attached_object.touch_links = ["block14_fix"]  # List of links that can touch the object
            
            # Define the box geometry
            box = SolidPrimitive()
            box.type = SolidPrimitive.BOX
            box.dimensions = [0.1, 0.1, 0.1]

            # Set box pose
            pose = Pose()
            pose.position = Point(x=0.2, y=0.0, z=0.025)
            pose.orientation = Quaternion(x=0.0, y=0.0, z=0.0, w=1.0)
            
            attached_object.object.primitives = [box]
            attached_object.object.primitive_poses = [pose]
            attached_object.object.operation = CollisionObject.ADD

            # Add attached object to planning scene
            planning_scene.robot_state.attached_collision_objects = [attached_object]
            
            # Publish planning scene update
            self.planning_scene_pub.publish(planning_scene)
            self.get_logger().info('Attached target box to end-effector')
            
        except Exception as e:
            self.get_logger().error(f'Error attaching box: {str(e)}')



    def detach_box(self):
        """Detach the target box"""
        
        try:

            # Create planning scene message
            planning_scene = PlanningScene()
            planning_scene.is_diff = True

            # Create detach message
            detach_object = AttachedCollisionObject()
        
            detach_object.object.id = "voxel"
            detach_object.object.operation = CollisionObject.REMOVE

            # Add to planning scene
            planning_scene.robot_state.attached_collision_objects = [detach_object]
            
            # Publish planning scene update
            self.planning_scene_pub.publish(planning_scene)
            self.get_logger().info('Detached target box')
            
            # Re-add the object to the scene
            self.setup_scene()
            
        except Exception as e:
            self.get_logger().error(f'Error detaching box: {str(e)}')
        

def main(args=None):
    rclpy.init(args=args)
    controller_node = RobotController()

    try:
        rclpy.spin(controller_node)
    except KeyboardInterrupt:
        controller_node.get_logger().info("Shutting down RobotController node...")
    finally:
        controller_node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()