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

from typing import List, Tuple, Optional

import matplotlib

# Use the TkAgg backend so Matplotlib can render inside a Tk widget
matplotlib.use("TkAgg")  # must be set *before* importing pyplot
import matplotlib.pyplot as plt  # noqa: E402  pylint: disable=wrong-import-position

# ---------------------------------------------------------------------------
# Data model helper
Point3D = [float, float, float]


# ---------------------------------------------------------------------------
# Matplotlib side – no Tk code here; completely reusable in other contexts
class Plot3DBackend:
    """Encapsulates a single 3‑D figure + axes and exposes draw helpers."""

    def __init__(self) -> None:
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

    def add_point(self, x: float, y: float, z: float, label: str | None = None) -> None:
        self.ax.scatter([x], [y], [z], s=40, c="red")
        if label:
            self.ax.text(x, y, z, label, fontsize=8, ha="left", va="bottom")
        self.ax.auto_scale_xyz([x], [y], [z])  # keep axes nicely scaled
        self._apply_limits()  # re-apply any user limits
        self.fig.canvas.draw_idle()

    def add_point_to_list(
        self, pts: List[Point3D], x: float, y: float, z: float
    ) -> None:
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
