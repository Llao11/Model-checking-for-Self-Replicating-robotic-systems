import subprocess


class Counterexample:
    def __init__(
        self, nusmv_result: str, vars=[".yaw", ".pitch"], angle_descritization=10
    ):
        self.nusmv_result = nusmv_result
        self.trace_vars = vars
        self.angle_descritization = angle_descritization

    def filter_variables(self) -> list[list[int]]:
        """
        get list of states with angles for each step
        """
        all_steps = [self.trace_vars]
        states_list = self.nusmv_result.split("-> State")
        states_list = states_list[1:]
        previous_step_values = self.trace_vars[:]
        for state in states_list:
            step_values = previous_step_values
            for line in state.split(sep="\n"):
                for i, var in enumerate(self.trace_vars):
                    if var in line:
                        value = line.split("=")[1]
                        step_values[i] = value
            all_steps.append(step_values)
            previous_step_values = step_values[:]
        try:
            all_steps = [
                [int(angle) * self.angle_descritization for angle in step]
                for step in all_steps[1:-1]
            ]
        except ValueError:
            print(
                "Error while str -> int transformation, check if all elements are int:"
            )
            self.print_steps(all_steps)
        return all_steps

    def print_steps(self, all_steps: list[list[int]]):
        for i in all_steps:
            print(i)

    @staticmethod
    def run_nusmv_file(smv_file="./smv/robot_structure.smv"):
        """runs smv file"""
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


if __name__ == "__main__":
    # Counterexample.run_nusmv_file()
    output_file = "result.txt"
    vars = ["block1.yaw", "block2.pitch", "block3.pitch"]
    with open(output_file) as trace:
        counter1 = Counterexample(trace.read(), vars)
        vars = counter1.filter_variables()
        counter1.print_steps(vars)
