#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseArray
from ros_gz_interfaces.srv import SetEntityPose

# identifies the Gazebo entity to move
from ros_gz_interfaces.msg import Entity


class ObjectPoseIO(Node):
    """
    - Subscribes to /model/<model_name>/pose (geometry_msgs/Pose) to track current pose
    - Calls /world/<world_name>/set_pose (ros_gz_interfaces/SetEntityPose) to set pose
    """

    def __init__(self, world_name: str, model_name: str):
        super().__init__("object_pose_io")

        self.world = world_name
        self.model = model_name
        self._latest_pose = None
        self._poses_by_name: dict[str, Pose] = {}

        # 1) Subscribe to live pose from Gazebo (bridged to ROS)
        topic = f"/model/{self.model}/pose"
        self._pose_sub = self.create_subscription(Pose, topic, self._pose_cb, 10)
        self.get_logger().info(f"Listening to: {topic}")

        # 2) Client for Gazebo's set_pose service (bridged to ROS)
        self._set_pose_srv_name = f"/world/{self.world}/set_pose"
        self._set_pose_cli = self.create_client(SetEntityPose, self._set_pose_srv_name)

        if not self._set_pose_cli.wait_for_service(timeout_sec=5.0):
            self.get_logger().warn(
                f"Service {self._set_pose_srv_name} not available (bridge running?)."
            )

    def set_pose(self, pose: Pose, timeout: float = 2.0) -> bool:
        """
        Set the model's pose in Gazebo.
        Returns True on success, False otherwise.
        """
        if not self._set_pose_cli.service_is_ready():
            self.get_logger().error(f"Service {self._set_pose_srv_name} not ready.")
            return False

        req = SetEntityPose.Request()
        req.entity = Entity()  # Identify the entity by name (a model)
        req.entity.name = self.model
        req.pose = pose  # geometry_msgs/Pose

        future = self._set_pose_cli.call_async(req)
        rclpy.spin_until_future_complete(self, future, timeout_sec=timeout)

        if not future.done() or future.result() is None:
            self.get_logger().error("SetEntityPose request timed out or failed.")
            return False

        ok = future.result().success
        if not ok:
            self.get_logger().error("SetEntityPose reported success=False.")
        return ok

    # --- Internals ---

    def _pose_cb(self, msg: Pose):
        # self._latest_pose = msg
        # Iterate all poses in this Pose_V and cache by name
        # self.get_logger().info(f": {msg}")
        p = msg
        x = p.position.x
        y = p.position.y
        z = p.position.z
        if p and not (x == 0 and y == 0 and z == 0):
            self.get_logger().info(f"Current position: [{x:.3f}, {y:.3f}, {z:.3f}]")


def main():
    rclpy.init()
    # Change these to your world/model names:
    node = ObjectPoseIO(world_name="empty", model_name="part1")

    # Optionally: move the object once after 3 seconds

    def move_once():
        node.destroy_timer(timer2)
        pose = Pose()
        pose.position.x = 1.0
        pose.position.y = 0.5
        pose.position.z = 0.3
        # Keep orientation as-is (identity)
        pose.orientation.w = 1.0
        if node.set_pose(pose):
            node.get_logger().info("Set pose succeeded.")
        else:
            node.get_logger().error("Set pose failed.")

    timer2 = node.create_timer(3.0, move_once)

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
