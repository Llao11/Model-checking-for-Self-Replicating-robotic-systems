import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray
import math


class RobotController(Node):
    def __init__(self):
        super().__init__("robot_controller")

        # Publisher to the position controller command topic
        self.command_publisher = self.create_publisher(
            Float64MultiArray, "/position_controller/commands", 10
        )

        # Timer to periodically send commands
        self.timer_period = 3  # seconds
        self.timer = self.create_timer(self.timer_period, self.timer_callback)

        # Example position sequence 180/pi
        self.command_sequences = [
            [0.0, 1.0, 0.5, 1.0, 2.0, 1.0, 0.0],  # Joint 1
            [0.0, 1.5, 1.5, -1.5, -1.5, 1.5, 0.0],  # Joint 2
        ]
        self.command_indices = [0] * len(self.command_sequences)

        self.get_logger().info("RobotController node has been started.")

    def timer_callback(self):
        # Get the next command for each joint
        command = Float64MultiArray()
        command.data = [
            self.command_sequences[joint_index][self.command_indices[joint_index]]
            for joint_index in range(len(self.command_sequences))
        ]

        # Publish the command
        self.command_publisher.publish(command)
        self.get_logger().info(f"Published command: {command.data}")

        # Update indices for the next commands
        for joint_index in range(len(self.command_sequences)):
            self.command_indices[joint_index] += 1
            if self.command_indices[joint_index] >= len(
                self.command_sequences[joint_index]
            ):
                # Loop back to the beginning
                self.command_indices[joint_index] = 0


def main(args=None):
    rclpy.init(args=args)
    controller_node = RobotController()

    try:
        rclpy.spin(controller_node)
    except KeyboardInterrupt:
        controller_node.get_logger().info("Shutting down TwoBlocksController node...")
    finally:
        controller_node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
