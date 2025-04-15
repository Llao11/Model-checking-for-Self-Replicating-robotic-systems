import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from std_msgs.msg import Float64MultiArray,Empty
from ament_index_python.packages import get_package_share_directory
import tkinter as tk
import threading
import math
import json
import os

class GUIController(Node):
    def __init__(self):
        super().__init__('robot_controller_gui')
        self.create_publishers()
        self.fixed_end=1

    # Fix to base
    def fix_1(self):
        msg = Empty()
        self.attach_publisher1.publish(msg)
        self.get_logger().info("Published attach1 message.")
        self.fixed_end=1
        self.free_2()

    def fix_2(self):
        msg = Empty()
        self.attach_publisher2.publish(msg)
        self.get_logger().info("Published attach2 message.")
        self.fixed_end=2
        self.free_1()

    def free_1(self):
        msg = Empty()
        self.detach_publisher1.publish(msg)
        self.get_logger().info("Published detach1 message.")

    def free_2(self):
        msg = Empty()
        self.detach_publisher2.publish(msg)
        self.get_logger().info("Published detach2 message.")

    
    # Fix objects

    def fix_obj1(self):
        msg = Empty()
        self.attach_publisher_obj1.publish(msg)
        self.get_logger().info("Published attach1 message.")
        self.free_obj2()

    def fix_obj2(self):
        msg = Empty()
        self.attach_publisher_obj2.publish(msg)
        self.get_logger().info("Published attach2 message.")
        self.free_obj1()

    def free_obj1(self):
        msg = Empty()
        self.detach_publisher_obj1.publish(msg)
        self.get_logger().info("Published detach1 message.")

    def free_obj2(self):
        msg = Empty()
        self.detach_publisher_obj2.publish(msg)
        self.get_logger().info("Published detach2 message.")

    # The free end of robot si moving to x,y,z relative to the fixed part
    def goto_XYZ(self, x,y,z):
        if x == '\n': x=0
        if y == '\n': y=0
        if z == '\n': z=0
        x = float(x)
        y = float(y)
        z = float(z)
        alpha = math.degrees(math.asin( math.sqrt(x*x+z*z)/4 ))
        gamma = math.degrees(math.atan2( z,x ))
        self.get_logger().info(f"alpha: {alpha}  gamma: {gamma}")
        joint2 = alpha-gamma
        joint3 = 180-2*alpha
        joint4 = alpha+gamma
        if self.fixed_end==1:
            self.get_logger().info(f"ANGLES:{joint2}  {joint3}  {joint4}")
            command_sequences = [0, joint2, joint3, joint4, 180]
        elif self.fixed_end==2:
            self.get_logger().info(f"ANGLES:{joint2}  {joint3}  {joint4}")
            command_sequences = [180, joint4, joint3, joint2, 0]
        
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
            self.get_logger().info(f"Published command for joint {joint_index}: {command.data}")
        except:
            self.get_logger().info(f"No data for joint {joint_index}: {command.data}")


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

class GUI:
    def __init__(self, node: GUIController):
        self.node = node
        self.root = tk.Tk()
        self.root.title("Robot Controller")

        label_x= tk.Label(self.root,text="X")
        outputx = tk.Text(self.root, height=1, width=6)
        label_y= tk.Label(self.root,text="Y")
        outputy = tk.Text(self.root, height=1, width=6)
        label_z= tk.Label(self.root,text="Z")
        outputz = tk.Text(self.root, height=1, width=6)
        btn_run = tk.Button(self.root, text="Go to XYZ", command=lambda: self.node.goto_XYZ(x=outputx.get('1.0', tk.END), 
                                                                                            y=outputy.get('1.0', tk.END), 
                                                                                            z=outputz.get('1.0', tk.END)))

        btn_fix1_base = tk.Button(self.root, text="Fix block1 to base", command=lambda: self.node.fix_1())
        btn_fix2_base = tk.Button(self.root, text="Fix block2 to base", command=lambda: self.node.fix_2())

        btn_fix1_obj = tk.Button(self.root, text="Fix object to block 1", command=lambda: self.node.fix_obj1())
        btn_fix2_obj = tk.Button(self.root, text="Fix object to block 2", command=lambda: self.node.fix_obj2())
        btn_free1_obj = tk.Button(self.root, text="Free object from block 1", command=lambda: self.node.free_obj1())
        btn_free2_obj = tk.Button(self.root, text="Free object from block 2", command=lambda: self.node.free_obj2())
        label_block1= tk.Label(self.root,text="Block1 - initially lower")
        label_block2= tk.Label(self.root,text="Block2 - initially upper")


        joint1_angle = tk.Text(self.root, height=1,width=6)
        joint2_angle = tk.Text(self.root, height=1,width=6)
        joint3_angle = tk.Text(self.root, height=1,width=6)
        joint4_angle = tk.Text(self.root, height=1,width=6)
        joint5_angle = tk.Text(self.root, height=1,width=6)
        joint1_angle.insert(tk.END, "0")
        joint2_angle.insert(tk.END, "0")
        joint3_angle.insert(tk.END, "0")
        joint4_angle.insert(tk.END, "0")
        joint5_angle.insert(tk.END, "0")

        label_angle = tk.Label(self.root,text="Angles in deg")
        btn_joint1 = tk.Button(self.root, text="Set Joint 1", command=lambda: self.node.rotate_joint(0,joint1_angle.get('1.0', tk.END)))
        btn_joint2 = tk.Button(self.root, text="Set Joint 2", command=lambda: self.node.rotate_joint(1,joint2_angle.get('1.0', tk.END)))
        btn_joint3 = tk.Button(self.root, text="Set Joint 3", command=lambda: self.node.rotate_joint(2,joint3_angle.get('1.0', tk.END)))
        btn_joint4 = tk.Button(self.root, text="Set Joint 4", command=lambda: self.node.rotate_joint(3,joint4_angle.get('1.0', tk.END)))
        btn_joint5 = tk.Button(self.root, text="Set Joint 5", command=lambda: self.node.rotate_joint(4,joint5_angle.get('1.0', tk.END)))
        btn_joints = tk.Button(self.root, text="Set all", command=lambda: self.node.rotate_joints([joint1_angle.get('1.0', tk.END),
                                                                                                   joint2_angle.get('1.0', tk.END),
                                                                                                   joint3_angle.get('1.0', tk.END),
                                                                                                   joint4_angle.get('1.0', tk.END),
                                                                                                   joint5_angle.get('1.0', tk.END),]))

        label_x.grid(row=0, column=0)
        outputx.grid(row=0, column=1)
        label_y.grid(row=1, column=0)
        outputy.grid(row=1, column=1)
        label_z.grid(row=2, column=0)
        outputz.grid(row=2, column=1)
        btn_run.grid(row=3, column=0)

        btn_fix2_base.grid(row=5, column=0)
        btn_fix1_base.grid(row=6, column=0)
        
        label_block2.grid(row=5, column=1)
        label_block1.grid(row=6, column=1)
        
        btn_fix2_obj.grid(row=7, column=0)
        btn_fix1_obj.grid(row=8, column=0)
        
        btn_free2_obj.grid(row=7, column=1)
        btn_free1_obj.grid(row=8, column=1)

        joint1_angle.grid(row=1, column=5)
        joint2_angle.grid(row=2, column=5)
        joint3_angle.grid(row=3, column=5)
        joint4_angle.grid(row=4, column=5)
        joint5_angle.grid(row=5, column=5)

        label_angle.grid(row=0, column=5)

        btn_joint1.grid(row=1, column=4)
        btn_joint2.grid(row=2, column=4)
        btn_joint3.grid(row=3, column=4)
        btn_joint4.grid(row=4, column=4)
        btn_joint5.grid(row=5, column=4)
        btn_joints.grid(row=6, column=4)



    def run(self):
        self.root.mainloop()

def main():
    rclpy.init()
    node = GUIController()

    # Run ROS spin in a separate thread
    threading.Thread(target=rclpy.spin, args=(node,), daemon=True).start()

    gui = GUI(node)
    gui.run()

    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
