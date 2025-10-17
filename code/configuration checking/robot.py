"""
General robot class to generate structure combinations,
translate structure to NuSMV
"""

from block import Block
from itertools import product


class Robot:
    def __init__(self, block_sequence: list[str], lengths=None):
        parent_block_num = None
        self.structure = []
        for num, block_type in enumerate(block_sequence):
            if lengths is None:
                block = Block(num, block_type, parent_block_num)
            else:
                length = lengths[num]
                block = Block(num, block_type, parent_block_num, length)
            self.structure.append(block)
            parent_block_num = num
        self.last_block = self.structure[-1]

    def __repr__(self):
        structure = ""
        for block in self.structure:
            structure += f"{block}\n"
        return structure

    def get_length(self) -> int:
        return len(self.structure)

    def get_block_names(self) -> list[str]:
        return [block.get_name() for block in self.structure]

    def get_configuration_name(self) -> str:
        name = ""
        for block in self.structure:
            name += f"{block.type}_"
        return name

    def get_nusmv_parameters(self) -> str:
        name = ""
        for block in self.structure:
            name += f"{block.type}_"
        return name

    def get_nusmv_init_part(self) -> str:
        init = ""
        for block in self.structure:
            init += f"{block.get_nusmv_initline()}"
        return init

    def get_nusmv_end_part(self) -> str:
        return self.last_block.get_nusmv_endblock()

    def get_nusmv_robot_structure_part(self):
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
        """
        structure = ""
        for block in self.structure:
            structure += block.get_nusmv_block() + "\n"
        return structure


if __name__ == "__main__":
    block_types = ["base", "yaw", "pitch", "pitch", "yaw", "pitch"]
    robot1 = Robot(block_types)
    print(robot1)
    # for configuration in Robot.get_all_combinations(4, {"yaw", "pitch"}):
    #     robot = Robot(configuration)
    #     robot.create_nusmv_from_template("1")
