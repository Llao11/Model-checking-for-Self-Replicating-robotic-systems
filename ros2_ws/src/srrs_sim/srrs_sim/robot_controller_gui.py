import rclpy
import tkinter as tk
import threading
from rclpy.executors import MultiThreadedExecutor

from . import SRRScontrollerNode
from . import SRRSsensorsNode


class GUI:
    def __init__(self, controller_node: SRRScontrollerNode, sensor_node: SRRSsensorsNode):
        self.controller_node = controller_node
        self.root = tk.Tk()
        self.root.title("Robot Controller")

        # Coordinate control

        label_x= tk.Label(self.root,text="X")
        outputx = tk.Text(self.root, height=1, width=6)
        label_y= tk.Label(self.root,text="Y")
        outputy = tk.Text(self.root, height=1, width=6)
        label_z= tk.Label(self.root,text="Z")
        outputz = tk.Text(self.root, height=1, width=6)
        btn_run = tk.Button(self.root, text="Go to XYZ", command=lambda: self.controller_node.goto_XYZ(x=outputx.get('1.0', tk.END), 
                                                                                            y=outputy.get('1.0', tk.END), 
                                                                                            z=outputz.get('1.0', tk.END)))
        label_x.grid(row=0, column=0)
        outputx.grid(row=0, column=1)
        label_y.grid(row=1, column=0)
        outputy.grid(row=1, column=1)
        label_z.grid(row=2, column=0)
        outputz.grid(row=2, column=1)
        btn_run.grid(row=3, column=0)

        #  End block fix

        self.btn_fix1_base = tk.Button(self.root, text="Fix block1 to base", command=lambda: self.controller_node.fix_1(gui=self))
        self.btn_fix2_base = tk.Button(self.root, text="Fix block2 to base", command=lambda: self.controller_node.fix_2(gui=self))

        self.btn_fix1_obj = tk.Button(self.root, text="Fix object to block 1", command=lambda: self.controller_node.fix_obj1(gui=self))
        self.btn_fix2_obj = tk.Button(self.root, text="Fix object to block 2", command=lambda: self.controller_node.fix_obj2(gui=self))
        self.btn_free1_obj = tk.Button(self.root, text="Free object from block 1", command=lambda: self.controller_node.free_obj1(gui=self))
        self.btn_free2_obj = tk.Button(self.root, text="Free object from block 2", command=lambda: self.controller_node.free_obj2(gui=self))

        self.fixed_block_var = tk.StringVar(value = self.controller_node.get_fixed_end())
        label_fixed_block = tk.Label(self.root, textvariable=self.fixed_block_var)
        self.label_fix_block1= tk.Label(self.root,text="Block1 fixed - initially lower", bg="red")
        self.label_fix_block2= tk.Label(self.root,text="Block2 fixed - initially upper", bg="yellow")

        self.btn_fix2_base.grid(row=5, column=0)
        self.btn_fix1_base.grid(row=6, column=0)
        
        label_fixed_block.grid(row=4, column=1)
        self.label_fix_block2.grid(row=5, column=1)
        self.label_fix_block1.grid(row=6, column=1)
        
        self.btn_fix2_obj.grid(row=7, column=0)
        self.btn_fix1_obj.grid(row=8, column=0)
        
        self.btn_free2_obj.grid(row=7, column=1)
        self.btn_free1_obj.grid(row=8, column=1)

        # Individual joint control

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
        btn_joint1 = tk.Button(self.root, text="Set Joint 1", command=lambda: self.controller_node.rotate_joint(0,joint1_angle.get('1.0', tk.END)))
        btn_joint2 = tk.Button(self.root, text="Set Joint 2", command=lambda: self.controller_node.rotate_joint(1,joint2_angle.get('1.0', tk.END)))
        btn_joint3 = tk.Button(self.root, text="Set Joint 3", command=lambda: self.controller_node.rotate_joint(2,joint3_angle.get('1.0', tk.END)))
        btn_joint4 = tk.Button(self.root, text="Set Joint 4", command=lambda: self.controller_node.rotate_joint(3,joint4_angle.get('1.0', tk.END)))
        btn_joint5 = tk.Button(self.root, text="Set Joint 5", command=lambda: self.controller_node.rotate_joint(4,joint5_angle.get('1.0', tk.END)))
        btn_joints = tk.Button(self.root, text="Set all", command=lambda: self.controller_node.rotate_joints([joint1_angle.get('1.0', tk.END),
                                                                                                   joint2_angle.get('1.0', tk.END),
                                                                                                   joint3_angle.get('1.0', tk.END),
                                                                                                   joint4_angle.get('1.0', tk.END),
                                                                                                   joint5_angle.get('1.0', tk.END),]))

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
    controller_node = SRRScontrollerNode.SRRSController()
    sensors_node = SRRSsensorsNode.SRRSsensorsNode()

    executor = MultiThreadedExecutor()
    executor.add_node(controller_node)
    executor.add_node(sensors_node)

    # Run 2 ROS nodes spin in a separate threads
    threading.Thread(target=executor.spin, daemon=True).start()

    gui = GUI(controller_node,sensors_node)
    gui.run()

    executor.shutdown()
    controller_node.destroy_node()
    sensors_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
