"""
General robot class to generate structure combinations,
translate structure to NuSMV
"""

from block import Block
from itertools import product


class Robot:
    def __init__(self, block_sequence: list[str]):
        parent_block_num = None
        self.structure = []
        for num, block_type in enumerate(block_sequence):
            block = Block(num, block_type, parent_block_num)
            self.structure.append(block)
            parent_block_num = num
        self.last_block = self.structure[-1]

    def __repr__(self):
        structure = ""
        for block in self.structure:
            structure += f"{block}\n"
        return structure

    def get_nusmv_initialization(self):
        init = ""
        for block in self.structure:
            init += f"{block.get_nusmv_initline()}"
        return init

    def get_nusmv_end_block(self):
        return self.last_block.get_nusmv_endblock()

    def get_nusmv_robot_structure(self):
        """block0: block_base(base_px, base_py, base_pz,
                            base_xhx, base_xhy, base_xhz,
                            base_yhx, base_yhy, base_yhz,
                            base_zhx, base_zhy, base_zhz,
                            L1);
        block1: block_yaw(block0.px, block0.py, block0.pz,
                            block0.xhx, block0.xhy, block0.xhz,
                            block0.yhx, block0.yhy, block0.yhz,
                            block0.zhx, block0.zhy, block0.zhz,
                            L1, yaw1 );
        block2: block_pitch(block1.px2, block1.py2, block1.pz2,
                          block1.xhx2, block1.xhy2, block1.xhz2,
                          block1.yhx2, block1.yhy2, block1.yhz2,
                          block1.zhx2, block1.zhy2, block1.zhz2,
                          L2, pitch2);
        block3: block_pitch(block2.px2, block2.py2, block2.pz2,
                          block2.xhx2, block2.xhy2, block2.xhz2,
                          block2.yhx2, block2.yhy2, block2.yhz2,
                          block2.zhx2, block2.zhy2, block2.zhz2,
                          L3, pitch3);"""
        structure = ""
        for block in self.structure:
            structure += block.get_nusmv_block() + "\n"
        return structure

    def get_nusmv_main(self):
        return f"""MODULE main
VAR
{self.get_nusmv_robot_structure()}
DEFINE

{self.get_nusmv_initialization()}

    -- constant base pose and world-aligned basis (×100)
    base_px := 0;       base_py := 0;       base_pz := 0;

    base_xhx := 100;    base_xhy := 0;      base_xhz := 0;
    base_yhx := 0;      base_yhy := 100;    base_yhz := 0;
    base_zhx := 0;      base_zhy := 0;      base_zhz := 100;
{self.get_nusmv_end_block()}

--Error calculation
-- 2D CASE: y - up
    -- discretization_angle := 10;
    -- error := LEN*sin10 = 10 * 0,173 = 1,73;

    error := 1; -- +-1 (error=2) endX and endY coordinates error while checking reachability
    checkX := 0;
    checkY := 0;
    checkZ := 30;
    endX_inside_limits := (endX <= (checkX + error) & endX >= (checkX - error));
    endY_inside_limits := (endY <= (checkY + error) & endY >= (checkY - error));
    endZ_inside_limits := (endZ <= (checkZ + error) & endZ >= (checkZ - error));"""

    def create_nusmv_from_template(
        self, name: str, path="./tmp/", template="./smv/robot_structure_template.smv"
    ):
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
            for num, line in enumerate(lines):
                # print(f"{num}: {line}")
                if start_line in line:
                    copy_new_flag = True
                    print(f"found start:{line} start copy new")
                if end_line in line:
                    copy_new_flag = False
                    print(f"found end:{line} stop copy new")
                if copy_new_flag:
                    if copy_finished_flag:
                        continue
                    else:
                        target_file.writelines(self.get_nusmv_main())
                        # copy_new_flag = False
                        copy_finished_flag = True
                else:
                    target_file.write(line)

    @staticmethod
    def get_all_combinations(length, types: set):
        return list(product(types, repeat=length))


if __name__ == "__main__":
    # block_types = ["base", "yaw", "pitch", "pitch", "yaw", "pitch"]
    # robot1 = Robot(block_types)
    # # print(robot1.get_nusmv_main())
    # robot1.create_nusmv_from_template("1")
    print(Robot.get_all_combinations(3, {"a", "b"}))
