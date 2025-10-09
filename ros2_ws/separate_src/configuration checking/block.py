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
        # x: float,
        # y: float,
        # z: float,
        parent_block_num: int | None,
        length=10,
    ):
        self.number = number
        self.type = type
        self.parent = parent_block_num
        self.length = length
        # self.x = x
        # self.y = y
        # self.z = z

    def __repr__(self):
        return f"Block{self.number}: {self.type}"

    def __get_angle(self) -> str:
        """return angle(yaw1 or pitch2)"""
        return f"{self.type}{self.number}"

    def get_nusmv_block(self) -> str:
        """
        returns lines like:
        block0: block_base(base_px, base_py, base_pz,
                        base_xhx, base_xhy, base_xhz,
                        base_yhx, base_yhy, base_yhz,
                        base_zhx, base_zhy, base_zhz,
                        L1);
        """
        if self.parent is None:
            return """\tblock0: block_base(base_px, base_py, base_pz,
                                \tbase_xhx, base_xhy, base_xhz,
                                \tbase_yhx, base_yhy, base_yhz,
                                \tbase_zhx, base_zhy, base_zhz,
                                \tL1);"""
        return f"""\tblock{self.number}: block_{self.type}(block{self.parent}.px2, block{self.parent}.py2, block{self.parent}.pz2,
                        \tblock{self.parent}.xhx2, block{self.parent}.xhy2, block{self.parent}.xhz2,
                        \tblock{self.parent}.yhx2, block{self.parent}.yhy2, block{self.parent}.yhz2,
                        \tblock{self.parent}.zhx2, block{self.parent}.zhy2, block{self.parent}.zhz2,
                        \tL{self.number}, {self.__get_angle()});"""

    def get_nusmv_initline(self):
        """Create line like:
        -- link1
        L1  := 10;
        yaw1:= 0;
        """
        if self.number == 0 and self.type == "base":
            return ""
        else:
            return f"\t-- link1\t\nL{self.number}\t:= {self.length};\n\t{self.__get_angle()}\t:= 0;\n"

    def get_nusmv_endblock(self):
        """
        Create line like:
        "endX := block5.px2;\nendY := block5.py2;\nendZ := block5.pz2;\n"
        """
        return f"endX := block{self.number}.px2;\nendY := block{self.number}.py2;\nendZ := block{self.number}.pz2;\n"
