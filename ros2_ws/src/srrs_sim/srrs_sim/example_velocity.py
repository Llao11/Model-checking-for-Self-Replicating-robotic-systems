import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray
import time

class VelocityTestNode(Node):
    def __init__(self):
        super().__init__('velocity_test_node')

        self.publisher = self.create_publisher(Float64MultiArray, '/velocity_controller/commands', 10)
        self.get_logger().info('Node created')

        commands = Float64MultiArray()

        commands.data.append(0)
        self.publisher.publish(commands)
        time.sleep(2)

        commands.data[0] = 1
        self.publisher.publish(commands)
        time.sleep(4)

        commands.data[0] = -1
        self.publisher.publish(commands)
        time.sleep(1)

        commands.data[0] = 0
        self.publisher.publish(commands)
        time.sleep(1)

def main(args=None):
    rclpy.init(args=args)
    node = VelocityTestNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
