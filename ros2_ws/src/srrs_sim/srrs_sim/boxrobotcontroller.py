#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import Bool
from gazebo_msgs.srv import SetJointProperties
from std_srvs.srv import Empty
import time

class JointController(Node):
    def __init__(self):
        super().__init__('joint_controller')
        
        # Create subscription for joint state control
        self.subscription = self.create_subscription(
            Bool,
            'set_joint_fixed',
            self.joint_state_callback,
            10)
            
        # Create client for Gazebo joint properties service
        self.joint_properties_client = self.create_client(
            SetJointProperties,
            '/gazebo/set_joint_properties')
            
        # Wait for Gazebo services
        while not self.joint_properties_client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Waiting for Gazebo services...')

    def joint_state_callback(self, msg):
        request = SetJointProperties.Request()
        request.joint_name = "controllable_joint"
        
        if msg.data:  # If True, make joint fixed
            self.get_logger().info('Setting joint to fixed')
            request.ode_joint_config.joint_type = "fixed"
        else:  # If False, make joint floating
            self.get_logger().info('Setting joint to floating')
            request.ode_joint_config.joint_type = "floating"
            
        # Send request to Gazebo
        future = self.joint_properties_client.call_async(request)
        future.add_done_callback(self.joint_properties_callback)

    def joint_properties_callback(self, future):
        try:
            response = future.result()
            self.get_logger().info('Joint property update successful')
        except Exception as e:
            self.get_logger().error(f'Service call failed: {str(e)}')

def main(args=None):
    rclpy.init(args=args)
    joint_controller = JointController()
    rclpy.spin(joint_controller)
    joint_controller.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
