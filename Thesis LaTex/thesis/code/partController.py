from rclpy.node import Node
from std_msgs.msg import Float64MultiArray, Empty

import subprocess
import signal


class PartController(Node):
    def __init__(self, number) -> None:
        super().__init__("part_controller")
        self.part_number = number
        self.create_publishers()
        self.create_bridge()
        self.empty_msg = Empty()
        self.detach_part_end1()  # send detach end-effectors from parts
        self.detach_part_end2()  # send detach end-effectors from parts

    def create_publishers(self):
        """Create publishers to send commands to the part"""
        num = self.part_number
        # attach/detach PART to  END-EFFECTORS 1 and 2
        self.end1_attach_publisher = self.create_publisher(
            Empty, f"/attach_end1_part{num}", 10
        )
        self.end2_attach_publisher = self.create_publisher(
            Empty, f"/attach_end2_part{num}", 10
        )
        self.end1_detach_publisher = self.create_publisher(
            Empty, f"/detach_end1_part{num}", 10
        )
        self.end2_detach_publisher = self.create_publisher(
            Empty, f"/detach_end2_part{num}", 10
        )
        # attach/detach PART to BASE
        self.base_attach_publisher = self.create_publisher(
            Empty, f"/attach_part{num}_base", 10
        )
        self.base_detach_publisher = self.create_publisher(
            Empty, f"/detach_part{num}_base", 10
        )
        self.command_publisher = self.create_publisher(
            Float64MultiArray, f"/position_controller{num}/commands", 10
        )

    def attach_part_end1(self):
        """send command to a part to attach to end1"""
        self.end1_attach_publisher.publish(self.empty_msg)

    def detach_part_end1(self):
        """send command to a part to detach from end1"""
        self.end1_detach_publisher.publish(self.empty_msg)

    def attach_part_end2(self):
        """send command to a part to attach to end 2"""
        self.end2_attach_publisher.publish(self.empty_msg)

    def detach_part_end2(self):
        """send command to a part to detach from end2"""
        self.end2_detach_publisher.publish(self.empty_msg)

    def attach_part_base(self):
        """send command to a part to attach to end 1"""
        self.base_attach_publisher.publish(self.empty_msg)

    def detach_part_base(self):
        """send command to a part to attach to end 2"""
        self.base_detach_publisher.publish(self.empty_msg)

    def create_bridge(self):
        """Create ROS-Gazebo bridges to send commands"""
        num = self.part_number
        BRIDGE_RULES = [
            f"/attach_end1_part{num}@std_msgs/msg/Empty@gz.msgs.Empty",
            f"/detach_end1_part{num}@std_msgs/msg/Empty@gz.msgs.Empty",
            f"/attach_end2_part{num}@std_msgs/msg/Empty@gz.msgs.Empty",
            f"/detach_end2_part{num}@std_msgs/msg/Empty@gz.msgs.Empty",
            f"/attach_part{num}_base@std_msgs/msg/Empty@gz.msgs.Empty",
            f"/detach_part{num}_base@std_msgs/msg/Empty@gz.msgs.Empty",
            f"/model/part{num}/pose@geometry_msgs/msg/Pose@gz.msgs.Pose",
        ]
        argv = ["ros2", "run", "ros_gz_bridge", "parameter_bridge"]
        argv.extend(BRIDGE_RULES)

        self.get_logger().info(f"Starting ros_gz_bridge: {' '.join(argv)}")
        self.proc = subprocess.Popen(
            argv, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, bufsize=1
        )

    def destroy_node(self):
        """Destroy this Node with closing bridges"""
        try:
            if self.proc and self.proc.poll() is None:
                self.get_logger().info("Stopping ros_gz_bridge...")
                self.proc.send_signal(signal.SIGINT)
                try:
                    self.proc.wait(timeout=5)
                except subprocess.TimeoutExpired:
                    self.proc.kill()
        finally:
            super().destroy_node()
