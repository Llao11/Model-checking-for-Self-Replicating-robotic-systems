from attr import s
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray,Empty
import math
import json
from ament_index_python.packages import get_package_share_directory
import os


class RobotController(Node):
    def __init__(self):
        super().__init__('robot_controller_keyboard')
        self.create_publishers()
        [self.command_sequences_detachable, self.command_sequences_deg] = self.read_commands()

        # Timer to periodically send commands
        self.timer_period = 3  # seconds
        self.timer = self.create_timer(self.timer_period, self.step)
        
        self.command_sequences = [[element * math.pi/180.0 for element in sublist] for sublist in self.command_sequences_deg]
        self.step = 0

        self.get_logger().info("RobotController node has been started.")

    def read_commands(self):
        package_name = 'srrs_sim'
        share_directory = get_package_share_directory(package_name)
        json_file_path = os.path.join(share_directory, 'commands', 'algorithm1.json')
        with open(json_file_path, 'r') as json_file:
            data = json.load(json_file)
        attach_blocks = data['attach_blocks']
        joint_angles = data['joint_angles']
        return [attach_blocks, joint_angles]

    def create_publishers(self):
        # Publishers for attach and detach topics
        self.attach_publisher_voxel = self.create_publisher(Empty, '/attach_link_voxel', 10)
        self.detach_publisher_voxel = self.create_publisher(Empty, '/detach_link_voxel', 10)
        self.attach_publisher1 = self.create_publisher(Empty, '/attach_link1', 10)
        self.detach_publisher1 = self.create_publisher(Empty, '/detach_link1', 10)
        self.attach_publisher2 = self.create_publisher(Empty, '/attach_link2', 10)
        self.detach_publisher2 = self.create_publisher(Empty, '/detach_link2', 10)

        # Separate publishers for each joint controller
        self.command_publisher1 = self.create_publisher(Float64MultiArray,'/position_controller1/commands',10)
        self.command_publisher2 = self.create_publisher(Float64MultiArray,'/position_controller2/commands',10)
        self.command_publisher3 = self.create_publisher(Float64MultiArray,'/position_controller3/commands',10)
        self.command_publisher4 = self.create_publisher(Float64MultiArray,'/position_controller4/commands',10)
        self.command_publisher5 = self.create_publisher(Float64MultiArray,'/position_controller5/commands',10)
        self.command_publishers = [self.command_publisher1,self.command_publisher2,self.command_publisher3,
                                   self.command_publisher4,self.command_publisher5]

    def step(self):
        print(f"Step: {self.step}")
        self.fix_blocks()
        self.rotate_joins()

    def fix_blocks(self):
        msg = Empty()
        if self.command_sequences_detachable[self.step][0] == "a":
            self.attach_publisher1.publish(msg)
            self.get_logger().info("Published attach1 message.")
        elif self.command_sequences_detachable[self.step][0] == "d":
            self.detach_publisher1.publish(msg)
            self.get_logger().info("Published detach1 message.")
        
        if self.command_sequences_detachable[self.step][1] == "a":
            self.attach_publisher2.publish(msg)
            self.get_logger().info("Published attach2 message.")
        elif self.command_sequences_detachable[self.step][1] == "d":
            self.detach_publisher2.publish(msg)
            self.get_logger().info("Published detach2 message.")

    def rotate_joins(self):
        for joint_index in range(len(self.command_sequences[0])):
            command = Float64MultiArray()
            command.data = [self.command_sequences[self.step][joint_index]]

            # Publish to respective joint controller
            self.command_publishers[joint_index].publish(command)
            self.get_logger().info(f"Published command for joint {joint_index+1}: {command.data}")

        # Update index for the next command
        self.step += 1
        if self.step >= len(self.command_sequences):
            self.step = 0  # Loop back to the beginning
            self.get_logger().info(f"Repeat sequence")


    def attach(self):
        msg = Empty()
        self.attach_publisher_voxel.publish(msg)
        self.get_logger().info("Published attach message.")

    def detach(self):
        msg = Empty()
        self.detach_publisher_voxel.publish(msg)
        self.get_logger().info("Published detach message.")        


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