from block import Block


"""Class to represent block of a robot"""

# example xacro:
# <xacro:block_ver block_number="11" parent_number="10"   x="0"   y="0"    z="0.5" />
# example smv:

# block_0 : BaseBlock(LEN,baseX,baseY,baseZ);
# block_1 : block_rot_vert(yaw1, LEN, block_0.x_end, block_0.y_end, block_0.z_end, block_0.yawAbs);
# block_2 : block_rot_hor(pitch2, LEN, block_1.x_end, block_1.y_end, block_1.z_end, block_1.yawAbs);


def test_block_str():
    block0_base = Block(0, "b", None)
    assert str(block0_base) == "Block0: b"


def test_get_nusmv_block():
    """
    block1 : block_base(base_px, base_py, base_pz,
                        base_xhx, base_xhy, base_xhz,
                        base_yhx, base_yhy, base_yhz,
                        base_zhx, base_zhy, base_zhz,
                        L1, yaw1 );
    block3 : block_pitch(block2.px2, block2.py2, block2.pz2,
                         block2.xhx2, block2.xhy2, block2.xhz2,
                         block2.yhx2, block2.yhy2, block2.yhz2,
                         block2.zhx2, block2.zhy2, block2.zhz2,
                         L3, pitch3);
    block4 : block_yaw(block3.px, block3.py, block3.pz,
    \t\t\t\t\t block3.xhx, block3.xhy, block3.xhz,
                       block3.yhx, block3.yhy, block3.yhz,
                       block3.zhx, block3.zhy, block3.zhz,
                       L4, yaw4 );
    """
    block0 = Block(0, "base", None)
    block3 = Block(3, "pitch", 2)
    block4 = Block(4, "yaw", 3)
    block0_nusmv = """block0: block_base(base_px, base_py, base_pz,
                                base_xhx, base_xhy, base_xhz,
                                base_yhx, base_yhy, base_yhz,
                                base_zhx, base_zhy, base_zhz,
                                L1);"""
    block3_nusmv = """block3: block_pitch(block2.px2, block2.py2, block2.pz2,
                        block2.xhx2, block2.xhy2, block2.xhz2,
                        block2.yhx2, block2.yhy2, block2.yhz2,
                        block2.zhx2, block2.zhy2, block2.zhz2,
                        L3, pitch3);"""
    block4_nusmv = """block4: block_yaw(block3.px2, block3.py2, block3.pz2,
                        block3.xhx2, block3.xhy2, block3.xhz2,
                        block3.yhx2, block3.yhy2, block3.yhz2,
                        block3.zhx2, block3.zhy2, block3.zhz2,
                        L4, yaw4);"""
    assert block0.get_nusmv_block() == block0_nusmv
    assert block3.get_nusmv_block() == block3_nusmv
    assert block4.get_nusmv_block() == block4_nusmv


def test_get_nusmv_initialization():
    block0 = Block(0, "base", None)
    block1 = Block(1, "yaw", 0)
    block2 = Block(2, "pitch", 1)
    block0_init = ""
    block1_init = """L1\t:= 10;\nyaw1\t:= 0;\n"""
    block2_init = """L2\t:= 10;\npitch2\t:= 0;\n"""
    assert block0.get_nusmv_initline() == block0_init
    assert block1.get_nusmv_initline() == block1_init
    assert block2.get_nusmv_initline() == block2_init


def test_get_endblock_definition():
    block5 = Block(5, "yaw", 4)
    endblock_lines = "endX := block5.px2;\nendY := block5.py2;\nendZ := block5.pz2;\n"
    assert block5.get_nusmv_endblock() == endblock_lines
