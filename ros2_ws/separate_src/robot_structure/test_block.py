from block import Block


"""Class to represent block of a robot"""

# example xacro:
# <xacro:block_ver block_number="11" parent_number="10"   x="0"   y="0"    z="0.5" />
# example smv:

# block_0 : BaseBlock(LEN,baseX,baseY,baseZ);
# block_1 : block_rot_vert(yaw1, LEN, block_0.x_end, block_0.y_end, block_0.z_end, block_0.yawAbs);
# block_2 : block_rot_hor(pitch2, LEN, block_1.x_end, block_1.y_end, block_1.z_end, block_1.yawAbs);


def test_get_nusmv_block():
    block0_base = Block(0, "b", 0.0, 0.0, 0.0, None)
    block1 = Block(1, "v", 0.0, 0.0, 0.0, 0)
    block2 = Block(2, "h", 0.0, 0.0, 0.0, 1)
    block3 = Block(3, "f", 0.0, 0.0, 0.0, 2)
    assert (
        block0_base.get_nusmv_block()
        == "block_0 : BaseBlock(pitch0, LEN, baseX, baseY, baseZ);\t\t-- generated\n"
    )
    assert (
        block1.get_nusmv_block()
        == "block_1 : block_rot_ver(yaw1, LEN, block_0.x_end, block_0.y_end, block_0.z_end, block_0.yawAbs);\t\t-- generated\n"
    )
    assert (
        block2.get_nusmv_block()
        == "block_2 : block_rot_hor(pitch2, LEN, block_1.x_end, block_1.y_end, block_1.z_end, block_1.yawAbs);\t\t-- generated\n"
    )
    assert (
        block3.get_nusmv_block()
        == "block_3 : block_fix(yaw3, LEN, block_2.x_end, block_2.y_end, block_2.z_end, block_2.yawAbs);\t\t-- generated\n"
    )


def test_get_nusmv_angle():
    block1 = Block(1, "v", 0.0, 0.0, 0.0, 0)
    block2 = Block(2, "h", 0.0, 0.0, 0.0, 1)
    angle_block1 = "yaw1\t:\t0..35;\t\t-- generated\n"
    angle_block2 = "pitch2\t:\t0..35;\t\t-- generated\n"
    assert block1.get_nusmv_angle() == angle_block1
    assert block2.get_nusmv_angle() == angle_block2


def test_get_nusmv_initline():
    block1 = Block(1, "v", 0.0, 0.0, 0.0, 0)
    block2 = Block(2, "h", 0.0, 0.0, 0.0, 1)
    block1_init = "init(yaw1)\t:= 0;"
    block2_init = "init(pitch2)\t:= 0;"
    assert block1.get_nusmv_initline() == block1_init
    assert block2.get_nusmv_initline() == block2_init


def test_get_nusmv_nextline():
    block1 = Block(1, "v", 0.0, 0.0, 0.0, 0)
    block2 = Block(2, "h", 0.0, 0.0, 0.0, 1)
    block1_next = "next(yaw1)\t:= {\n\t\tyaw1,\n\t\t(yaw1+1) mod 36,\n\t\t(yaw1+35) mod 36\n\t\t};\t\t-- generated\n"
    block2_next = "next(pitch2)\t:= {\n\t\tpitch2,\n\t\t(pitch2+1) mod 36,\n\t\t(pitch2+35) mod 36\n\t\t};\t\t-- generated\n"
    assert block1.get_nusmv_nextline() == block1_next
    assert block2.get_nusmv_nextline() == block2_next


def test_get_endblock_definition():
    block5 = Block(5, "v", 0.0, 0.0, 0.0, 4)
    endblock_lines = (
        "endX := block_5.x_end;\nendY := block_5.y_end;\nendZ := block_5.z_end;\n"
    )
    assert block5.get_nusmv_endblock() == endblock_lines
