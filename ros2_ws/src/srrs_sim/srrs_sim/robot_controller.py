import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray
import math
from gazebo_msgs.srv import SetJointProperties
from gazebo_msgs.msg import ODEJointProperties

class RobotController(Node):
    def __init__(self):
        super().__init__('robot_controller')

        self.srv = self.create_service(SetJointProperties, 'change_joint', self.change_joint_callback)
        self.get_logger().info('Joint Modifier Service Ready')

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





    def change_joint_callback(self, request, response):
        # Modify joint properties here
        joint_properties = ODEJointProperties()
        # Since we're changing to a fixed joint, these properties are examples
        joint_properties.fudge_factor = [0.0]
        request.ode_joint_config = joint_properties
        
        response.success = True
        response.status_message = "Joint type changed to fixed"
        return response

    def send_request(self, joint_name):
        client = self.create_client(SetJointProperties, '/gazebo/set_joint_properties')
        while not client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Service not available, waiting again...')

        request = SetJointProperties.Request()
        request.joint_name = joint_name
        
        future = client.call_async(request)
        rclpy.spin_until_future_complete(self, future)
        
        if future.result() is not None:
            self.get_logger().info(f'Joint {joint_name} modified successfully')
        else:
            self.get_logger().info('Service call failed')



        
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