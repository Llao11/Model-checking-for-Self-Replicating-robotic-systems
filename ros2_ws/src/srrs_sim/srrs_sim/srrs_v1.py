import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64

class JointController(Node):
    def __init__(self):
        super().__init__('joint_controller')

        # Publisher to the joint command topic
        self.publisher = self.create_publisher(Float64, '/revolute_joint/command', 10)

        # Timer to send commands periodically
        self.timer = self.create_timer(0.1, self.publish_command)

        # Current joint position target
        self.target_position = 0.0

    def publish_command(self):
        # Example: oscillate joint position between -1 and 1 radian
        self.target_position += 0.1
        if self.target_position > 1.0:
            self.target_position = -1.0

        # Publish the target position
        msg = Float64()
        msg.data = self.target_position
        self.publisher.publish(msg)
        self.get_logger().info(f"Publishing target position: {self.target_position}")

def main(args=None):
    rclpy.init(args=args)
    node = JointController()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
