import rclpy
import tkinter as tk
import threading
from rclpy.executors import MultiThreadedExecutor

from . import SRRScontrollerNode
from . import SRRSsensorsNode


class GUI:
    def __init__(
        self, controller_node: SRRScontrollerNode, sensor_node: SRRSsensorsNode
    ):
        self.controller_node = controller_node
        self.sensor_node = sensor_node
        self.root = tk.Tk()
        self.root.title("Robot Controller")

        # Coordinate control

        label_x = tk.Label(self.root, text="X")
        outputx = tk.Text(self.root, height=1, width=6)
        label_y = tk.Label(self.root, text="Y")
        outputy = tk.Text(self.root, height=1, width=6)
        label_z = tk.Label(self.root, text="Z")
        outputz = tk.Text(self.root, height=1, width=6)
        btn_run = tk.Button(
            self.root,
            text="Go to XYZ",
            command=lambda: self.goto_XYZ(
                outputx.get("1.0", tk.END),
                outputy.get("1.0", tk.END),
                outputz.get("1.0", tk.END),
            ),
        )
        label_x.grid(row=0, column=0)
        outputx.grid(row=0, column=1)
        label_y.grid(row=1, column=0)
        outputy.grid(row=1, column=1)
        label_z.grid(row=2, column=0)
        outputz.grid(row=2, column=1)
        btn_run.grid(row=3, column=0)

        #  End block fix

        self.btn_fix1_base = tk.Button(
            self.root,
            text="Fix block1 to base",
            command=lambda: self.controller_node.fix_1_to_base(gui=self),
        )
        self.btn_fix2_base = tk.Button(
            self.root,
            text="Fix block2 to base",
            command=lambda: self.controller_node.fix_2_to_base(gui=self),
        )

        self.btn_fix1_obj = tk.Button(
            self.root,
            text="Fix object 1 to block 1",
            command=lambda: self.controller_node.fix_obj_to_block1(1, gui=self),
        )
        self.btn_fix2_obj = tk.Button(
            self.root,
            text="Fix object 1 to block 2",
            command=lambda: self.controller_node.fix_obj_to_block2(1, gui=self),
        )

        # TODO change buttons/elements to fix only connected objects(
        # not only 1 as in line 42)

        self.btn_free1_obj = tk.Button(
            self.root,
            text="Free objects from block 1",
            command=lambda: self.controller_node.free_block1_from_obj(gui=self),
        )
        self.btn_free2_obj = tk.Button(
            self.root,
            text="Free objects from block 2",
            command=lambda: self.controller_node.free_block2_from_obj(gui=self),
        )
        self.btn_start_assemble = tk.Button(
            self.root,
            text="Start assemble",
            command=lambda: self.start_assemble(),
        )

        # Position fix/free buttons
        self.btn_fix2_base.grid(row=5, column=0)
        self.btn_fix1_base.grid(row=6, column=0)
        self.btn_fix2_obj.grid(row=7, column=0)
        self.btn_fix1_obj.grid(row=8, column=0)

        self.btn_free2_obj.grid(row=7, column=1)
        self.btn_free1_obj.grid(row=8, column=1)

        # Assembly
        self.btn_start_assemble.grid(row=9, column=0)

        # Individual joint control

        joint1_angle = tk.Text(self.root, height=1, width=6)
        joint2_angle = tk.Text(self.root, height=1, width=6)
        joint3_angle = tk.Text(self.root, height=1, width=6)
        joint4_angle = tk.Text(self.root, height=1, width=6)
        joint5_angle = tk.Text(self.root, height=1, width=6)
        joint1_angle.insert(tk.END, "0")
        joint2_angle.insert(tk.END, "0")
        joint3_angle.insert(tk.END, "0")
        joint4_angle.insert(tk.END, "0")
        joint5_angle.insert(tk.END, "0")

        btn_joint1 = tk.Button(
            self.root,
            text="Set Joint 1",
            command=lambda: self.controller_node.rotate_joint(
                0, joint1_angle.get("1.0", tk.END)
            ),
        )
        btn_joint2 = tk.Button(
            self.root,
            text="Set Joint 2",
            command=lambda: self.controller_node.rotate_joint(
                1, joint2_angle.get("1.0", tk.END)
            ),
        )
        btn_joint3 = tk.Button(
            self.root,
            text="Set Joint 3",
            command=lambda: self.controller_node.rotate_joint(
                2, joint3_angle.get("1.0", tk.END)
            ),
        )
        btn_joint4 = tk.Button(
            self.root,
            text="Set Joint 4",
            command=lambda: self.controller_node.rotate_joint(
                3, joint4_angle.get("1.0", tk.END)
            ),
        )
        btn_joint5 = tk.Button(
            self.root,
            text="Set Joint 5",
            command=lambda: self.controller_node.rotate_joint(
                4, joint5_angle.get("1.0", tk.END)
            ),
        )
        btn_joints = tk.Button(
            self.root,
            text="Set all",
            command=lambda: self.controller_node.rotate_joints(
                [
                    joint1_angle.get("1.0", tk.END),
                    joint2_angle.get("1.0", tk.END),
                    joint3_angle.get("1.0", tk.END),
                    joint4_angle.get("1.0", tk.END),
                    joint5_angle.get("1.0", tk.END),
                ]
            ),
        )

        joint1_angle.grid(row=1, column=5)
        joint2_angle.grid(row=2, column=5)
        joint3_angle.grid(row=3, column=5)
        joint4_angle.grid(row=4, column=5)
        joint5_angle.grid(row=5, column=5)

        btn_joint1.grid(row=1, column=4)
        btn_joint2.grid(row=2, column=4)
        btn_joint3.grid(row=3, column=4)
        btn_joint4.grid(row=4, column=4)
        btn_joint5.grid(row=5, column=4)
        btn_joints.grid(row=6, column=4)

        # Lables fix blocks:
        self.fixed_block_var = tk.StringVar(value=self.controller_node.get_fixed_end())
        self.label_fixed_block = tk.Label(self.root, textvariable=self.fixed_block_var)

        self.label_fix_block1 = tk.Label(
            self.root, text="Block1 fixed - initially lower", bg="red"
        )
        self.label_fix_block2 = tk.Label(
            self.root, text="Block2 fixed - initially upper", bg="yellow"
        )

        self.label_fixed_block.grid(row=4, column=1)
        self.label_fix_block2.grid(row=5, column=1)
        self.label_fix_block1.grid(row=6, column=1)

        # Lables angles:
        label_angle = tk.Label(self.root, text="Angles in deg")
        label_angle.grid(row=0, column=5)
        self.label_joint1_angle = tk.Label(self.root, text=0)
        self.label_joint2_angle = tk.Label(self.root, text=0)
        self.label_joint3_angle = tk.Label(self.root, text=0)
        self.label_joint4_angle = tk.Label(self.root, text=0)
        self.label_joint5_angle = tk.Label(self.root, text=0)
        self.label_joint1_angle.grid(row=1, column=6)
        self.label_joint2_angle.grid(row=2, column=6)
        self.label_joint3_angle.grid(row=3, column=6)
        self.label_joint4_angle.grid(row=4, column=6)
        self.label_joint5_angle.grid(row=5, column=6)

        # Lables contacts:
        label_contact1 = tk.Label(self.root, text="Contact1:")
        label_contact2 = tk.Label(self.root, text="Contact2:")
        label_contact1.grid(row=8, column=4)
        label_contact2.grid(row=7, column=4)

        # KEY shortkats
        self.root.bind("<Return>", btn_run.invoke())

        self.update_angles()
        self.update_fix_end()
        self.update_contact_objects()

        self.lock = threading.Lock()

    def update_angles(self):
        joint1 = tk.StringVar(value=int(self.sensor_node.get_joint_angle(0)))
        joint2 = tk.StringVar(value=int(self.sensor_node.get_joint_angle(1)))
        joint3 = tk.StringVar(value=int(self.sensor_node.get_joint_angle(2)))
        joint4 = tk.StringVar(value=int(self.sensor_node.get_joint_angle(3)))
        joint5 = tk.StringVar(value=int(self.sensor_node.get_joint_angle(4)))
        self.label_joint1_angle.config(textvariable=joint1)
        self.label_joint2_angle.config(textvariable=joint2)
        self.label_joint3_angle.config(textvariable=joint3)
        self.label_joint4_angle.config(textvariable=joint4)
        self.label_joint5_angle.config(textvariable=joint5)
        # schedule next update every 30 ms
        self.root.after(30, self.update_angles)

    def update_fix_end(self):
        self.fixed_block_var = tk.StringVar(
            value="Fixed block: " + str(self.controller_node.get_fixed_end())
        )
        self.label_fixed_block.config(textvariable=self.fixed_block_var)
        # schedule next update every 30 ms
        self.root.after(30, self.update_fix_end)

    def update_contact_objects(self):
        # print("update")
        contact1, contact2 = self.sensor_node.get_contact_objects()
        self.contact_obj1_var = tk.StringVar(value=str(contact1))
        self.contact_obj2_var = tk.StringVar(value=str(contact2))
        label_contact1_obj = tk.Label(self.root, textvariable=self.contact_obj1_var)
        label_contact2_obj = tk.Label(self.root, textvariable=self.contact_obj2_var)
        label_contact1_obj.grid(row=8, column=5)
        label_contact2_obj.grid(row=7, column=5)
        # schedule next update every 100 ms
        self.root.after(100, self.update_contact_objects)

    # def press_gotoXYZ():
    #     self.goto_XYZ(
    #             outputx.get("1.0", tk.END),
    #             outputy.get("1.0", tk.END),
    #             outputz.get("1.0", tk.END),
    #         )

    def goto_XYZ(self, outputx, outputy, outputz):
        thread = threading.Thread(
            target=self.controller_node.goto_XYZ,
            args=(outputx, outputy, outputz),
            daemon=True,
        )
        thread.start()

    # ASSEMBLE ===========================================================================================================================

    def start_assemble(self):
        # self.controller_node.get_logger().info("Start assemble")
        self.controller_node.fix_1_to_base(gui=self)
        self.controller_node.free_block1_from_obj(gui=self)
        self.controller_node.free_block2_from_obj(gui=self)
        self.controller_node.goto_XYZ(
            2,
            2,
            2,
        )

    # RUN ===========================================================================================================================

    def run(self):
        self.root.mainloop()


def main():
    rclpy.init()

    sensors_node = SRRSsensorsNode.SRRSsensorsNode()
    controller_node = SRRScontrollerNode.SRRSController(sensors_node)

    executor = MultiThreadedExecutor()
    executor.add_node(controller_node)
    executor.add_node(sensors_node)

    # Run 2 ROS nodes spin in a separate threads
    threading.Thread(target=executor.spin, daemon=True).start()

    gui = GUI(controller_node, sensors_node)
    gui.run()

    executor.shutdown()
    controller_node.destroy_node()
    sensors_node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
