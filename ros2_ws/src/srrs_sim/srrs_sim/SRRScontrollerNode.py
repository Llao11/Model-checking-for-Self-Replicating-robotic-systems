
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray,Empty,String
from sensor_msgs.msg import JointState
from ros_gz_interfaces.msg import Contacts
from ament_index_python.packages import get_package_share_directory
import math
import time
import numpy as np
from rclpy.duration import Duration

# TODO: Change timer.sleep() in goto_XYZ() to checking with contact sensor
# TODO: Write separate class to search for parts around with camera

class SRRSController(Node):
    def __init__(self):
        super().__init__('robot_controller')
        self.create_publishers()
        self.create_subscribers()
        self.fixed_end=1
        # threshold difference between target and achivable angles of joint - for waiting while moving in target position
        self.joint_diff_threshold = 2 # [degrees] 
        self.joint_angles_current = [0,0,0,0,0]
    

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
    
    def create_subscribers(self):
        # self.contact1_subscriber = self.create_subscription(String, '/contact1/change_state', self.contact1_changed ,10)
        self.joints_angles_subscriber = self.create_subscription(JointState, '/joint_states', self.joint_state_changed ,10)

    # =========================================================================================================================================
    # The free end of robot  moving to x,y,z relative to the fixed part (0,0) 
    def goto_XYZ(self, x, y, z, step_size=2):
        if x == '\n': x=0
        if y == '\n': y=0
        if z == '\n': z=0
        x = float(x)
        y = float(y)
        z = float(z)
        # Choose if target point in near or far form (0,0)
        if abs(x) > step_size or abs(y) > step_size :
            # going to a far located point
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
            # Step algorithm:
            self.goto_XYZ(stepX,stepY,1)        # go to step in selected direction above base (z+1) 
            self.goto_XYZ(stepX,stepY,0)        # go to step in selected direction on the base 
            self.swap_fix_block()               # change base
            self.goto_XYZ( x, y, z, step_size)  # recursively go to the next step
        # near pose calculation
        else:
            command_sequences = self.calculate_angles(x,y,z)
            self.rotate_joints(command_sequences)


    def calculate_angles( self, x, y, z ):
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
            # self.get_logger().info(f"ANGLES fix1: {joint1}  {joint2}  {joint3}  {joint4}  {joint5}" )
            command_sequences = [joint1, joint2, joint3, joint4, joint5]

        elif self.fixed_end==2:
            joint1 = joint1+180
            joint5 = joint5+180
            # self.get_logger().info(f"ANGLES fix2:  {joint1} {joint2}  {joint3}  {joint4}  {joint5}")
            command_sequences = [joint5, joint4, joint3, joint2, joint1]
        else: 
            self.get_logger().info(f"End block not fixed")
        return command_sequences
    
    
    # Low level joints control ===============================================================================================================
    
    def rotate_joints(self,command_sequences): 
        for joint_index in range(len(command_sequences)):
            self.rotate_joint(joint_index,float(command_sequences[joint_index]))
        self.wait_movement_finish(command_sequences)
        
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
            
    # Wait until movement finished
    def wait_movement_finish(self, joints_angles_target: list[float]):      # joint target angles in degrees
        self.current_target_angles = joints_angles_target
        self.movement_stop_flag = False
        self.timer_rate=0.1       # checking rate in seconds
        self.max_waiting_time = 5 # in seconds
        self.step_count = 0
        self.timer = self.create_timer( self.timer_rate, self.waiting_step)                
        while self.movement_stop_flag == False:
            # self.get_logger().info(f"self.step_count \t: {self.step_count} ")
            max_count = self.max_waiting_time/self.timer_rate
            if self.step_count >= max_count:  # stop movement after max_waiting_time
                self.movement_stop_flag = True
                self.get_logger().info(f"ERROR: target point not achived \n")
        self.timer.destroy()
    
    def waiting_step(self):
        self.step_count = self.step_count + 1
        # self.get_logger().info(f"self.step_count \t: {self.step_count} ")
        # self.get_logger().info(f"command_sequences: {self.current_target_angles} \n")
        joints_angles_target = [float(a) for a in self.current_target_angles]                                         # str to float
        joint_angles_current_deg = [float(angle)*180.0/math.pi for angle in self.joint_angles_current]          # rad to deg
        diff = [abs(a-b) for a,b in zip(joints_angles_target, joint_angles_current_deg)]                        # calculate difference in deg
        if max(diff) < self.joint_diff_threshold:
            self.movement_stop_flag = True
            # self.get_logger().info(f"movement_stop_flag: {self.movement_stop_flag}")

    def joint_state_changed(self, msg):
        joint_angles_current_dict = dict(zip( msg.name, msg.position ))
        sorted_names = ['rev0_1', 'rev2_3', 'rev5_6', 'rev8_9', 'rev13_14']
        self.joint_angles_current = [joint_angles_current_dict[i] for i in sorted_names]
        # self.get_logger().info(f"sorted: {sorted_names}")
        # self.get_logger().info(f"joint_angles_current: {self.joint_angles_current}")


    def get_joint_angle(self, joint_num):
        joint=float(self.joint_angles_current[joint_num])*180.0/math.pi
        return joint    
    
    # Fix to base  ===========================================================================================================================

    def get_fixed_end(self):
        return self.fixed_end
    
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
        time.sleep(0.3)

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
        time.sleep(0.3)

    def free_1(self):
        msg = Empty()
        self.detach_publisher1.publish(msg)
        self.get_logger().info("Published detach1 message.")

    def free_2(self):
        msg = Empty()
        self.detach_publisher2.publish(msg)
        self.get_logger().info("Published detach2 message.")

    
    # Fix objects  ===========================================================================================================================
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


