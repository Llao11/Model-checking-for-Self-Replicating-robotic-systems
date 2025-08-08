from rclpy.node import Node
import rclpy
from std_msgs.msg import Float64MultiArray, Empty, String
from sensor_msgs.msg import JointState

# from std_msgs.msg import Float64MultiArray, Empty, String
# from sensor_msgs.msg import JointState
# from ros_gz_interfaces.msg import Contacts
# from ament_index_python.packages import get_package_share_directory
# from typing import List
from . import SRRScontrollerNode
from . import SRRSsensorsNode

# import math
# import time
# import numpy as np
# from rclpy.duration import Duration


class Assemble(Node):
    def __init__(self) -> None:
        super().__init__("Assemble")
        self.sensorNode = SRRSsensorsNode.SRRSsensorsNode()
        self.controllerNode = SRRScontrollerNode.SRRSController(self.sensorNode)
        self.create_publishers()

    def create_publishers(self):
        """
        publishers for attach and detach topics
        """

        self.attach_publisher_voxel = self.create_publisher(
            Empty, "/attach_link_voxel", 10
        )
        self.detach_publisher_voxel = self.create_publisher(
            Empty, "/detach_link_voxel", 10
        )
        self.attach_publisher1 = self.create_publisher(Empty, "/attach_link1", 10)
        self.detach_publisher1 = self.create_publisher(Empty, "/detach_link1", 10)
        self.attach_publisher2 = self.create_publisher(Empty, "/attach_link2", 10)
        self.detach_publisher2 = self.create_publisher(Empty, "/detach_link2", 10)

        self.attach1_publisher_obj1 = self.create_publisher(
            Empty, "/attach_link1_obj_1", 10
        )
        self.attach1_publisher_obj2 = self.create_publisher(
            Empty, "/attach_link1_obj_2", 10
        )
        self.attach1_publisher_obj3 = self.create_publisher(
            Empty, "/attach_link1_obj_3", 10
        )
        self.attach2_publisher_obj1 = self.create_publisher(
            Empty, "/attach_link2_obj_1", 10
        )
        self.attach2_publisher_obj2 = self.create_publisher(
            Empty, "/attach_link2_obj_2", 10
        )
        self.attach2_publisher_obj3 = self.create_publisher(
            Empty, "/attach_link2_obj_3", 10
        )

        self.detach1_publisher_objects = self.create_publisher(
            Empty, "/detach1_objects", 10
        )
        self.detach2_publisher_objects = self.create_publisher(
            Empty, "/detach2_objects", 10
        )

        # separate publishers for each joint controller
        self.command_publisher1 = self.create_publisher(
            Float64MultiArray, "/position_controller1/commands", 10
        )
        self.command_publisher2 = self.create_publisher(
            Float64MultiArray, "/position_controller2/commands", 10
        )
        self.command_publisher3 = self.create_publisher(
            Float64MultiArray, "/position_controller3/commands", 10
        )
        self.command_publisher4 = self.create_publisher(
            Float64MultiArray, "/position_controller4/commands", 10
        )
        self.command_publisher5 = self.create_publisher(
            Float64MultiArray, "/position_controller5/commands", 10
        )
        self.command_publishers = [
            self.command_publisher1,
            self.command_publisher2,
            self.command_publisher3,
            self.command_publisher4,
            self.command_publisher5,
        ]

    def start_assemble(self):
        # load assemble sequence
        # robot_type_sequence = ["block_base", "block_vert_rot", "block_hor_rot"]
        # for block_type in robot_type_sequence:
        #     # search nearest surrounding
        #     x, y, z = search_arround(block_type)
        #
        #     # move end-effector to grasp point
        #     self.controllerNodel.goto_XYZ(x, y, z)
        msg = Empty()
        self.controllerNode.fix_1_to_base()
        self.controllerNode.free_2_from_base()

        self.controllerNode.free_block2_from_obj()
        self.controllerNode.free_block2_from_obj()

        self.controllerNode.goto_XYZ(1, 3, 2)


def main(args=None):
    rclpy.init(args=args)
    assembleNode = Assemble()

    try:
        rclpy.spin(assembleNode)
    except KeyboardInterrupt:
        assembleNode.get_logger().info("Shutting down RobotController node...")
    finally:
        assembleNode.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
