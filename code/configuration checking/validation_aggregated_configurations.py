from counterexample import Counterexample
import statistics
import matplotlib.pyplot as plt

from datetime import datetime, timezone

length_max = 5
# POINT REACHABILITY CHECKING
for length in range(3, length_max):
    smv_file = f"./smv_aggregated/robot_structure_aggregated_point_length{length}.smv"
    result_path = f"tmp/aggregated_region_result{length}.txt"
    start_time = datetime.now(timezone.utc)
    Counterexample.run_nusmv_file(smv_file, result_path)
    elapsed_time = datetime.now(timezone.utc) - start_time
    print(f"Time: {elapsed_time.total_seconds()} sec")
    end_coordinates = ["endX", "endY", "endZ"]
    block_types = ["yaw", "pitch"]
    block_type_vars = [f"var_block{num}" for num in range(1, length)]
    # print(block_type_vars)
    with open(result_path) as trace:
        counterexample = Counterexample(trace.read())
        types = counterexample.filter_variables(block_type_vars)[1]
        configuration = [block_types[num] for num in types]
        print(configuration)

# REGION REACHABILITY CHECKING
target = ["{-10,10}", "{-10,10}", "{0,10}"]
print(f"\nChecking reachability of region: {target}:")
block_types = {"yaw", "pitch"}
sum_timesR = []
robot_size = []
config_names = []
results = []
list_of_times = []

for length in range(3, length_max):
    smv_file = f"./smv_aggregated/robot_structure_aggregated_region_length{length}.smv"
    result_path = f"tmp/aggregated_region_result{length}.txt"
    start_time = datetime.now(timezone.utc)
    Counterexample.run_nusmv_file(smv_file, result_path)
    elapsed_time = datetime.now(timezone.utc) - start_time
    print(f"Time: {elapsed_time.total_seconds()} sec")
    end_coordinates = ["endX", "endY", "endZ"]
    block_types = ["yaw", "pitch"]
    block_type_vars = [f"var_block{num}" for num in range(1, length)]
    # print(block_type_vars)
    with open(result_path) as trace:
        counterexample = Counterexample(trace.read())
        types = counterexample.filter_variables(block_type_vars)[1]
        configuration = [block_types[num] for num in types]
        print(configuration)
