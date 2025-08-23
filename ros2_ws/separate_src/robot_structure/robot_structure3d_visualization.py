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

from __future__ import annotations, print_function

import random
import tkinter as tk
from typing import List, Tuple, Optional

import matplotlib

# Use the TkAgg backend so Matplotlib can render inside a Tk widget
matplotlib.use("TkAgg")  # must be set *before* importing pyplot
import matplotlib.pyplot as plt  # noqa: E402  pylint: disable=wrong-import-position
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg  # noqa: E402
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 – required for 3‑D backend

# ---------------------------------------------------------------------------
# Data model helper
Point3D = [float, float, float]


# ---------------------------------------------------------------------------
# Matplotlib side – no Tk code here; completely reusable in other contexts
class Plot3DBackend:
    """Encapsulates a single 3‑D figure + axes and exposes draw helpers."""

    def __init__(self) -> None:
        """create plot"""
        self.fig = plt.Figure(figsize=(5, 4), dpi=100)
        self.ax = self.fig.add_subplot(111, projection="3d")
        self._line = None  # will hold the Line3D artist once created
        self._stored_limits: dict[str, Optional[Tuple[float, float]]] = {
            "x": None,
            "y": None,
            "z": None,
        }
        self._style_axes()
        self._text_labels: List = []

    # --------------------------- private helpers -------------------------
    def _style_axes(self) -> None:
        self.ax.set_xlabel("X")
        self.ax.set_ylabel("Y")
        self.ax.set_zlabel("Z")
        self.ax.set_title("Dynamic 3‑D line plot – edit points at runtime")
        self.ax.grid(True)

    def _apply_limits(self) -> None:
        """Re‑apply user‑defined limits if they exist."""
        if self._stored_limits["x"]:
            self.ax.set_xlim(*self._stored_limits["x"])
        if self._stored_limits["y"]:
            self.ax.set_ylim(*self._stored_limits["y"])
        if self._stored_limits["z"]:
            self.ax.set_zlim(*self._stored_limits["z"])

    # --------------------------- public API ------------------------------
    def set_limits(
        self,
        xlim: Optional[Tuple[float, float]] = None,
        ylim: Optional[Tuple[float, float]] = None,
        zlim: Optional[Tuple[float, float]] = None,
    ) -> None:
        """Remember axis limits; pass *None* to leave an axis autoscaling."""
        self._stored_limits.update({"x": xlim, "y": ylim, "z": zlim})
        self._apply_limits()
        self.fig.canvas.draw_idle()

    def _create_label(self, pts: List[Point3D]):
        for label in self._text_labels:
            label.remove()
        self._text_labels.clear()
        for idx, point in enumerate(pts):
            x = point[0]
            y = point[1]
            z = point[2]
            text = f"{idx} ({x},{y},{z})"

            LABEL_KW = dict(fontsize=8, color="black")
            self._text_labels.append(self.ax.text(x, y, z, text, **LABEL_KW))

    def draw_lines(self, pts: List[Point3D]) -> None:
        """Clear the axes and redraw the poly‑line through *pts*."""
        self.ax.clear()
        self._style_axes()

        if pts:
            x, y, z = zip(*pts)
            (self._line,) = self.ax.plot(x, y, z, marker="o", linewidth=2)
            # *** real autoscaling for 3‑D ***
            self.ax.auto_scale_xyz(x, y, z)

        # Re‑apply manual limits last so they override autoscale
        self._create_label(pts)
        self._apply_limits()
        self.fig.canvas.draw_idle()

    def add_point(self, pts: List[Point3D], x: float, y: float, z: float) -> None:
        pts.append((x, y, z))

    def update_point(
        self, pts: List[Point3D], index: int, x: float, y: float, z: float
    ) -> None:
        if 0 <= index < len(pts):
            pts[index] = (x, y, z)
        else:
            raise IndexError("Point index out of range")

    def refresh(self, pts: List[Point3D]) -> None:
        """Efficiently update the existing Line3D artist in‑place."""
        if not pts or self._line is None:
            self.draw_lines(pts)  # falls back to full redraw
            return

        x, y, z = zip(*pts)
        self._line.set_data_3d(x, y, z)

        # *** dedicated 3‑D autoscaler ***
        self.ax.auto_scale_xyz(x, y, z)
        self._create_label(pts)
        # Re‑apply any user‑pinned limits so they win over autoscale
        self._apply_limits()
        self.fig.canvas.draw_idle()


# ---------------------------------------------------------------------------
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
        self.backend = Plot3DBackend()
        self.points: List[Point3D] = []
        self.canvas = FigureCanvasTkAgg(self.backend.fig, master=self)
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
        x = self.parse_coordinates("X" + str(index))
        y = self.parse_coordinates("Y" + str(index))
        z = self.parse_coordinates("Z" + str(index))
        # Convert pairs where at least one bound was provided; else None
        self.backend.update_point(self.points, index, x, y, z)
        self.backend.refresh(self.points)

    def show_robot(self) -> None:
        """Render a little 3‑D L‑shaped robot made of 2 points."""
        for idx, pt in enumerate(self.robot_structure):
            self.backend.add_point(self.points, *pt)
            self.show_coord_change(idx)
        self.backend.refresh(self.points)

    def add_random(self) -> None:
        """add random point to a plot"""
        new_pt = (
            random.uniform(0, 5),
            random.uniform(0, 5),
            random.uniform(0, 5),
        )
        self.backend.add_point(self.points, *new_pt)
        self.backend.refresh(self.points)


# ---------------------------------------------------------------------------
if __name__ == "__main__":
    App().mainloop()
