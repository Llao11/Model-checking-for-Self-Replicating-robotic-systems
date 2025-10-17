import statistics
import matplotlib.pyplot as plt
from configurations_checking import Configuration_checking


# POINT REACHABILITY CHECKING
target = ["5", "5", "10"]
# print(f"Checking reachability of point: {target}:")
#
# robot_size = [3, 4, 5, 6]
# sum_times1 = [
#     sum([0.0899, 0.0291, 0.0467, 0.0275]),
#     sum([0.3534, 0.0920, 0.5114, 0.0322, 0.5847, 0.0528, 0.1590, 0.0294]),
#     sum(
#         [
#             1.8347,
#             0.2701,
#             2.0633,
#             0.0390,
#             2.2923,
#             0.2200,
#             0.9994,
#             0.0132,
#             1.1530,
#             0.2345,
#             2.3829,
#             0.0237,
#             0.4713,
#             0.0673,
#             0.1292,
#             0.1292,
#         ]
#     ),
#     sum(
#         [
#             169.71,
#             1.8283,
#             70.105,
#             0.2860,
#             50.922,
#             2.4502,
#             17.172,
#             0.0463,
#             55.968,
#             6.5920,
#             147.78,
#             0.2445,
#             18.397,
#             1.1950,
#             2.7777,
#             0.0128,
#             25.389,
#             2.2987,
#             46.454,
#             0.2329,
#             45.252,
#             5.0098,
#             17.253,
#             0.0482,
#             2.8130,
#             0.5298,
#             7.4332,
#             0.0784,
#             1.1831,
#             0.1470,
#             0.6042,
#             0.0119,
#         ]
#     ),
# ]
#
# # REGION REACHABILITY CHECKING
#
# sum_times2 = [0.051897, 0.691716, 22.641955, 1057.268079]
#
# plt.figure(figsize=(8, 6))
# plt.plot(
#     robot_size, sum_times1, marker="o", linestyle="-", color="b", label="Individual"
# )
# plt.plot(
#     robot_size, sum_times2, marker="o", linestyle="-", color="r", label="Aggregated"
# )
# plt.xlabel("Robot Size")
# plt.ylabel("Total checking time (seconds)")
# plt.title(
#     "Model checking time with robot size for point target, sequential and aggregated"
# )
# plt.grid(True)
# plt.legend()
# save_path = "Time_size_plot point.png"
# plt.savefig(save_path, dpi=300)
# plt.show()


# REGION REACHABILITY CHECKING
robot_size = [3, 4, 5, 6]
target = ["{-10,10}", "{-10,10}", "{0,10}"]
print(f"\nChecking reachability of region: {target}:")
sum_times1 = [0.3452, 4.6432, 212.13245, 11926.512631]
sum_times2 = [0.051897, 0.691716, 14.641955, 724.8079]

plt.figure(figsize=(8, 6))
plt.plot(
    robot_size, sum_times1, marker="o", linestyle="-", color="b", label="Individual"
)
plt.plot(
    robot_size, sum_times2, marker="o", linestyle="-", color="r", label="Aggregated"
)
plt.xlabel("Robot Size")
plt.ylabel("Total checking time (seconds)")
plt.title(
    "Model checking time with robot size for region target, sequential and aggregated"
)
plt.grid(True)
plt.legend()
save_path = "Time_size_plot point.png"
plt.savefig(save_path, dpi=300)
plt.show()
