
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray,Empty
from ament_index_python.packages import get_package_share_directory
import math
import time

class SRRSController(Node):
    def __init__(self):
        super().__init__('robot_controller_gui')
        self.create_publishers()
        self.fixed_end=1

    # Fix to base
    def swap_fix_block(self):
        if self.get_fixed_end() == 1:
                self.fix_2()
        elif self.get_fixed_end() == 2:
            self.fix_1()

    def fix_1(self, **kwargs):
        msg = Empty()
        self.attach_publisher1.publish(msg)
        self.get_logger().info("Published attach1 message.")
        self.fixed_end=1
        self.free_2()
        self.get_logger().info(f"fixed_end=1")
        if "gui" in kwargs:
            gui= kwargs.get('gui', None)
            gui.btn_fix1_base.config(bg="green")
            gui.btn_fix2_base.config(bg="white")

    def fix_2(self,**kwargs):
        msg = Empty()
        self.attach_publisher2.publish(msg)
        self.get_logger().info("Published attach2 message.")
        self.fixed_end=2
        self.free_1()
        self.get_logger().info(f"fixed_end=2")
        if "gui" in kwargs:
            gui= kwargs.get('gui', None)
            gui.btn_fix1_base.config(bg="white")
            gui.btn_fix2_base.config(bg="green")

    def free_1(self):
        msg = Empty()
        self.detach_publisher1.publish(msg)
        self.get_logger().info("Published detach1 message.")

    def free_2(self):
        msg = Empty()
        self.detach_publisher2.publish(msg)
        self.get_logger().info("Published detach2 message.")

    
    # Fix objects

    def fix_obj1(self,**kwargs):
        msg = Empty()
        self.attach_publisher_obj1.publish(msg)
        self.get_logger().info("Published attach1 message.")
        self.free_obj2()
        if "gui" in kwargs:
            gui= kwargs.get('gui', None)
            gui.btn_fix1_obj.config(bg="red")
            gui.btn_free1_obj.config(bg="white")

    def fix_obj2(self,**kwargs):
        msg = Empty()
        self.attach_publisher_obj2.publish(msg)
        self.get_logger().info("Published attach2 message.")
        self.free_obj1()
        if "gui" in kwargs:
            gui= kwargs.get('gui', None)
            gui.btn_fix2_obj.config(bg="red")
            gui.btn_free2_obj.config(bg="white")

    def free_obj1(self,**kwargs):
        msg = Empty()
        self.detach_publisher_obj1.publish(msg)
        self.get_logger().info("Published detach1 message.")
        if "gui" in kwargs:
            gui= kwargs.get('gui', None)
            gui.btn_fix1_obj.config(bg="white")
            gui.btn_free1_obj.config(bg="green")

    def free_obj2(self,**kwargs):
        msg = Empty()
        self.detach_publisher_obj2.publish(msg)
        self.get_logger().info("Published detach2 message.")
        if "gui" in kwargs:
            gui= kwargs.get('gui', None)
            gui.btn_fix2_obj.config(bg="white")
            gui.btn_free2_obj.config(bg="green")


    # The free end of robot  moving to x,y,z relative to the fixed part
    def goto_XYZ(self, x, y, z, step_size=2):

        if x == '\n': x=0
        if y == '\n': y=0
        if z == '\n': z=0
        x = float(x)
        y = float(y)
        z = float(z)

        # going to a far located point
        if abs(x) > step_size or abs(y) > step_size :
            if x > step_size:
                stepX = step_size
                x = x-step_size
            elif x < -step_size:
                stepX = -step_size
                x = x+step_size
            else: 
                stepX = 0
            if y > step_size:
                stepY = step_size
                y = y-step_size
            elif y < -step_size:
                stepY = -step_size
                y = y+step_size
            else: 
                stepY = 0
            self.get_logger().info(f"\nX: {x}\n Y:{y}\n Z:{z}")
            self.goto_XYZ(stepX,stepY,0)
            time.sleep(4)
            self.swap_fix_block()
            time.sleep(1)
            self.goto_XYZ( x, y, z, step_size)
        
        # near pose calculation
        else:
            # in XY plane:
            r = math.sqrt(x*x + y*y)
            r_0 = math.sqrt(x*x + y*y - 1)

            beta  = math.degrees(math.atan2(y,x))
            beta_0 = beta - math.degrees(math.asin(1/r))

            alpha = math.degrees(math.asin( math.sqrt(r_0*r_0+z*z)/4 ))
            gamma = math.degrees(math.atan2( z,abs(r_0) ))

            joint1 = beta_0
            joint2 = alpha-gamma
            joint3 = 180-2*alpha
            joint4 = alpha+gamma
            joint5 = beta_0
            
            if self.fixed_end==1:
                # change the basic direction if 
                joint1 = joint1
                joint5 = joint5
                # self.get_logger().info(f"joint1: {joint1}")
                # self.get_logger().info(f"joint1: {joint1}")
                # self.get_logger().info(f"ANGLES fix1: {joint1}  {joint2}  {joint3}  {joint4}  {joint5}" )
                command_sequences = [joint1, joint2, joint3, joint4, joint5]

            elif self.fixed_end==2:
                joint1 = joint1+180
                joint5 = joint5+180
                # self.get_logger().info(f"ANGLES fix2:  {joint1} {joint2}  {joint3}  {joint4}  {joint5}")
                command_sequences = [joint5, joint4, joint3, joint2, joint1]
            
            for joint_index in range(len(command_sequences)):
                self.rotate_joint(joint_index,command_sequences[joint_index])

    
    def rotate_joints(self,command_sequences):
        for joint_index in range(len(command_sequences)):
            self.rotate_joint(joint_index,command_sequences[joint_index])

    def rotate_joint(self,joint_index,angle):
        command = Float64MultiArray()
        # Degrees to Radians
        try:
            command.data = [float(angle)* math.pi/180.0]
            self.command_publishers[joint_index].publish(command)
            # self.get_logger().info(f"Published command for joint {joint_index}: {command.data}")
        except:
            pass
            # self.get_logger().info(f"No data for joint {joint_index}: {command.data}")



    def create_publishers(self):
        # Publishers for attach and detach topics
        self.attach_publisher_voxel = self.create_publisher(Empty, '/attach_link_voxel', 10)
        self.detach_publisher_voxel = self.create_publisher(Empty, '/detach_link_voxel', 10)
        self.attach_publisher1 = self.create_publisher(Empty, '/attach_link1', 10)
        self.detach_publisher1 = self.create_publisher(Empty, '/detach_link1', 10)
        self.attach_publisher2 = self.create_publisher(Empty, '/attach_link2', 10)
        self.detach_publisher2 = self.create_publisher(Empty, '/detach_link2', 10)

        self.attach_publisher_obj1 = self.create_publisher(Empty, '/attach_obj_link1', 10)
        self.attach_publisher_obj2 = self.create_publisher(Empty, '/attach_obj_link2', 10)
        self.detach_publisher_obj1 = self.create_publisher(Empty, '/detach_obj_link1', 10)
        self.detach_publisher_obj2 = self.create_publisher(Empty, '/detach_obj_link2', 10)

        # Separate publishers for each joint controller
        self.command_publisher1 = self.create_publisher(Float64MultiArray,'/position_controller1/commands',10)
        self.command_publisher2 = self.create_publisher(Float64MultiArray,'/position_controller2/commands',10)
        self.command_publisher3 = self.create_publisher(Float64MultiArray,'/position_controller3/commands',10)
        self.command_publisher4 = self.create_publisher(Float64MultiArray,'/position_controller4/commands',10)
        self.command_publisher5 = self.create_publisher(Float64MultiArray,'/position_controller5/commands',10)
        self.command_publishers = [self.command_publisher1,self.command_publisher2,self.command_publisher3,
                                   self.command_publisher4,self.command_publisher5]
        
    def get_fixed_end(self):
        return self.fixed_end