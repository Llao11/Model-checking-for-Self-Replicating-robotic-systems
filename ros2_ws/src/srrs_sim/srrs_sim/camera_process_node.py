import rclpy
from rclpy.node import Node
from rclpy.qos import QoSPresetProfiles
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2


class CameraProcessNode(Node):
    def __init__(self):
        super().__init__("camera_process_node")
        self.bridge = CvBridge()
        topic = "/camera1/image"
        qos = QoSPresetProfiles.SENSOR_DATA.value  # best_effort + small depth
        self.sub = self.create_subscription(Image, topic, self.callback, qos)
        self.get_logger().info(f"Subscribed to {topic}")

    def callback(self, msg: Image):
        # Convert to OpenCV image (BGR)
        frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding="bgr8")
        # ---- your processing here ----
        # Example: draw FPS-ish text
        cv2.putText(
            frame,
            f"{msg.header.stamp.sec}.{msg.header.stamp.nanosec:09d}",
            (10, 30),
            cv2.FONT_HERSHEY_SIMPLEX,
            1,
            (255, 255, 255),
            2,
        )

        # Show (optional)
        cv2.imwrite("./frame.jpg", frame)
        cv2.imshow("camera", frame)
        cv2.waitKey(1)


def main():
    rclpy.init()
    node = CameraProcessNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        cv2.destroyAllWindows()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
