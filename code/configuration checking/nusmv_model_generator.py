from robot import Robot
import matplotlib.pyplot as plt


class RobotNusmvGenerator:
    """Class to generate NuSMV specification of a robot"""

    def __init__(
        self,
        robot: Robot,
        template_smv="./smv/robot_structure_template.smv",
        output_smv_path="./tmp/",
        isCollisionChecking=False,
    ):
        self.robot = robot
        self.isTargetPoint = False
        self.isTargetRegion = False
        self.isCollisionChecking = isCollisionChecking
        self.template = template_smv
        self.output_path = output_smv_path

    def set_target_region(self, X_range: str, Y_range: str, Z_range: str):
        """Set target range in form XYZ_range in form "-10..10" or {-10,-5,0,5,10}"""
        self.X_range = X_range
        self.Y_range = Y_range
        self.Z_range = Z_range
        self.isTargetRegion = True

    def set_target_point(self, checkX: int, checkY: int, checkZ: int):
        """Set target_point coordinates"""
        self.checkX = checkX
        self.checkY = checkY
        self.checkZ = checkZ
        self.isTargetPoint = True

    def get_specification(self):
        """Return specification based on target (EF for region, AG! for point"""
        condition = "& blocks_above_surface" if self.isCollisionChecking else ""
        if self.isTargetPoint and self.isTargetRegion:
            print("Error: Defined both target_point and target_region, choose one")
            raise AttributeError("define one of targets point or region")
        elif self.isTargetRegion:
            spec = f"CTLSPEC\n\t EF (endX_inside_limits & endY_inside_limits & endZ_inside_limits {
                condition
            })"
        elif self.isTargetPoint:
            spec = f"CTLSPEC\n\t AG !(endX_inside_limits & endY_inside_limits & endZ_inside_limits {
                condition
            })"
        else:
            print(
                "Warning: No specification generated, target point or region are not defined"
            )
            spec = ""
        return spec

    def get_target(self):
        """Return target variables NUSMV definition based on target region or target point"""
        target_region = ""
        target_point = ""
        if self.isTargetPoint and self.isTargetRegion:
            print("Error: Defined both target_point and target_region, choose one")
            raise AttributeError("define one of targets point or region")
        elif self.isTargetRegion:
            target_region = f"""
             FROZENVAR
                 checkX : {self.X_range};
                 checkY : {self.Y_range};
                 checkZ : {self.Z_range};
            """
        elif self.isTargetPoint:
            target_point = f"""
            checkX := {self.checkX};
            checkY := {self.checkY};
            checkZ := {self.checkZ};
            """
        else:
            raise AttributeError("define one of targets point or region")
        return target_point, target_region

    def get_collision_condition(self):
        """blocks_above_surface := ( block1.pz2>=0 &...);"""
        if self.isCollisionChecking:
            condition = "blocks_above_surface := (\n"
            delimiter = ""
            for name in self.robot.get_block_names():
                condition += f"{delimiter} {name}.pz2 >= 0\n"
                delimiter = "&"
            condition += ");"
            return condition
        else:
            return ""

    def get_main_module(self):
        """return main module template for with current target coordinates"""
        target_point, target_region = self.get_target()
        spec = self.get_specification()
        collision_condition = self.get_collision_condition()
        main = f"""MODULE main
        {target_region}
        VAR
        {self.robot.get_nusmv_robot_structure_part()}
        DEFINE
        {self.robot.get_nusmv_init_part()}
            base_px := 0;       base_py := 0;       base_pz := 0;
            base_xhx := 100;    base_xhy := 0;      base_xhz := 0;
            base_yhx := 0;      base_yhy := 100;    base_yhz := 0;
            base_zhx := 0;      base_zhy := 0;      base_zhz := 100;
        {self.robot.get_nusmv_end_part()}
            error := 1; -- +-1 (error=2) endX and endY coordinates error while checking reachability
            {target_point}
            endX_inside_limits := (endX <= (checkX + error) & endX >= (checkX - error));
            endY_inside_limits := (endY <= (checkY + error) & endY >= (checkY - error));
            endZ_inside_limits := (endZ <= (checkZ + error) & endZ >= (checkZ - error));
            \n{collision_condition}
            \n{spec}
            """
        return main

    def generate_from_template(self, name: str):
        """generate nusmv file from template using get_nusmv_main_module method"""
        with (
            open(self.template, "r") as template_file,
            open(self.output_path + name + ".smv", "w") as target_file,
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
                        new_main_module = self.get_main_module()
                        target_file.writelines(new_main_module)
                        copy_finished_flag = True
                else:
                    target_file.write(line)


if __name__ == "__main__":
    blocks_types = ["base", "yaw", "pitch", "pitch", "pitch", "yaw"]
    # blocks_len = [10, 20, 30, 30, 10, 20]
    # robot = Robot(blocks_types, blocks_len)
    # generator = RobotNusmvGenerator(robot)
    # generator.set_target_point(5, 5, 5)
    # generator.generate_from_template("project_robot")
