#!/usr/bin/env python3
"""
Tkinter GUI embedding a dynamic **3‑D Matplotlib** plot – now laid out with the
`grid()` geometry‑manager instead of `pack()`.  The functional bits are
unchanged; only the widget placement differs.

* **Plot3DBackend** – unchanged. Owns the `Figure`/`Axes3D` and helper methods.
* **App** – uses a 2‑row grid: row 0 hosts the canvas, row 1 hosts a control
  bar (buttons + axis‑limit widgets).  Columns expand elastically thanks to
  `grid_columnconfigure(..., weight=1)`.

Run the file and you’ll see the same interactive 3‑D plot with buttons and
limit‑boxes, but everything is positioned via `grid()`.
"""

from __future__ import annotations, print_function, with_statement
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk

from block import Block
import xml.etree.ElementTree as ET
import random
import re
import subprocess
import threading
import tkinter as tk
from typing import List, Tuple, Optional
from Plot3D import Plot3D
import matplotlib

# Use the TkAgg backend so Matplotlib can render inside a Tk widget
matplotlib.use("TkAgg")  # must be set *before* importing pyplot
import matplotlib.pyplot as plt  # noqa: E402  pylint: disable=wrong-import-position
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg  # noqa: E402
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 – required for 3‑D backend

# ---------------------------------------------------------------------------
# Data model helper
Point3D = [float, float, float]
input_smv_file = "./smv/robot_structure3d.smv"
output_smv_file = "./smv/template_robot_structure3d.smv"

# ---------------------------------------------------------------------------
# Tkinter GUI wrapper


class App(tk.Tk):
    def __init__(self) -> None:
        """Initiate GUI"""
        super().__init__()
        self.title("3‑D Line Demo")
        self.geometry("900x700")

        self.robot_structure = [[0, 0, 0], [1, 2, 1], [2, 3, 0]]
        self.coordinates_vars: dict[str, tk.StringVar] = {}
        # Backend plot
        self.plot = Plot3D()
        self.plot.set_limits((-50, 50), (-50, 50), (0, 100))
        self.points: List[Point3D] = []

        # --------------------------- main layout (grid) ------------------
        self.grid_rowconfigure(0, weight=1)  # canvas row grows
        self.grid_columnconfigure(0, weight=1)

        # Matplotlib canvas inside Tk
        self.canvas = FigureCanvasTkAgg(self.plot.fig, master=self)
        self.canvas.draw()
        self.canvas_widget = self.canvas.get_tk_widget()
        self.canvas_widget.grid(row=0, column=0, sticky="nsew")

        toolbar = NavigationToolbar2Tk(self.canvas, self, pack_toolbar=False)
        toolbar.grid(row=1, column=0, sticky="ew")
        toolbar.update()
        # Control panel --------------------------------------------------
        self.ctrl = tk.Frame(self)
        self.ctrl.grid(row=2, column=0, sticky="ew", pady=5)
        self.ctrl.columnconfigure((0, 1, 2, 3, 4, 5), weight=1)

        tk.Button(self.ctrl, text="Show Robot", command=self.show_robot).grid(
            row=0, column=0, padx=5, sticky="w"
        )
        self.goalX = tk.StringVar(value=str(1))
        self.goalY = tk.StringVar(value=str(1))
        self.goalZ = tk.StringVar(value=str(1))
        tk.Entry(self.ctrl, textvariable=self.goalX, width=5).grid(
            row=0, column=1, padx=5, sticky="e"
        )
        tk.Entry(self.ctrl, textvariable=self.goalY, width=5).grid(
            row=0, column=2, padx=5, sticky="e"
        )
        tk.Entry(self.ctrl, textvariable=self.goalZ, width=5).grid(
            row=0, column=3, padx=5, sticky="e"
        )
        tk.Button(self.ctrl, text="Set goal point", command=self.add_goal_point).grid(
            row=0, column=4, padx=5, sticky="w"
        )
        tk.Button(self.ctrl, text="Check model", command=self.check_model).grid(
            row=0, column=5, padx=5, sticky="e"
        )
        tk.Button(
            self.ctrl, text="Check reachability", command=self.check_reachability
        ).grid(row=1, column=5, padx=5, sticky="e")
        tk.Button(self.ctrl, text="Read xacro", command=self.read_robot_structure).grid(
            row=2, column=5, padx=5, sticky="e"
        )
        self.status_var = tk.StringVar(value="Ready")
        tk.Label(self.ctrl, textvariable=self.status_var, anchor="w").grid(
            row=3, column=5, padx=5, sticky="e"
        )
        tk.Button(self.ctrl, text="Quit", command=self.destroy).grid(
            row=0, column=6, padx=5, sticky="e"
        )

        # Initial blank plot
        self.plot.draw_lines(self.points)
        # self.add_points()

    def change_status(self, new_status):
        """change status label in UI"""
        self.status_var.set(new_status)

    def show_coord_change(self, index):
        """show UI for changing block"""
        # Axis‑limit widgets --------------------------------------------
        coordinates_frame = tk.Frame(self.ctrl)
        coordinates_frame.grid(row=index + 1, column=0, columnspan=3, padx=10)
        # for index in range(len(self.robot_structure)):
        lbl = tk.Label(coordinates_frame, text=f"Block{index}")
        for idx, axis in enumerate(
            ("X" + str(index), "Y" + str(index), "Z" + str(index))
        ):
            lbl.pack(side=tk.LEFT)
            var = tk.StringVar(value=str(self.points[index][idx]))
            self.coordinates_vars[axis] = var
            entry = tk.Entry(coordinates_frame, textvariable=var, width=5)
            entry.pack(side=tk.LEFT)
        tk.Button(
            coordinates_frame, text="Apply", command=lambda: self.move_block(index)
        ).pack(side=tk.LEFT, padx=5)

    # --------------------------- UI callbacks ---------------------------
    def parse_coordinates(self, key: str) -> Optional[float]:
        text = self.coordinates_vars[key].get().strip()
        if not text:
            return None
        try:
            return float(text)
        except ValueError:
            return None

    def move_block(self, index) -> None:
        x = self.parse_coordinates("X" + str(index))
        y = self.parse_coordinates("Y" + str(index))
        z = self.parse_coordinates("Z" + str(index))
        # Convert pairs where at least one bound was provided; else None
        self.plot.update_point(self.points, index, x, y, z)
        self.plot.refresh(self.points)

    def show_robot(self) -> None:
        """Render a robot"""
        self.points = []
        for idx, pt in enumerate(self.robot_structure):
            self.plot.add_point_with_line(self.points, *pt)
            self.show_coord_change(idx)
        self.plot.refresh(self.points)

    def check_model_nonthreaded(self) -> None:
        """run smv template and get counterexample"""
        self.change_status("Checking ...")

        result = subprocess.run(
            [
                ".././NuSMV-2.7.0-linux64/bin/NuSMV",
                "-dynamic",
                output_smv_file,
            ],
            capture_output=True,
            text=True,
        )
        self.finish_checking(result)

    def check_model(self) -> None:
        """run smv template and get counterexample"""
        self.change_status("Checking ...")

        def start_checking():
            result = subprocess.run(
                [
                    ".././NuSMV-2.7.0-linux64/bin/NuSMV",
                    "-dynamic",
                    output_smv_file,
                ],
                capture_output=True,
                text=True,
            )
            self.after(0, lambda: self.finish_checking(result))

        threading.Thread(target=start_checking).start()

    def finish_checking(self, result):
        """process model checking result"""
        if "is true" in result.stdout:
            print("The LTL property holds.")
            self.change_status("No counterexample found")
            self.point_check_status = False
        else:
            counterexample = result.stdout
            blocks = {}
            base = {}
            for line in counterexample.splitlines():
                match_base = re.search(r"base([X,Y,Z])\s*=\s*(-?\d+)", line)
                if match_base:
                    axis_base = match_base.group(1)
                    value_base = int(match_base.group(2))
                    base[axis_base] = value_base
                match = re.search(r"block_(\d+)\.([a-zA-Z])_end\s*=\s*(-?\d+)", line)
                if match:
                    idx = int(match.group(1))
                    axis = match.group(2)
                    value = int(match.group(3))
                    if idx not in blocks:
                        blocks[idx] = {}
                    blocks[idx][axis] = value
            result = [
                [block["x"], block["y"], block["z"]]
                for _, block in sorted(blocks.items())
            ]
            result.insert(0, [base["X"], base["Y"], base["Z"]])
            status = "Counterexample:"
            self.change_status(str(status + "\n" + str(result)))
            print(result)
            self.robot_structure = result
            self.plot.refresh(self.points)
            self.show_robot()
            self.point_check_status = True

    def get_goal_from_model(self):
        """Get goal point coordinates from current NuSMV model"""
        x, y, z = 0, 0, 0
        with open(output_smv_file, "r") as model:
            data = model.read()
            for line in data.splitlines():
                # checkX := 2;
                # check[X,Y,Z]\s*:=\s*(-?\d:)
                pattern = r"check[X,Y,Z]\s*:=*"
                match = re.search(pattern, line)
                if match:
                    prefix = match.group()
                    if "X" in prefix:
                        x = int(line.strip().removeprefix(prefix).strip(";"))
                        print(x, end=";")
                    if "Y" in prefix:
                        y = int(line.strip().removeprefix(prefix).strip(";"))
                        print(y, end=";")
                    if "Z" in prefix:
                        z = int(line.strip().removeprefix(prefix).strip(";"))
                        print(z)
        return x, y, z

    def change_goal_in_model(self, x, y, z) -> None:
        """Set goal point coordinates in NuSMV model"""
        with open(input_smv_file, "r") as model:
            lines = model.readlines()
        with open(output_smv_file, "w") as model:
            for line in lines:
                # check[X,Y,Z]\s*:=\s*(-?\d:)
                if re.search(r"checkX\s*:=\s*-?\d+;", line):
                    newX_line = f"checkX := {x};"
                    model.write(newX_line + "\n")
                elif re.search(r"checkY\s*:=\s*-?\d+;", line):
                    newY_line = f"checkY := {y};"
                    model.write(newY_line + "\n")
                elif re.search(r"checkZ\s*:=\s*-?\d+;", line):
                    newZ_line = f"checkZ := {z};"
                    model.write(newZ_line + "\n")
                else:
                    model.write(line)

    def check_reachability(self) -> None:
        """Add set of available points"""
        print("start checking points")
        for i in range(-60, 70, 20):
            for j in range(-60, 70, 20):
                for k in range(-60, 70, 20):
                    self.change_goal_in_model(i, j, k)
                    self.check_model_nonthreaded()
                    print(i, j, k, self.point_check_status)
                    if self.point_check_status:
                        self.plot.draw_point(i, j, k)

    def add_goal_point(self) -> None:
        """Add goal point to NuSMV model and to a graph"""
        x = int(self.goalX.get().strip())
        y = int(self.goalY.get().strip())
        z = int(self.goalZ.get().strip())
        self.plot.draw_target(x, y, z, f"Target:({x},{y},{z})")
        self.plot.refresh(self.points)
        self.change_goal_in_model(x, y, z)
        print("Target point set: x={0}, y={1}, z={2}".format(x, y, z))

    def read_robot_structure(self, xacro_path="./robot_example.xacro"):
        """
        Read robot structure from xacro file in "xacro_path"
        create:
        MAIN Module::VAR::blocks_sequence and angles
        MAIN module::DEFINE::endXYZ=end_blockXYZ
        MAIN module::ASSIGN::inits and next
        """
        # example xacro:
        # <xacro:block_ver block_number="11" parent_number="10"   x="0"   y="0"    z="0.5" />
        # example smv:

        # block_0 : BaseBlock(LEN,baseX,baseY,baseZ);
        # block_1 : block_rot_vert(yaw1, LEN, block_0.x_end, block_0.y_end, block_0.z_end, block_0.yawAbs);
        # block_2 : block_rot_hor(pitch2, LEN, block_1.x_end, block_1.y_end, block_1.z_end, block_1.yawAbs);
        structure_xacro = ""
        smv_var_blocks = "SMV structure: \n"
        smv_var_angles = "SMV angles: \n"
        end_block = None
        with open(xacro_path, "r") as xacro:
            for line in xacro.readlines():
                if "xacro:block_" in line:
                    structure_xacro += line
                    line = line.strip().lstrip("<xacro:")
                    block_type = line.split()[0][6]
                    attrs = dict(re.findall(r'(\w+)="([^"]+)"', line))
                    num = int(attrs["block_number"])
                    parent = int(attrs["parent_number"])
                    x = float(attrs["x"])
                    y = float(attrs["y"])
                    z = float(attrs["z"])
                    current_block = Block(num, block_type, x, y, z, parent)
                    smv_var_blocks += current_block.get_nusmv_block()
                    smv_var_angles += current_block.get_nusmv_angle()
                    end_block = current_block
        print(structure_xacro)
        print(smv_var_blocks)
        print(smv_var_angles)
        print(end_block.get_nusmv_endblock_definition)

        # ---------------------------------------------------------------------------


if __name__ == "__main__":
    App().mainloop()
