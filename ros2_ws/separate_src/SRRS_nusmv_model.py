import subprocess
import json

# Define the NuSMV model as a string
with open("SRRS_model_template.smv", "r") as file:
    nusmv_model_template = file.read()

nusmv_model = nusmv_model_template.format(
    MAX_POS=9,
    STEPS=5,
    R=3,
    BUSY_CELLS = [ [1,6], [8,2] ],
    coords_leg1 = [ [2,2], [3,2], [3,3], [4,3], [4,4] ],
    coords_leg2 = [ [1,2], [1,3], [2,3], [2,4], [3,4] ],
    # TODO: change to one sequence of steps
    # TODO: integrate to the simulation
    # TODO: research interactive mode of NUSMV and how to use counterexamples
    )

# Write the model to a file
with open("2D_SimpleModel.smv", "w") as f:
    f.write(nusmv_model)

# Run NuSMV to verify the model
result = subprocess.run(["./NuSMV-2.7.0-linux64/bin/NuSMV", "2D_SimpleModel.smv"], capture_output=True, text=True)

# Print the output
print(result.stdout)

# Check if the verification was successful
if "is true" in result.stdout:
    print("The LTL property holds.")
else:
    print("The LTL property does not hold.")