import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray
import math

class TwoBlocksController(Node):
    def __init__(self):
        super().__init__('two_blocks_controller')

        # Publisher to the position controller command topic
        self.command_publisher = self.create_publisher(
            Float64MultiArray,
            '/position_controller/commands',
            10
        )

        # Timer to periodically send commands
        self.timer_period = 2  # seconds
        self.timer = self.create_timer(self.timer_period, self.timer_callback)

        # Example position sequence 180/pi
        sequence = [0.0, 90.0, 180, 0, 90, 180, 0.0]
        self.command_sequence = [i*math.pi/180 for i in sequence]
        self.command_index = 0

        self.get_logger().info("TwoBlocksController node has been started.")

    def timer_callback(self):
        # Get the next position command from the sequence
        command = Float64MultiArray()
        command.data = [self.command_sequence[self.command_index]]

        # Publish the command
        self.command_publisher.publish(command)
        self.get_logger().info(f"Published command: {command.data[0]}")

        # Update the index for the next command
        self.command_index += 1
        if self.command_index >= len(self.command_sequence):
            self.command_index = 0  # Loop back to the beginning


def main(args=None):
    rclpy.init(args=args)
    controller_node = TwoBlocksController()

    try:
        rclpy.spin(controller_node)
    except KeyboardInterrupt:
        controller_node.get_logger().info("Shutting down TwoBlocksController node...")
    finally:
        controller_node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
