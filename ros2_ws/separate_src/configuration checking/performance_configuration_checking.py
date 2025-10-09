from robot import Robot
from itertools import product
from datetime import datetime, timezone
import subprocess
import threading
import re
from counterexample import Counterexample
from configurations_checking import Configuration_checking


checkX = 10
checkY = 10
checkZ = 20
length = 5
block_types = {"yaw", "pitch"}
config_checking = Configuration_checking(length, block_types)

config_checking.start_checking_combinations()
