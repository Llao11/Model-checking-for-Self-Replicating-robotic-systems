# srrs_sim/spawner/part_spawner.py  (ament_python package)
import rclpy, xacro, os
from rclpy.node import Node
from geometry_msgs.msg import Pose
from ros_gz_interfaces.msg import EntityFactory          # message
from ros_gz_interfaces.srv import SpawnEntity            # service

class PartSpawner(Node):
    def __init__(self):
        super().__init__('part_spawner')
        self.cli = self.create_client(SpawnEntity, '/world/empty/spawn_entity')
        self.cli.wait_for_service(timeout_sec=2.0)
        self.spawn_part()
        


    def spawn_part(self, x=1.0, y=-0.60, z=0.134, part_num=99):
        # 1. Generate a temporary URDF from your Xacro
        part_num = 99 # default part number
        tmpfile = os.path.join("src/srrs_sim/urdf", f'part_{part_num}.urdf')
        
        xacro_path = 'src/srrs_sim/urdf/part.xacro'
        doc = xacro.process_file(xacro_path, mappings={'part_num': str(part_num)})
        with open(tmpfile, "w") as fp:
            fp.write(doc.toprettyxml(indent="  "))
        self.get_logger().info(f"Generated URDF: {tmpfile}")

        # 2. Fill the EntityFactory message
        factory              = EntityFactory()
        factory.name         = f'part_{part_num}'
        factory.sdf_filename = "/tmp/part42.urdf"          # could also fill `sdf` string
        factory.pose         = Pose()
        factory.pose.position.x = x
        factory.pose.position.y = y
        factory.pose.position.z = z

        # 3. Wrap it in the SpawnEntity service request
        req = SpawnEntity.Request()
        req.entity_factory = factory

        # 4. Call the service
        future = self.cli.call_async(req)
        rclpy.spin_until_future_complete(self, future, timeout_sec=5.0)

        if future.result() and future.result().success:
            self.get_logger().info(f"Spawned {factory.name}")
        else:
            self.get_logger().error("Spawn failed")


def main():
    rclpy.init()
    rclpy.spin(PartSpawner())
