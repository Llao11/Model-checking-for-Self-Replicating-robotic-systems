import statistics
import matplotlib.pyplot as plt
from configurations_checking import Configuration_checking


# POINT REACHABILITY CHECKING
target = ["5", "5", "10"]
print(f"Checking reachability of point: {target}:")
block_types = {"yaw", "pitch"}
sum_times = []
robot_size = []
config_names = []
results = []
list_of_times = []
length_max = 7
for length in range(2, length_max):
    robot_size.append(length)
    config_checking = Configuration_checking(length, block_types, target)
    # config_checking.set_target(target)
    config_names, times, res = config_checking.start_checking_combinations()
    results.append(res)
    list_of_times.append(times)
    sum_times.append(sum(times))
    print(times)


# REGION REACHABILITY CHECKING
target = ["{-10,10}", "{-10,10}", "{0,10}"]
print(f"\nChecking reachability of region: {target}:")
block_types = {"yaw", "pitch"}
sum_timesR = []
robot_size = []
config_names = []
results = []
list_of_times = []

for length in range(2, length_max):
    robot_size.append(length)
    config_checking = Configuration_checking(
        length, block_types, target, isTargetRegion=True
    )
    # config_checking.set_target(target)
    config_names, times, res = config_checking.start_checking_combinations()
    results.append(res)
    list_of_times.append(times)
    sum_times.append(statistics.mean(times))
    std_dev = statistics.stdev(times)
