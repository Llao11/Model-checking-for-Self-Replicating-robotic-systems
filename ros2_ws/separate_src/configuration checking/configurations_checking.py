from robot import Robot
from itertools import product
from datetime import datetime, timezone
import subprocess
import statistics
import re
from counterexample import Counterexample

import matplotlib.pyplot as plt


class Configuration_checking:
    def __init__(
        self,
        length,
        block_types,
        template_smv="./smv/robot_structure_template.smv",
        output_smv_path="./tmp/",
    ):
        self.isTargetPoint = False
        self.isTargetRegion = False
        self.template = template_smv
        self.path = output_smv_path
        self.length = length
        self.block_types = block_types
        self.num_of_combinations = (len(self.block_types)) ** (self.length - 1)
        self.combinations = self.get_all_combinations(self.length, self.block_types)

    def set_target_region(self, X_start, X_end, Y_start, Y_end, Z_start, Z_end):
        self.X_start = X_start
        self.Y_start = Y_start
        self.Z_start = Z_start
        self.X_end = X_end
        self.Y_end = Y_end
        self.Z_end = Z_end
        self.isTargetRegion = True

    def set_target_point(self, checkX, checkY, checkZ):
        self.checkX = checkX
        self.checkY = checkY
        self.checkZ = checkZ
        self.isTargetPoint = True

    def get_main_module(self, robot: Robot):
        """return main module template for with current target coordinates"""
        target_region = ""
        target_point = ""
        if self.isTargetPoint and self.isTargetRegion:
            print("Error: Defined both target_point and target_region, choose one")
            return None
        elif self.isTargetRegion:
            target_region = """
             FROZENVAR
                 checkX : {-10, -5, 0, 5, 10};
                 checkY : {-10, -5, 0, 5, 10};
                 checkZ : {0, 5, 10};
            """
            spec = """
            CTLSPEC
                EF (endX_inside_limits & endY_inside_limits & endZ_inside_limits )
            """
            # target_region = f"""
            #  FROZENVAR
            #      checkX : {self.X_start}..{self.X_end};
            #      checkY : {self.Y_start}..{self.Y_end};
            #      checkZ : {self.Z_start}..{self.Z_end};
            # """
        elif self.isTargetPoint:
            target_point = f"""
            checkX := {self.checkX};
            checkY := {self.checkY};
            checkZ := {self.checkZ};
            """
            spec = """
            CTLSPEC
                EF !(endX_inside_limits & endY_inside_limits & endZ_inside_limits )
            """
        else:
            print("Error: target point or region not defined")
            return None
        main = f"""MODULE main
        {target_region}
        VAR
        {robot.get_nusmv_robot_structure_part()}
        DEFINE
        {robot.get_nusmv_init_part()}
            base_px := 0;       base_py := 0;       base_pz := 0;
            base_xhx := 100;    base_xhy := 0;      base_xhz := 0;
            base_yhx := 0;      base_yhy := 100;    base_yhz := 0;
            base_zhx := 0;      base_zhy := 0;      base_zhz := 100;
        {robot.get_nusmv_end_part()}
            error := 1; -- +-1 (error=2) endX and endY coordinates error while checking reachability
            {target_point}
            endX_inside_limits := (endX <= (checkX + error) & endX >= (checkX - error));
            endY_inside_limits := (endY <= (checkY + error) & endY >= (checkY - error));
            endZ_inside_limits := (endZ <= (checkZ + error) & endZ >= (checkZ - error));
            {spec}
            """
        # print(main)
        return main

    def generate_nusmv_from_template(
        self,
        name: str,
        robot: Robot,
        path="./tmp/",
        template="./smv/robot_structure_template.smv",
    ):
        """generate nusmv file from template using get_nusmv_main_module method"""
        with (
            open(template, "r") as template_file,
            open(path + name + ".smv", "w") as target_file,
        ):
            lines = template_file.readlines()
            start_line = "MODULE main"
            end_line = "--main end"
            copy_new_flag = False
            copy_finished_flag = False
            for line in lines:
                if start_line in line:
                    copy_new_flag = True
                    # print(f"found start:{line} start copy new")
                if end_line in line:
                    copy_new_flag = False
                    # print(f"found end:{line} stop copy new")
                if copy_new_flag:
                    if copy_finished_flag:
                        continue
                    else:
                        new_main_module = self.get_main_module(robot)
                        target_file.writelines(new_main_module)
                        copy_finished_flag = True
                else:
                    target_file.write(line)

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

    def result_processing(self, result, name):
        """process model checking result"""
        if "is true" in result.stdout:
            result = False if self.isTargetPoint else True
        else:
            result = True if self.isTargetPoint else False
        not_word = "" if result else "not"
        print(
            f"{self.num}/{self.num_of_combinations}:{name}:\t{not_word} reachable",
            end="",
        )
        return result
        # counterexample = result.stdout
        # parse_counterexample(counterexample)

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
        if self.isTargetPoint and self.isTargetRegion:
            print("Error: Defined both target_point and target_region, choose one")
        elif self.isTargetRegion:
            print(
                f"Checking {self.X_start=}..{self.X_end}, {self.Y_start=}..{
                    self.Y_end
                }, {self.Z_start=}..{self.Z_end}"
            )
        elif self.isTargetPoint:
            print(f"Checking {self.checkX=}, {self.checkY=}, {self.checkZ=}")
        else:
            print("Error: target point or region not defined")
        print(f"{self.length=}")
        print(f"number of combinations:{self.num_of_combinations}")
        self.num = 0
        for configuration in self.combinations:
            self.num += 1
            start_time = datetime.now(timezone.utc)
            robot = Robot(configuration)
            config_name = robot.get_configuration_name()
            configs.append(config_name)
            self.generate_nusmv_from_template(config_name, robot)
            result = self.check_model(config_name)
            isReachable = self.result_processing(result, config_name)
            elapsed_time = datetime.now(timezone.utc) - start_time
            checking_times.append(elapsed_time.total_seconds())
            res = "reachable" if isReachable else "not reachable"
            results.append(res)
            print(f"\t[{elapsed_time.total_seconds()} sec]")
            output_result_file = self.path + config_name + "_result.txt"
            if self.isTargetPoint:
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
    list_of_times = []
    for length in range(2, 7):
        robot_size.append(length)
        config_checking = Configuration_checking(length, block_types)
        # config_checking.set_target_point(checkX, checkY, checkZ)
        config_checking.set_target_region(-5, 5, -5, 5, 0, 5)
        config_names, times, res = config_checking.start_checking_combinations()
        results.append(res)
        list_of_times.append(times)
        means.append(statistics.mean(times))
        std_dev = statistics.stdev(times)
    with open("time_size_res.txt", "a") as file:
        file.write(str(config_names))
        file.write(str(means))
        file.write(str(results))
    plt.figure(figsize=(8, 6))
    plt.plot(robot_size, means, marker="o", linestyle="-", color="b")
    plt.xlabel("Robot Size")
    plt.ylabel("Average checking time (seconds)")
    plt.title("Checking time changing with robot size")
    plt.grid(True)
    save_path = "Time_size_plot.png"
    plt.savefig(save_path, dpi=300)
    plt.show()
