import threading
import queue
import rclpy
from rclpy.node import Node
from rclpy.executors import SingleThreadedExecutor
from rclpy.qos import QoSPresetProfiles
from sensor_msgs.msg import Image
from cv_bridge import CvBridge

import cv2
from PIL import Image as PILImage
from PIL import ImageTk
import tkinter as tk


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
        self.out_queue.put(frame_rgb)


def start_ros(node, executor):
    # Run the ROS executor forever on a background thread
    executor.add_node(node)
    try:
        executor.spin()
    finally:
        executor.shutdown()
        node.destroy_node()
        rclpy.shutdown()


class TkCameraApp:
    def __init__(self, queue_common: queue.Queue):
        self.queue_frames = queue_common
        self.root = tk.Tk()
        self.root.title("ROS2 Camera (Tkinter)")
        self.label = tk.Label(self.root)
        self.label.pack()
        self.photo = None  # keep reference

        # Close handler
        self.root.protocol("WM_DELETE_WINDOW", self.on_close)
        self._running = True
        self.poll_queue()

    def poll_queue(self):
        if not self._running:
            return
        try:
            frame_rgb = self.queue_frames.get_nowait()
            pil_img = PILImage.fromarray(frame_rgb)
            self.photo = ImageTk.PhotoImage(image=pil_img)
            self.label.config(image=self.photo)
        except queue.Empty:
            pass
        # Aim ~60 FPS UI polling; adjust as needed
        self.root.after(16, self.poll_queue)

    def on_close(self):
        self._running = False
        self.root.destroy()

    def run(self):
        self.root.mainloop()


def main():
    rclpy.init()
    queue_frames = queue.Queue(maxsize=2)

    node = Camera_process_node_gui(
        queue_frames, topic="/camera2/image"
    )  # <- set your topic
    executor = SingleThreadedExecutor()

    ros_thread = threading.Thread(target=start_ros, args=(node, executor), daemon=True)
    ros_thread.start()

    # Start Tkinter on main thread
    app = TkCameraApp(queue_frames)
    app.run()
    # When Tk closes, stop ROS
    executor.shutdown()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
