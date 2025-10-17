from rclpy.node import Node
import time
from .materialController import MaterialController
from .robotController import RobotController

# TODO: Change timer.sleep() in goto_XYZ() to checking with contact sensor
# TODO: Write separate class to search for parts around with camera


class SRRSController(Node):
    def __init__(self, sensorNode, robot_joint_names):
        super().__init__("simulation_controller")
        self.sensorNode = sensorNode
        self.robotController = RobotController(self.sensorNode, robot_joint_names)
        self.materialController = MaterialController(parts_num=3)
        self.parts = self.materialController.get_parts()

    # Low level robot control =============================================
    def goto_XYZ(self, x, y, z):
        self.robotController.goto_XYZ(x, y, z)

    def rotate_joints(self, command_sequences):
        self.robotController.rotate_joints(command_sequences)
        self.robotController.wait_movement_finish(command_sequences)

    # Fix to base  ==========================================================
    def get_fixed_end(self):
        return self.robotController.fixed_end

    def swap_fix_block(self):
        self.robotController.swap_fix_block()

    def fix_end1_base(self, **kwargs):
        self.robotController.fix_end1_base()
        if "gui" in kwargs:
            gui = kwargs.get("gui", None)
            try:
                gui.btn_fix1_base.config(bg="green")
                gui.btn_fix2_base.config(bg="white")
            except:
                self.get_logger().info("Published attach1 message.")
        time.sleep(0.3)

    def fix_end2_base(self, **kwargs):
        self.robotController.fix_end2_base()
        if "gui" in kwargs:
            gui = kwargs.get("gui", None)
            gui.btn_fix1_base.config(bg="white")
            gui.btn_fix2_base.config(bg="green")
        time.sleep(0.3)

    def free_end1_base(self):
        self.robotController.free_end1_base()

    def free_end2_base(self):
        self.robotController.free_end2_base()

    # Fix PARTS to END-EFFECTORS  ==========================================

    def fix_end1_part(self, part_num, **kwargs):
        part_index = part_num - 1
        self.parts[part_index].attach_part_end1()
        self.parts[part_index].detach_part_base()
        self.get_logger().info(f"Attach part {part_num} to block 1")
        if "gui" in kwargs:
            gui = kwargs.get("gui", None)
            gui.btn_fix1_obj.config(bg="red")
            gui.btn_free1_obj.config(bg="white")

    def fix_end2_part(self, part_num, **kwargs):
        part_index = part_num - 1
        self.parts[part_index].detach_part_base()
        self.parts[part_index].attach_part_end2()
        self.get_logger().info(f"Attach part {part_num} to block 1")
        if "gui" in kwargs:
            gui = kwargs.get("gui", None)
            gui.btn_fix1_obj.config(bg="red")
            gui.btn_free1_obj.config(bg="white")

    # FREE PARTS from  END-EFFECTORS ======================================

    def free_end1_part(self, part_num):
        part_index = part_num - 1
        self.parts[part_index].detach_part_end1()
        self.parts[part_index].attach_part_base()
        self.get_logger().info(f"Detached part {part_index} from robot end 1")

    def free_end2_part(self, part_num):
        part_index = part_num - 1
        self.parts[part_index].detach_part_end2()
        self.parts[part_index].attach_part_base()
        self.get_logger().info(f"Detached part {part_index} from robot end 2")

    def free_ends_all_parts(self, **kwargs):
        for part_controller in self.parts:
            part_controller.detach_part_end2()
            part_controller.detach_part_end1()
        self.get_logger().info("Detach all parts from robot end1 and end2")
        if "gui" in kwargs:
            gui = kwargs.get("gui", None)
            gui.btn_fix2_obj.config(bg="white")
            gui.btn_free2_obj.config(bg="green")
