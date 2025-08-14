import rclpy
import os
import time
import subprocess
import queue
import tkinter as tk
import threading
from rclpy.executors import MultiThreadedExecutor

from PIL import Image as PILImage
from PIL import ImageTk
import tkinter as tk

from . import SRRScontrollerNode
from . import SRRSsensorsNode
from . import camera_subscriber_node


class GUI:
    def __init__(
        self,
        controller_node: SRRScontrollerNode.SRRSController,
        sensor_node: SRRSsensorsNode.SRRSsensorsNode,
        camera1_queue: queue.Queue,
        camera2_queue: queue.Queue,
    ):
        self.controller_node = controller_node
        self.sensor_node = sensor_node

        # Camera data initial variables
        self.queue1_frames = camera1_queue
        self.queue2_frames = camera2_queue
        self.photo1 = None  # keep reference
        self.photo2 = None  # keep reference
        self._running = True

        self.root = tk.Tk()
        self.root.title("Robot Controller")
        self.root.protocol("WM_DELETE_WINDOW", self.on_close)

        self.ui_setup()

        # setup Video from Camera

        # thread_cam1 = threading.Thread(
        #     target=self.root.after,
        #     args=(16, self.poll_queue1),
        #     daemon=True,
        # )
        # thread_cam2 = threading.Thread(
        #     target=self.root.after,
        #     args=(26, self.poll_queue2),
        #     daemon=True,
        # )
        # thread_cam1.start()
        # thread_cam2.start()
        self.root.after(16, self.poll_queue1)  # ~60 fps
        self.root.after(26, self.poll_queue2)

        # spawn additional parts during runtime
        self.current_part_num = 10

        # KEY shortkats
        self.update_angles()
        self.update_fix_end()
        self.update_contact_objects()
        # self.lock = threading.Lock()

    def ui_setup(self):
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

        # Labels camera:
        self.camera_label1 = tk.Label(self.root)
        self.camera_label1.grid(row=10, column=0, columnspan=3)
        self.camera_label2 = tk.Label(self.root)
        self.camera_label2.grid(row=10, column=3, columnspan=3)
        # self.root.bind("<Return>", lambda e: btn_run.invoke())

    def poll_queue1(self):
        """camera 1 queue"""
        if not self._running:
            return
        try:
            frame_rgb = self.queue1_frames.get_nowait()
            pil_img = PILImage.fromarray(frame_rgb)
            pil_img = pil_img.resize((320, 240), PILImage.LANCZOS)
            self.photo1 = ImageTk.PhotoImage(image=pil_img)
            self.camera_label1.config(image=self.photo1)
        except queue.Empty:
            pass
        finally:
            self.root.after(16, self.poll_queue1)

    def poll_queue2(self):
        """camera 2 queue"""
        if not self._running:
            return
        try:
            frame_rgb = self.queue2_frames.get_nowait()
            pil_img = PILImage.fromarray(frame_rgb)
            pil_img = pil_img.resize((320, 240), PILImage.LANCZOS)
            self.photo2 = ImageTk.PhotoImage(image=pil_img)
            self.camera_label2.config(image=self.photo2)
        except queue.Empty:
            pass
        finally:
            self.root.after(26, self.poll_queue2)

    def update_angles(self):
        joint1 = tk.StringVar(value=str(int(self.sensor_node.get_joint_angle(0))))
        joint2 = tk.StringVar(value=str(int(self.sensor_node.get_joint_angle(1))))
        joint3 = tk.StringVar(value=str(int(self.sensor_node.get_joint_angle(2))))
        joint4 = tk.StringVar(value=str(int(self.sensor_node.get_joint_angle(3))))
        joint5 = tk.StringVar(value=str(int(self.sensor_node.get_joint_angle(4))))
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

    def goto_XYZ(self, outputx, outputy, outputz):
        """Create a thread with command to ControlNode to goto_XYZ"""
        # self.controller_node.goto_XYZ(outputx, outputy, outputz)
        thread = threading.Thread(
            target=self.controller_node.goto_XYZ,
            args=(outputx, outputy, outputz),
            daemon=True,
        )
        thread.start()
        thread.join()

    # ASSEMBLE ===========================================================================================================================
    def start_assemble(self):
        """Main assemble sequence"""
        self.controller_node.get_logger().info("Start assemble")
        self.controller_node.fix_1_to_base(gui=self)
        self.controller_node.free_block1_from_obj(gui=self)
        self.controller_node.free_block2_from_obj(gui=self)
        self.assemble_coordinates = {"x": 2, "y": -2, "z": 0}
        self.move_part(num=1, x=1, y=2)
        # self.spawn_part(6, 6, 0)
        self.assemble_coordinates["z"] = 1
        self.move_part(num=2, x=-1, y=2)

    def move_part(self, num, x, y):
        """move part number num, from x,y coordinates to assemble_coordinates"""
        self.goto_XYZ(x, y, 3)
        self.goto_XYZ(x, y, 1)
        self.fix_part(num)
        self.goto_XYZ(x, y, 3)
        self.goto_XYZ(
            self.assemble_coordinates["x"],
            self.assemble_coordinates["y"],
            self.assemble_coordinates["z"] + 2,
        )
        self.goto_XYZ(
            self.assemble_coordinates["x"],
            self.assemble_coordinates["y"],
            self.assemble_coordinates["z"] + 1,
        )
        self.free_part()
        self.goto_XYZ(
            self.assemble_coordinates["x"],
            self.assemble_coordinates["y"],
            self.assemble_coordinates["z"] + 2,
        )

    def fix_part(self, part_num, end_num=2):
        """Fix part number part_num to end block number end_num"""
        if end_num == 1:
            self.controller_node.fix_obj_to_block1(part_num)
        if end_num == 2:
            self.controller_node.fix_obj_to_block2(part_num)

    def free_part(self, end_num=2):
        """Free object from end-effector number end_num block"""
        if end_num == 1:
            self.controller_node.free_block1_from_obj()
        if end_num == 2:
            self.controller_node.free_block2_from_obj()

    def spawn_part(self, X=5, Y=5, Z=0):
        """Spawns one block on the field, X,Y,Z - int coordinates relative to the robot base"""
        x = 0.134 * X
        y = 0.134 * Y
        z = 0.135 + 0.134 * Z
        path_to_ros2_ws = (
            "/home/lao/Documents/Masterarbeit/git/SRRS_gazebo_sim/ros2_ws/"
        )
        path_to_part = f"{path_to_ros2_ws}/src/srrs_sim/urdf/new_part.urdf"
        ros_setup = f"source /opt/ros/jazzy/setup.bash && source {
            path_to_ros2_ws
        }/install/setup.bash"
        ros_cmd = f"ros2 run ros_gz_sim create  -world empty  \
            -name  part{self.current_part_num}  -file  \
            {path_to_part}  -x {x} -y {y} -z {z}"
        subprocess.Popen(
            [
                "bash",
                "-c",
                f"{ros_setup} && {ros_cmd}",
                "shell=True",
            ]
        )
        self.current_part_num += 1

    # CLOSE ===========================================================================================================================

    def on_close(self):
        self._running = False
        self.root.destroy()

    # RUN ===========================================================================================================================
    def run(self):
        self.root.mainloop()


def main():
    rclpy.init()

    # common Queue for camera frames
    queue1_frames = queue.Queue(maxsize=1)
    queue2_frames = queue.Queue(maxsize=1)
    camera1_topic = "/camera1/image"
    camera2_topic = "/camera2/image"

    # create Nodes
    sensors_node = SRRSsensorsNode.SRRSsensorsNode()
    controller_node = SRRScontrollerNode.SRRSController(sensors_node)
    camera1_sub_node = camera_subscriber_node.Camera_process_node_gui(
        queue1_frames, camera1_topic
    )
    camera2_sub_node = camera_subscriber_node.Camera_process_node_gui(
        queue2_frames, camera2_topic
    )

    # initializa Nodes
    executor = MultiThreadedExecutor()
    executor.add_node(controller_node)
    executor.add_node(sensors_node)
    executor.add_node(camera1_sub_node)
    executor.add_node(camera2_sub_node)

    # Run 2 ROS nodes spin in a separate threads
    threading.Thread(target=executor.spin, daemon=True).start()

    gui = GUI(controller_node, sensors_node, queue1_frames, queue2_frames)
    gui.run()

    executor.shutdown()
    controller_node.destroy_node()
    sensors_node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
