import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray
import math
from gazebo_msgs.srv import SetLinkState
from gazebo_msgs.msg import LinkState

class RobotController(Node):
    def __init__(self):
        super().__init__('robot_controller')

        # Leg switcher 
        # TODO: CHECK THIS!
        
        self.client = self.create_client(SetLinkState, '/gazebo/set_link_state')
        while not self.client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Waiting for /gazebo/set_link_state service...')
        self.get_logger().info('Connected to /gazebo/set_link_state service')

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
            [0.0,   90,    45,    0,   -45,    -90,    0.0],  # Joint 2
            [0.0,   90,    45,    0,   -45,     -90,    0.0],  # Joint 3
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
                self.fix_leg_to_world("block0_fix", fixed=False)


    def fix_leg_to_world(self, leg_name, fixed):
        request = SetLinkState.Request()
        link_state = LinkState()
        link_state.link_name = leg_name

        if fixed:
            # Fix the leg by attaching it to the world with zero velocity
            link_state.pose.position.x = 0.0
            link_state.pose.position.y = 0.0
            link_state.pose.position.z = 0.0
            link_state.twist.linear.x = 0.0
            link_state.twist.linear.y = 0.0
            link_state.twist.linear.z = 0.0
        else:
            # Release the leg by enabling free movement
            link_state.pose.position.x = 0.0
            link_state.pose.position.y = 0.0
            link_state.pose.position.z = 1.0  # Example release position
            link_state.twist.linear.x = 0.1
            link_state.twist.linear.y = 0.1
            link_state.twist.linear.z = 0.1

        request.link_state = link_state

        future = self.client.call_async(request)
        rclpy.spin_until_future_complete(self, future)
        if future.result():
            self.get_logger().info(f'Successfully updated state for {leg_name}')
        else:
            self.get_logger().error(f'Failed to update state for {leg_name}')


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