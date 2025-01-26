import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray
import math

class RobotController(Node):
    def __init__(self):
        super().__init__('robot_controller')

        # Separate publishers for each joint controller
        self.command_publisher1 = self.create_publisher(
            Float64MultiArray,
            '/position_controller1/commands',
            10
        )
        self.command_publisher2 = self.create_publisher(
            Float64MultiArray,
            '/position_controller2/commands',
            10
        )

        # Timer to periodically send commands
        self.timer_period = 3  # seconds
        self.timer = self.create_timer(self.timer_period, self.timer_callback)

        # Separate command sequences for each joint
        self.command_sequences = [
            [0.0, 1.0, 0.5, 1.0, 2.0, 1.0, 0.0],  # Joint 1
            [0.0, 1.5, 1.5, -1.5, -1.5, 1.5, 0.0]  # Joint 2
        ]
        self.command_indices = [0] * len(self.command_sequences)

        self.get_logger().info("RobotController node has been started.")

    def timer_callback(self):
        # Publish commands for each joint separately
        for joint_index in range(len(self.command_sequences)):
            command = Float64MultiArray()
            command.data = [self.command_sequences[joint_index][self.command_indices[joint_index]]]

            # Publish to respective joint controller
            if joint_index == 0:
                self.command_publisher1.publish(command)
            else:
                self.command_publisher2.publish(command)

            self.get_logger().info(f"Published command for joint {joint_index+1}: {command.data}")

            # Update index for the next command
            self.command_indices[joint_index] += 1
            if self.command_indices[joint_index] >= len(self.command_sequences[joint_index]):
                self.command_indices[joint_index] = 0  # Loop back to the beginning


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