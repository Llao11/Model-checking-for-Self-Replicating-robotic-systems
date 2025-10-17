from robot import Robot
from counterexample import Counterexample
from nusmv_model_generator import RobotNusmvGenerator

# common parameters
angle_vars = [
    "block1.yaw",
    "block2.pitch",
    "block3.yaw",
    "block4.pitch",
]
# Point target model checking
sequence = ["base", "yaw", "pitch", "yaw", "pitch"]
lengths = [10, 10, 10, 10, 10]
robot = Robot(sequence, lengths)
generator = RobotNusmvGenerator(robot, output_smv_path="./smv/")
generator.set_target_point(20, 20, 20)
generator.generate_from_template("new_robot")
result = Counterexample.run_nusmv_file("./smv/new_robot.smv")
counterexample = Counterexample(result, len(sequence))
counterexample.set_plot_limits(30)
end_coordinates = ["endX", "endY", "endZ"]
steps = counterexample.filter_variables(end_coordinates)
print(steps)
angles = counterexample.get_angles(angle_vars)
print("Control angles:")
counterexample.print_steps(angles)
counterexample.plot_trace(-1, show_plot=True)
