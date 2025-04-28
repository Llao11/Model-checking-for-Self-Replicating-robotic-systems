
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray,Empty, String
from ros_gz_interfaces.msg import Contacts
from ament_index_python.packages import get_package_share_directory
import math
import time
from rclpy.duration import Duration

# TODO: Change timer.sleep() in goto_XYZ() to checking with contact sensor
# TODO: Write separate class to search for parts around with camera

class SRRSsensorsNode(Node):
    def __init__(self):
        super().__init__('robot_sensor')
        self.create_publishers()
        self.create_subscribers()
        

    def create_publishers(self):
        # Publishers for sending colliding objects
        self.contact1_publisher = self.create_publisher(String, '/contact1/change_state', 10)
        self.contact2_publisher = self.create_publisher(String, '/contact2/change_state', 10)

        
    def create_subscribers(self):
        self.contact1_collision = False
        self.contact2_collision = False
        self.contact1_object = None
        self.contact2_object = None
        self.contact1_last_update = self.get_clock().now()
        self.contact2_last_update = self.get_clock().now()
        self.period = Duration(seconds=0.5)
        self.create_timer(0.1, self.timer_callback)
        self.contact1_subscriber = self.create_subscription(Contacts,"/robot/contact1", self.set_contact1_state ,10)
        self.contact2_subscriber = self.create_subscription(Contacts,"/robot/contact2", self.set_contact2_state ,10)
    

    def set_contact1_state(self, msg: Contacts):
        contact_msg = msg.contacts[0]
        # self.get_logger().info(f"Collision between {contact_msg.collision1.name.split("_")[0]} and {contact_msg.collision2.name}")
        old_contact1_collision = self.contact1_collision
        self.contact1_collision=True
        self.contact1_last_update = self.get_clock().now()
        self.contact1_object = contact_msg.collision2.name.split("::")[0]
        
        # Log changes in contact sensor state
        if old_contact1_collision != self.contact1_collision:
            self.get_logger().info(f"\nContact 1: {self.contact1_object}")
            self.publish_contact1(self.contact1_object)
    
    def set_contact2_state(self, msg: Contacts):
        contact_msg = msg.contacts[0]
        # self.get_logger().info(f"Collision between {contact_msg.collision1.name.split("_")[0]} and {contact_msg.collision2.name}")
        old_contact2_collision = self.contact2_collision
        self.contact2_collision=True
        self.contact2_last_update = self.get_clock().now()
        self.contact2_object = contact_msg.collision2.name.split("::")[0]
        if old_contact2_collision != self.contact2_collision:
            self.get_logger().info(f"\nContact 2: {self.contact2_object}")
            self.publish_contact2(self.contact2_object)

    
    def timer_callback(self):
        # check if last contact update was earlier then period
        old_contact1_collision = self.contact1_collision
        old_contact2_collision = self.contact2_collision

        if self.contact1_collision==True and (self.get_clock().now() - self.contact1_last_update) > self.period:
            self.contact1_collision = False
            self.contact1_object = None
        if self.contact2_collision==True and (self.get_clock().now() - self.contact2_last_update) > self.period:
            self.contact2_collision = False
            self.contact2_object = None
        
        # Log changes in contact sensor state
        if old_contact1_collision != self.contact1_collision:
            self.get_logger().info(f"\nContact 1: {self.contact1_object}")
            self.publish_contact1(self.contact1_object)
        if old_contact2_collision != self.contact2_collision:
            self.get_logger().info(f"\nContact 2: {self.contact2_object}")
            self.publish_contact2(self.contact2_object)
        
    def publish_contact1(self, object1):
        msg = String()
        msg.data = str(object1)
        self.contact1_publisher.publish(msg)
    
    def publish_contact2(self, object2):
        msg = String()
        msg.data = str(object2)
        self.contact2_publisher.publish(msg)

