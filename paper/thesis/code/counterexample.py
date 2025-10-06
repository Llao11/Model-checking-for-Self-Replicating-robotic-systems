import subprocess
import matplotlib.pyplot as plt


class Counterexample:
    """Class to parse nusmv counterexample, retreive trace states,
    filter variables and represent traces as graphs"""

    def __init__(self, nusmv_result: str):
        self.nusmv_result = nusmv_result
        self.robot_len = 5

    def plot_lines(self, ax, points):
        """
        Plot a list of 3D points connected with lines and save the figure.
        """
        xs, ys, zs = zip(*points)
        ax.plot(xs, ys, zs, marker="o", linestyle="-")
        for i, (x, y, z) in enumerate(points):
            ax.text(x, y, z, f"{i}", fontsize=9, color="black")

    def plot_trace(self, robot_step=0, save_path="3d_plot.png"):
        """Plot a end-effector trace from counterexample."""
        end_coordinates = ["endX", "endY", "endZ"]
        trace = self.filter_variables(end_coordinates)
        fig = plt.figure()
        ax = fig.add_subplot(111, projection="3d")
        ax.set_xlim(-20, 20)  # X axis range
        ax.set_ylim(-20, 20)  # Y axis range
        ax.set_zlim(0, 40)  # Z axis range
        ax.set_box_aspect([1, 1, 1])
        self.plot_lines(ax, trace)
        robot_pos0 = self.get_robot_blocks(self.robot_len)[robot_step]
        self.plot_lines(ax, robot_pos0)
        ax.set_xlabel("X")
        ax.set_ylabel("Y")
        ax.set_zlabel("Z")
        plt.savefig(save_path, dpi=300)
        plt.show()
        plt.close(fig)  # Close the figure to free memory
        print(f"3D plot saved to {save_path}")

    def filter_variables(self, vars: list[str]) -> list[list[int]] | None:
        """returns the list of steps, each step is a list of states with defined variable"""
        all_steps = [vars]
        states_list = self.nusmv_result.split("-> State")
        states_list = states_list[1:]
        previous_step_values = vars[:]
        for state in states_list:
            step_values = previous_step_values
            for line in state.split(sep="\n"):
                for i, var in enumerate(vars):
                    if var in line:
                        value = line.split("=")[1]
                        step_values[i] = value
            all_steps.append(step_values)
            previous_step_values = step_values[:]
        try:
            all_steps = [[int(variable) for variable in step] for step in all_steps[1:]]
            return all_steps
        except ValueError:
            print(
                "Error while str -> int transformation, check if all elements are int:"
            )
            return None

    def get_robot_blocks(self, robot_size):
        """Return robot blocks coordinates for each step."""
        blocks = []
        steps = []
        # get changin by blocks by steps [[changing block0], [changing block1] ...]
        for i in range(robot_size):
            blocks_coordinates = [
                f"block{i}.px2",
                f"block{i}.py2",
                f"block{i}.pz2",
            ]
            block_steps = self.filter_variables(blocks_coordinates)
            blocks.append(block_steps)
        # transpose the matrix (blocks to steps)
        for i in range(len(blocks[0])):
            step = []
            for j in range(len(blocks)):
                step.append(blocks[j][i])
            steps.append(step)
        print("Robot blocks by steps:")
        self.print_steps(steps)
        return steps

    def get_angles(
        self, angle_vars=[".yaw", ".pitch"], angle_descritization=10
    ) -> list[list[int]] | None:
        """returns the list of states with angles in degrees for each step"""
        all_steps = self.filter_variables(angle_vars)
        all_steps = [
            [angle * angle_descritization for angle in step] for step in all_steps
        ]
        return all_steps

    def print_steps(self, all_steps):
        """Print list"""
        for i in all_steps:
            print(i)

    def get_target_coordinates(
        self, target_coordinates=["checkX", "checkY", "checkZ"]
    ) -> list[list[int]] | None:
        """returns target coordinates values"""
        return self.filter_variables(target_coordinates)

    def get_end_coordinates(
        self, end_coordinates=["endX", "endY", "endZ"]
    ) -> list[list[int]] | None:
        """list of end-effector coordinates by steps"""
        return self.filter_variables(end_coordinates)

    @staticmethod
    def run_nusmv_file(smv_file="./smv/robot_structure.smv"):
        """runs smv file and if there is a counterexample store the result in file"""
        nusmv_path = ".././NuSMV-2.7.0-linux64/bin/NuSMV"
        file = smv_file
        output_file = "result.txt"
        result = subprocess.run(
            [
                nusmv_path,
                "-dynamic",
                file,
            ],
            capture_output=True,
            text=True,
        )
        stdout = result.stdout
        if "is true" in result.stdout:
            print("The LTL property holds.")
        else:
            with open(output_file, "w") as result_file:
                print("Generating counterexample..")
                result_file.write(stdout)
