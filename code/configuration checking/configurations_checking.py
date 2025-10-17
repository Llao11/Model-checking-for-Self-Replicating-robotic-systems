from robot import Robot
from itertools import product
from datetime import datetime, timezone
import subprocess
import statistics
import re
from counterexample import Counterexample
from nusmv_model_generator import RobotNusmvGenerator

import matplotlib.pyplot as plt


class Configuration_checking:
    def __init__(
        self,
        length,
        block_types,
        target: list,
        isTargetRegion=False,
        template_smv="./smv/robot_structure_template.smv",
        output_smv_path="./tmp/",
    ):
        self.template = template_smv
        self.path = output_smv_path
        self.length = length
        self.block_types = block_types
        self.target = target
        self.isTargetRegion = isTargetRegion
        self.num_of_combinations = (len(self.block_types)) ** (self.length - 1)
        self.combinations = self.get_all_combinations(self.length, self.block_types)

    def set_target(self, target: list[str], generator):
        if len(target) == 3:
            if self.isTargetRegion:
                generator.set_target_region(
                    self.target[0], self.target[1], self.target[2]
                )
            else:
                generator.set_target_point(
                    int(self.target[0]), int(self.target[1]), int(self.target[2])
                )
        else:
            raise ValueError(
                "Target have to be defined in form:\n\
                '5','6','7'\n '-5..5', '-6..6','-7..7'\n\
                or\n'{-5,0,5}', '{-5,0,5}' '0,5'"
            )

    def get_all_combinations(self, length, types: set):
        length = length - 1
        combinations = list(product(types, repeat=length))
        combinations = [["base"] + list(combination) for combination in combinations]
        return combinations

    def check_model(self, name):
        """run smv template and get counterexample"""
        output_smv_file = self.path + name + ".smv"
        result = subprocess.run(
            [
                ".././NuSMV-2.7.0-linux64/bin/NuSMV",
                "-dynamic",
                output_smv_file,
            ],
            capture_output=True,
            text=True,
        )
        return result

    def result_processing(self, result, name, generator):
        """process model checking result"""
        if "is true" in result.stdout:
            result = False if generator.isTargetPoint else True
        else:
            result = True if generator.isTargetPoint else False
        not_word = "" if result else "not"
        print(
            f"{self.num}/{self.num_of_combinations}:{name}:\t{not_word} reachable",
            end="",
        )
        return result

    def parse_counterexample(self, counterexample: str):
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
            [block["x"], block["y"], block["z"]] for _, block in sorted(blocks.items())
        ]
        result.insert(0, [base["X"], base["Y"], base["Z"]])

    def start_checking_combinations(self):
        """the main part checks combinations of blocks one by one"""
        checking_times = []
        results = []
        configs = []
        print(f"{self.length=}")
        print(f"number of combinations:{self.num_of_combinations}")
        self.num = 0
        for configuration in self.combinations:
            self.num += 1
            start_time = datetime.now(timezone.utc)
            robot = Robot(configuration)
            generator = RobotNusmvGenerator(robot)
            self.set_target(self.target, generator)
            config_name = robot.get_configuration_name()
            configs.append(config_name)
            generator.generate_from_template(config_name)
            result = self.check_model(config_name)
            isReachable = self.result_processing(result, config_name, generator)
            elapsed_time = datetime.now(timezone.utc) - start_time
            checking_times.append(elapsed_time.total_seconds())
            res = "reachable" if isReachable else "not reachable"
            results.append(res)
            print(f"\t[{elapsed_time.total_seconds()} sec]")
            output_result_file = self.path + config_name + "_result.txt"
            if generator.isTargetPoint:
                stdout = result.stdout
                with open(output_result_file, "w") as result_file:
                    if "is true" in result.stdout:
                        result_file.write("The LTL property holds.")
                    else:
                        result_file.write(stdout)
                        with open(output_result_file) as trace:
                            counterexample = Counterexample(
                                trace.read(), robot_len=self.length
                            )
                        graph_path = self.path + config_name + ".png"
                        counterexample.plot_trace(-1, save_path=graph_path)
        return configs, checking_times, results


if __name__ == "__main__":
    block_types = {"yaw", "pitch"}
    means = []
    robot_size = []
    config_names = []
    results = []
    # target = ["5", "5", "10"]
    target = ["{-10,10}", "{-10,10}", "{0,10}"]
    list_of_times = []
    for length in range(2, 8):
        robot_size.append(length)
        config_checking = Configuration_checking(
            length, block_types, target, isTargetRegion=True
        )
        # config_checking.set_target(target)
        config_names, times, res = config_checking.start_checking_combinations()
        results.append(res)
        list_of_times.append(times)
        means.append(statistics.mean(times))
        std_dev = statistics.stdev(times)
    # with open("time_size_res.txt", "a") as file:
    #     file.write(str(config_names))
    #     file.write(str(means))
    #     file.write(str(results))
    plt.figure(figsize=(8, 6))
    plt.plot(robot_size, means, marker="o", linestyle="-", color="b")
    plt.xlabel("Robot Size")
    plt.ylabel("Average checking time (seconds)")
    plt.title("Checking time changing with robot size")
    plt.grid(True)
    save_path = "Time_size_plot.png"
    plt.savefig(save_path, dpi=300)
    plt.show()
