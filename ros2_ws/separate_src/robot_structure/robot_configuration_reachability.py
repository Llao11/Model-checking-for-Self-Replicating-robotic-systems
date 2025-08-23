from __future__ import annotations, print_function

import random
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

# Tkinter GUI wrapper


class App(tk.Tk):
    def __init__(self) -> None:
        """Create GUI"""
        super().__init__()
        self.title("Robot 3D configuration")
        self.geometry("900x700")

        # Initial robot structure
        self.robot_structure = [[0, 0, 0], [1, 2, 1], [2, 3, 0]]
        # Variables for coordinates input
        self.coordinates_vars: dict[str, tk.StringVar] = {}

        # main layout (grid)
        self.grid_rowconfigure(0, weight=1)  # canvas row grows
        self.grid_columnconfigure(0, weight=1)

        # Matplotlib canvas inside Tk
        # Backend plot
        self.plot = Plot3D()
        self.points: List[Point3D] = []
        self.canvas = FigureCanvasTkAgg(self.plot.fig, master=self)
        self.canvas.draw()
        self.canvas_widget = self.canvas.get_tk_widget()
        self.canvas_widget.grid(row=0, column=0, sticky="nsew")

        # Control panel --------------------------------------------------
        self.ctrl = tk.Frame(self)
        self.ctrl.grid(row=1, column=0, sticky="ew", pady=5)
        self.ctrl.columnconfigure((0, 1, 2, 3, 4, 5), weight=1)

        tk.Button(self.ctrl, text="Show Robot", command=self.show_robot).grid(
            row=0, column=0, padx=5, sticky="w"
        )
        tk.Button(self.ctrl, text="Add Random Point", command=self.add_random).grid(
            row=0, column=1, padx=5, sticky="w"
        )
        tk.Button(self.ctrl, text="Quit", command=self.destroy).grid(
            row=0, column=3, padx=5, sticky="e"
        )
        # Initial blank plot
        # self.backend.draw_lines(self.points)

    def show_coord_change(self, index: int):
        """show ui to change the robot coordinates"""
        # Axis‑limit widgets --------------------------------------------
        coordinates_frame = tk.Frame(self.ctrl)
        coordinates_frame.grid(row=index + 1, column=0, columnspan=2, padx=10)
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
        """moves block number "index" according to inputed values"""
        x = self.parse_coordinates("X" + str(index))
        y = self.parse_coordinates("Y" + str(index))
        z = self.parse_coordinates("Z" + str(index))
        # Convert pairs where at least one bound was provided; else None
        self.plot.update_point(self.points, index, x, y, z)
        self.plot.refresh(self.points)

    def show_robot(self) -> None:
        """Render a little 3‑D L‑shaped robot made of 2 points."""
        self.points: List[Point3D] = []
        for idx, pt in enumerate(self.robot_structure):
            self.plot.add_point_with_line(self.points, *pt)
            self.show_coord_change(idx)
        self.plot.refresh(self.points)

    def add_target_point(self, x, y, z) -> None:
        """add target point to a plot"""
        self.plot.draw_point(x, y, z, "as")
        # self.plot.add_point_with_line(self.points, *new_pt)
        self.plot.refresh(self.points)

    def add_random(self) -> None:
        """add random point to a plot"""
        x = float(random.uniform(0, 2))
        y = float(random.uniform(0, 2))
        z = float(random.uniform(0, 2))
        self.plot.draw_point(x, y, z, "as")
        # self.plot.add_point_with_line(self.points, *new_pt)
        self.plot.refresh(self.points)


# ---------------------------------------------------------------------------
if __name__ == "__main__":
    App().mainloop()
