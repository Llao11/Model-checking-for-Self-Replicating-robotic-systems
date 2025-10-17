from rclpy.node import Node
from std_msgs.msg import Float64MultiArray, Empty, String
import time
from .partController import PartController


class MaterialController(Node):
    def __init__(self, parts_num):
        super().__init__("material_controller")
        self.create_parts(parts_num)

    def create_parts(self, amount):
        self.parts = []
        for i in range(amount):
            part_controller = PartController(i + 1)
            self.parts.append(part_controller)

    def get_parts(self):
        return self.parts
