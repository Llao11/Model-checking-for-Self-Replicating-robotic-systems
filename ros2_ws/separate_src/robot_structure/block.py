class Block:
    """Class to represent block of a robot"""

    # example xacro:
    # <xacro:block_ver block_number="11" parent_number="10"   x="0"   y="0"    z="0.5" />
    # example smv:

    # block_0 : BaseBlock(LEN,baseX,baseY,baseZ);
    # block_1 : block_rot_vert(yaw1, LEN, block_0.x_end, block_0.y_end, block_0.z_end, block_0.yawAbs);
    # block_2 : block_rot_hor(pitch2, LEN, block_1.x_end, block_1.y_end, block_1.z_end, block_1.yawAbs);

    def __init__(
        self,
        number: int,
        type: str,
        x: float,
        y: float,
        z: float,
        parent_block_num: int | None,
    ):
        self.number = number
        self.type = type
        self.parent = parent_block_num
        self.x = x
        self.y = y
        self.z = z

    def __get_angle_type(self) -> str:
        """return angle(yaw1 or pitch2)"""
        if self.type == "f" or self.type == "v":
            return f"yaw{self.number}"
        elif self.type == "h" or self.type == "b":
            return f"pitch{self.number}"
        else:
            raise Exception("Block has a wrong type")

    def __get_block_type(self) -> str:
        if self.type == "f":
            return "block_fix"
        elif self.type == "v":
            return "block_rot_ver"
        elif self.type == "h":
            return "block_rot_hor"
        elif self.type == "b":
            return "BaseBlock"
        else:
            raise Exception("Block has a wrong type")

    def get_nusmv_block(self) -> str:
        """
        returns lines like:
        "block_0 : BaseBlock(pitch0, LEN, baseX, baseY, baseZ);\t\t--generated"
        "block_1 : block_rot_ver(yaw1,LEN, block_0.x_end, block_0.y_end, block_0.z_end, block_0.yawAbs);\t\t-- generated\n"
        "block_2 : block_rot_hor(pitch2, LEN, block_1.x_end, block_1.y_end, block_1.z_end, block_1.yawAbs);\t\t-- generated\n"
        "block_3 : block_fix(yaw3, LEN, block_2.x_end, block_2.y_end, block_2.z_end, block_2.yawAbs);\t\t-- generated\n"
        """

        start = f"block_{self.number} : "
        end = "\t\t-- generated\n"
        if self.type == "f" or self.type == "v" or self.type == "h":
            line = f"{self.__get_block_type()}({self.__get_angle_type()}, LEN, block_{
                self.parent
            }.x_end, block_{self.parent}.y_end, block_{self.parent}.z_end, block_{
                self.parent
            }.yawAbs);"
            return start + line + end
        elif self.type == "b":
            line = f"BaseBlock(pitch{self.number}, LEN, baseX, baseY, baseZ);"
            return start + line + end
        else:
            raise Exception("Block has a wrong type")

    def get_nusmv_angle(self) -> str:
        if self.type == "f" or self.type == "v":
            angle = f"yaw{self.number}"
        elif self.type == "h":
            angle = f"pitch{self.number}"
        elif self.type == "b":
            angle = " "
        else:
            raise Exception("Block has a wrong type")
        end = "\t:\t0..35;\t\t-- generated"
        return angle + end + "\n"

    def get_nusmv_initline(self):
        """Create line like:
        init(yaw1)   := 0;
        init(pitch2) := 0;
        """
        return f"init({self.__get_angle_type()})\t:= 0;"

    def get_nusmv_nextline(self):
        """Create line like
        next(yaw1)   := {
                        yaw1,               -- stays the same
                        (yaw1+1) mod 36,    -- + 10 degrees
                        (yaw1+35) mod 36    -- - 10 degrees
                        };
        """
        angle = self.__get_angle_type()

        # "next(pitch2)   := {\n\t\tpitch2,\n\t\t(pitch2+1) mod 36,\n\t\t(pitch2+35) mod 36\n\t\t};\t\t-- generated\n"
        return f"next({angle})\t:= {{\n\t\t{angle},\n\t\t({angle}+1) mod 36,\n\t\t({angle}+35) mod 36\n\t\t}};\t\t-- generated\n"

    def get_nusmv_endblock(self):
        """
        Create line like:
        "endX := block_5.x_end;\nendY := block_5.y_end;\nendZ := block_5.z_end;\n"
        """
        return f"endX := block_{self.number}.x_end;\nendY := block_{self.number}.y_end;\nendZ := block_{self.number}.z_end;\n"
