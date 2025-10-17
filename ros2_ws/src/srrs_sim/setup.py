from setuptools import find_packages, setup
import os
from glob import glob

package_name = "srrs_sim"

setup(
    name=package_name,
    version="0.0.0",
    packages=find_packages(exclude=["test"]),
    data_files=[
        ("share/ament_index/resource_index/packages", ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
        (os.path.join("share", package_name, "launch"), glob("launch/*.launch.py")),
        (os.path.join("share", package_name, "config"), glob("config/*.yaml")),
        (os.path.join("share", package_name, "commands"), glob("commands/*.json")),
        (os.path.join("share", package_name, "urdf"), glob("urdf/*.urdf")),
        (os.path.join("share", package_name, "urdf"), glob("urdf/*.xacro")),
        (os.path.join("share", package_name, "urdf/parts"), glob("urdf/parts/*.xacro")),
        (os.path.join("share", package_name, "sdf"), glob("sdf/*.sdf")),
        (os.path.join("share", package_name, "nusmv"), glob("nusmv/*.py")),
        (os.path.join("share", package_name, "nusmv/smv"), glob("nusmv/smv/*.smv")),
        (os.path.join("share", package_name, "meshes"), glob("meshes/*.stl")),
    ],
    install_requires=["setuptools"],
    zip_safe=True,
    maintainer="lao",
    maintainer_email="dmitry.babaytsev@cgi.com",
    description="TODO: Package description",
    license="Apache-2.0",
    tests_require=["pytest"],
    entry_points={
        "console_scripts": [
            "joints_controller = srrs_sim.joints_controller:main",
            "robot_controller_gui = srrs_sim.robot_controller_gui:main",
            "robot_controller_gui_config_validation = srrs_sim.robot_controller_gui_config_validation:main",
            "SRRSController = srrs_sim.SRRSController:main",
            "PartSpawner = srrs_sim.PartSpawner:main",
            "robotController = srrs_sim.robotController:main",
            "materialController = srrs_sim.materialController:main",
            "Assemble = srrs_sim.Assemble:main",
            "object_pose_io = srrs_sim.object_pose_io:main",
            "camera_process_node = srrs_sim.camera_process_node:main",
            "camera_process_node_gui = srrs_sim.camera_process_node_gui:main",
        ],
    },
)
