from robot import Robot


def test_init_robot():
    """test string representation of robot"""
    block_types = ["block_base", "block_yaw", "block_pitch", "block_pitch"]
    robot1 = Robot(block_types)
    assert (
        str(robot1)
        == "Block0: block_base\nBlock1: block_yaw\nBlock2: block_pitch\nBlock3: block_pitch\n"
    )


def test_nusmv_robot_structure():
    """test robot structure nusmv representation"""
    block_types = ["base", "yaw", "pitch", "pitch"]
    robot1_struct = """block0: block_base(base_px, base_py, base_pz,
                                base_xhx, base_xhy, base_xhz,
                                base_yhx, base_yhy, base_yhz,
                                base_zhx, base_zhy, base_zhz,
                                L1);
block1: block_yaw(block0.px2, block0.py2, block0.pz2,
                        block0.xhx2, block0.xhy2, block0.xhz2,
                        block0.yhx2, block0.yhy2, block0.yhz2,
                        block0.zhx2, block0.zhy2, block0.zhz2,
                        L1, yaw1);
block2: block_pitch(block1.px2, block1.py2, block1.pz2,
                        block1.xhx2, block1.xhy2, block1.xhz2,
                        block1.yhx2, block1.yhy2, block1.yhz2,
                        block1.zhx2, block1.zhy2, block1.zhz2,
                        L2, pitch2);
block3: block_pitch(block2.px2, block2.py2, block2.pz2,
                        block2.xhx2, block2.xhy2, block2.xhz2,
                        block2.yhx2, block2.yhy2, block2.yhz2,
                        block2.zhx2, block2.zhy2, block2.zhz2,
                        L3, pitch3);\n"""
    robot1 = Robot(block_types)
    assert robot1.get_nusmv_robot_structure() == robot1_struct


def test_get_nusmv_end_block():
    block_types = ["base", "yaw", "pitch", "pitch"]
    robot1 = Robot(block_types)
    end_block = """endX := block3.px2;
endY := block3.py2;
endZ := block3.pz2;
"""
    assert robot1.get_nusmv_end_block() == end_block


def test_get_nusmv_initialization():
    block_types = ["base", "yaw", "pitch", "pitch"]
    robot1 = Robot(block_types)
    init = """L1\t:= 10;
yaw1\t:= 0;
L2\t:= 10;
pitch2\t:= 0;
L3\t:= 10;
pitch3\t:= 0;\n"""
    assert robot1.get_nusmv_initialization() == init


def test_get_nusmv_main():
    main_module = """MODULE main
VAR
    block0 : block_base(base_px, base_py, base_pz,
                        base_xhx, base_xhy, base_xhz,
                        base_yhx, base_yhy, base_yhz,
                        base_zhx, base_zhy, base_zhz,
                        L1);
    block1 : block_yaw(block0.px, block0.py, block0.pz,
                        block0.xhx, block0.xhy, block0.xhz,
                        block0.yhx, block0.yhy, block0.yhz,
                        block0.zhx, block0.zhy, block0.zhz,
                        L1, yaw1 );
    block2 : block_pitch(block1.px2, block1.py2, block1.pz2,
                      block1.xhx2, block1.xhy2, block1.xhz2,
                      block1.yhx2, block1.yhy2, block1.yhz2,
                      block1.zhx2, block1.zhy2, block1.zhz2,
                      L2, pitch2);
    block3 : block_pitch(block2.px2, block2.py2, block2.pz2,
                      block2.xhx2, block2.xhy2, block2.xhz2,
                      block2.yhx2, block2.yhy2, block2.yhz2,
                      block2.zhx2, block2.zhy2, block2.zhz2,
                      L3, pitch3);
    block4 : block_yaw(block3.px, block3.py, block3.pz,
                        block3.xhx, block3.xhy, block3.xhz,
                        block3.yhx, block3.yhy, block3.yhz,
                        block3.zhx, block3.zhy, block3.zhz,
                        L4, yaw4 );
    block5 : block_pitch(block4.px2, block4.py2, block4.pz2,
                      block4.xhx2, block4.xhy2, block4.xhz2,
                      block4.yhx2, block4.yhy2, block4.yhz2,
                      block4.zhx2, block4.zhy2, block4.zhz2,
                      L5, pitch5);
DEFINE

L1 := 10;
yaw1    := 0;
L2 := 10;
pitch2  := 0;
L3 := 10;
pitch3  := 0;
L4 := 10;
yaw4    := 0;
L5 := 10;
pitch5  := 0;

    -- constant base pose and world-aligned basis (×100)
    base_px := 0;       base_py := 0;       base_pz := 0;

    base_xhx := 100;    base_xhy := 0;      base_xhz := 0;
    base_yhx := 0;      base_yhy := 100;    base_yhz := 0;
    base_zhx := 0;      base_zhy := 0;      base_zhz := 100;

    endX := block5.px2;
    endY := block5.py2;
    endZ := block5.pz2;

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
    block_types = ["base", "yaw", "pitch", "pitch", "yaw", "pitch"]
    robot1 = Robot(block_types)
    assert robot1.get_nusmv_main == main_module


def test_robot_generate_combinations():
    """test all robot combinations with given block types"""
    combinations = Robot.get_all_combinations(block_types)
    pass
