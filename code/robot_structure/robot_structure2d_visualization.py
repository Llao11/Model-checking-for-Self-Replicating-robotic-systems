import matplotlib.pyplot as plt
from typing import List, Tuple
from time import sleep


# Separate x and y coordinates
# x_coords, y_coords = zip(*points)

Point = Tuple[float, float]
# points = [(0, 0), (1, 2), (3, 1), (4, 4), (2, 3)]


class Plot:
    def __init__(self):
        self.fig, self.ax = plt.subplots()

    def draw_lines(self, pts: List[Point]) -> None:
        """Clear the axes and redraw the line connecting *pts*."""
        if not pts:
            return
        x, y = zip(*pts)
        self.ax.clear()
        self.ax.plot(x, y, marker="o", linewidth=2)
        self.ax.set_xlabel("X")
        self.ax.set_ylabel("Y")
        self.ax.set_title("Dynamic line plot – edit points at runtime")
        self.ax.grid(True)
        plt.pause(0.01)  # ensure canvas refreshes

    def add_point(self, pts: List[Point], x: float, y: float) -> None:
        """Append a new (x, y) tuple to *pts*."""
        pts.append((x, y))

    def update_point(self, pts: List[Point], index: int, x: float, y: float) -> None:
        """Replace the point at *index* with a new (x, y) pair."""
        if 0 <= index < len(pts):
            pts[index] = (x, y)
        else:
            raise IndexError("Point index out of range")

    def update(self, new_pts):
        xs, ys = zip(*new_pts)
        # line.set_data(xs, ys)  # 1. mutate
        self.ax.relim()
        self.ax.autoscale_view()
        self.fig.canvas.draw_idle()  # 2. ask for redraw
        plt.pause(0.01)

    def create_plot(self) -> None:
        points: List[Point] = [
            # (0, 0),
            # (1, 1),
            # (1, 2),
        ]
        self.draw_lines(points)

        self.add_point(points, 5, 2)  # add a new point
        self.draw_lines(points)  # refresh plot

        print("Close the window to end the program.")
        plt.show(block=True)

        sleep(2)

        plt.show(block=False)
        self.update_point(pts=points, index=2, x=1, y=1)  # move first point
        self.draw_lines(points)  # refresh plot


if __name__ == "__main__":

    plot = Plot()
    plot.create_plot()
