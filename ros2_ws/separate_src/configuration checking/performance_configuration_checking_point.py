from robot import Robot
import re
from configurations_checking import Configuration_checking
import statistics
import re
from counterexample import Counterexample
import matplotlib.pyplot as plt

# common parameters
means = []
robot_size = []
config_names = []
results = []
list_of_times = []
block_types = {"yaw", "pitch"}
# Point target model checking
for length in range(2, 7):
    robot_size.append(length)
    config_checking = Configuration_checking(length, block_types)
    config_checking.set_target_point(5, 5, 10)
    config_names, times, res = config_checking.start_checking_combinations()
    results.append(res)
    list_of_times.append(times)
    means.append(statistics.mean(times))
    std_dev = statistics.stdev(times)

# postprocessing
with open("time_size_res.txt", "a") as file:
    file.write(str(config_names))
    file.write(str(means))
    file.write(str(results))
plt.figure(figsize=(8, 6))
plt.plot(robot_size, means, marker="o", linestyle="-", color="b")
plt.xlabel("Robot Size")
plt.ylabel("Average checking time (seconds)")
plt.title("Checking time changing with robot size")
plt.grid(True)
save_path = "Time_size_plot.png"
plt.savefig(save_path, dpi=300)
plt.show()
