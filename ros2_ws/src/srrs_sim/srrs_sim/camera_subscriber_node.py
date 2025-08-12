import queue
from rclpy.node import Node
from rclpy.qos import QoSPresetProfiles
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2


class Camera_process_node_gui(Node):
    def __init__(self, out_queue: queue.Queue, topic="/camera2/image"):
        super().__init__("tk_camera_subscriber")
        self.bridge = CvBridge()
        self.out_queue = out_queue
        qos = QoSPresetProfiles.SENSOR_DATA.value  # BEST_EFFORT, small depth
        self.sub = self.create_subscription(Image, topic, self.callback, qos)
        self.get_logger().info(f"Subscribed to {topic}")

    def callback(self, msg: Image):
        """Preprocess images and put it in Queue"""
        # Convert ROS -> OpenCV BGR
        frame_bgr = self.bridge.imgmsg_to_cv2(msg, desired_encoding="bgr8")
        # Convert BGR -> RGB for Pillow/Tk
        frame_rgb = cv2.cvtColor(frame_bgr, cv2.COLOR_BGR2RGB)
        # Non-blocking: try to keep only the latest frame in queue
        if self.out_queue.qsize() > 1:
            try:
                self.out_queue.get_nowait()
            except queue.Empty:
                pass

        # Non-blocking put; if a producer/consumer race fills it, just drop
        try:
            self.out_queue.put_nowait(frame_rgb)
        except queue.Full:
            pass
