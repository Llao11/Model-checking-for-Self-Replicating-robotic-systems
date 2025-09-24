from robot import Robot
from itertools import product
from datetime import datetime, timezone
import subprocess
import threading
import re


class Configuration_checking:
    def __init__(self, checkX, checkY, checkZ, length, block_types):
        self.template = ("./smv/robot_structure_template.smv",)
        self.path = "./tmp/"
        self.checkX = checkX
        self.checkY = checkY
        self.checkZ = checkZ
        self.length = length
        self.block_types = block_types
        self.num_of_combinations = (len(self.block_types)) ** (self.length - 1)
        self.combinations = self.get_all_combinations(self.length, self.block_types)

    def get_nusmv_main_module(self, robot: Robot, checkX, checkY, checkZ):
        return f"""MODULE main
        VAR
        {robot.get_nusmv_robot_structure_part()}
        DEFINE

        {robot.get_nusmv_init_part()}

            -- constant base pose and world-aligned basis (×100)
            base_px := 0;       base_py := 0;       base_pz := 0;

            base_xhx := 100;    base_xhy := 0;      base_xhz := 0;
            base_yhx := 0;      base_yhy := 100;    base_yhz := 0;
            base_zhx := 0;      base_zhy := 0;      base_zhz := 100;
        {robot.get_nusmv_end_part()}

        --Error calculation
        -- 2D CASE: y - up
            -- discretization_angle := 10;
            -- error := LEN*sin10 = 10 * 0,173 = 1,73;

            error := 1; -- +-1 (error=2) endX and endY coordinates error while checking reachability
            checkX := {checkX};
            checkY := {checkY};
            checkZ := {checkZ};
            endX_inside_limits := (endX <= (checkX + error) & endX >= (checkX - error));
            endY_inside_limits := (endY <= (checkY + error) & endY >= (checkY - error));
            endZ_inside_limits := (endZ <= (checkZ + error) & endZ >= (checkZ - error));"""

    def create_nusmv_from_template(
        self,
        name: str,
        robot: Robot,
        path="./tmp/",
        template="./smv/robot_structure_template.smv",
    ):
        """creates nusmv file from template using get_nusmv_main_module method"""
        with (
            open(template, "r") as template_file,
            open(path + name + ".smv", "w") as target_file,
        ):
            lines = template_file.readlines()
            start_line = "MODULE main"
            end_line = "--main end"
            copy_new_flag = False
            copy_finished_flag = False
            # if (
            #     start_line not in template_file.read()
            #     or end_line not in template_file.read()
            # ):
            #     raise Exception(
            #         f'Template does not have  "{start_line}" or "{end_line}" lines'
            #     )
            # else:
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
                        new_main_module = self.get_nusmv_main_module(
                            robot, self.checkX, self.checkY, self.checkZ
                        )
                        target_file.writelines(new_main_module)
                        copy_finished_flag = True
                else:
                    target_file.write(line)

    def get_all_combinations(self, length, types: set):
        length = length - 1
        combinations = list(product(types, repeat=length))
        combinations = [["base"] + list(combination) for combination in combinations]
        return combinations

    def check_model(self, name) -> None:
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
        self.result_processing(result, name)

    # def check_model(name) -> None:
    #     """run smv template and get counterexample"""
    #     output_smv_file = path + name
    #
    #     def start_checking():
    #         result = subprocess.run(
    #             [
    #                 ".././NuSMV-2.7.0-linux64/bin/NuSMV",
    #                 "-dynamic",
    #                 output_smv_file,
    #             ],
    #             capture_output=True,
    #             text=True,
    #         )
    # after(0, lambda: self.finish_checking(result))
    # threading.Thread(target=start_checking).start()

    def result_processing(self, result, name):
        """process model checking result"""
        if "is true" in result.stdout:
            print(
                f"{self.num}/{self.num_of_combinations}:{name}:\tnot reachable", end=""
            )
        else:
            print(f"{self.num}/{self.num_of_combinations}:{name}:\treachable", end="")
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
        print(f"Checking for {self.checkX=}, {self.checkY=}, {self.checkZ=}")
        print(f"{self.length=}")
        print(f"number of combinations:{self.num_of_combinations}")
        self.num = 0
        for configuration in self.combinations:
            self.num += 1
            start_time = datetime.now(timezone.utc)
            robot = Robot(configuration)
            self.create_nusmv_from_template(robot.get_configuration_name(), robot)
            self.check_model(robot.get_configuration_name())

            elapsed_time = datetime.now(timezone.utc) - start_time
            print(f"\t[{elapsed_time.total_seconds()} sec]")


if __name__ == "__main__":
    checkX = 10
    checkY = 10
    checkZ = 10
    length = 6
    block_types = {"yaw", "pitch"}
    config_checking = Configuration_checking(
        checkX, checkY, checkZ, length, block_types
    )
    config_checking.start_checking_combinations()
