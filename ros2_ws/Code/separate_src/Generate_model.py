import subprocess
import re

class Generate_model:
    def __init__(self, field_size, robot_sequence):
        self.field_size = field_size  # Instance attribute


        # Define the NuSMV model as a string
        template_file = "Assemble_initial_template.smv"
        self.model_file = "Assemble_temporary.smv"
        with open(template_file, "r") as file:
            self.nusmv_model_template = file.read()

        # INITIAL PARAMETERS
        self.field_max_index=self.field_size+1
        self.visit_cells_types = "{UNKNOWN, VISITED}"
        self.robot_sequence = robot_sequence #["TYPE1","TYPE2","TYPE2","TYPE3"]
        self.robot_states = "{MOVING, CHECKING, ASSEMBLING, FINISHED, FAILED }"
        field_object_types = ["NONE", "TYPE1", "TYPE2", "TYPE3", "OBSTACLE1"]
        object_coordinates = {
            (3,3):"TYPE1", 
            (1,2):"TYPE2",
            (2,0):"TYPE2",
            (3,1):"TYPE3",
            }


        # GENERATED PARAMETERS

        # Generate initial_grid based on object_coordinates: [ [NONE,NONE],[NONE,TYPE1] ];
        initial_grid="[\n"
        for x in range(self.field_max_index+1):
            initial_grid= initial_grid + "["
            for y in range(self.field_max_index+1):
                if (x,y) in object_coordinates:
                    object_type = object_coordinates.get((x,y))
                else: 
                    object_type = "NONE"
                initial_grid = initial_grid + object_type
                if y<self.field_max_index: 
                    initial_grid= initial_grid + "," 
                else:
                    initial_grid= initial_grid + "]"
            if x<self.field_max_index: 
                initial_grid= initial_grid + ",\n" 
            else:
                initial_grid= initial_grid + "\n"
            # initial_grid= initial_grid + ",\n"
        self.initial_grid= initial_grid + "];"


        # Types of objects on the field {NONE, TYPE1, TYPE2, OBSTACLE1, TYPE3}
        self.object_types = f" {set(field_object_types)}".replace("'","")

        self.robot_size = len(self.robot_sequence)-1

        # set of part types: {TYPE1, TYPE2, TYPE3};
        self.robot_part_types = f" {set(self.robot_sequence)}".replace("'","")

        # Form cicle of: init(sequence[0]) := TYPE1;
        self.init_robot_sequence = ""
        for i in range(len(self.robot_sequence)):
            self.init_robot_sequence = self.init_robot_sequence +f"\n init(sequence[{i}]) := {self.robot_sequence[i]};" 

    def generate(self):
        nusmv_model = self.nusmv_model_template.format(
            field_max_index=self.field_max_index,
            robot_size=self.robot_size,
            object_types = self.object_types,
            visit_cells_types = self.visit_cells_types,
            robot_states = self.robot_states,
            robot_part_types = self.robot_part_types,
            init_robot_sequence = self.init_robot_sequence,
            initial_grid= self.initial_grid,
            # TODO: change to one sequence of steps
            # TODO: integrate to the simulation
            # TODO: research interactive mode of NUSMV and how to use counterexamples
            )

        # Write the model to a file
        with open(self.model_file, "w") as f:
            f.write(nusmv_model)

    def generate(self):
        # Run NuSMV to verify the model
        result = subprocess.run(["./NuSMV-2.7.0-linux64/bin/NuSMV", "-dynamic", self.model_file], capture_output=True, text=True)

        # Print the output
        # print(result.stdout)

# Check if the verification was successful
# if "is true" in result.stdout:
#     print("The LTL property holds.")
# else:
#     print("The LTL property does not hold.")

#  TODO derive shortest path based on coordinates if G F (robot_state != FINISHED); is false

        result_analysis = result.stdout
        words_to_find = [ "x = ", "y = ","robot_state = FINISHED"]

        # Split the text into lines and filter lines containing the words
        pattern = re.compile(r"\b(" + "|".join(map(re.escape, words_to_find)) + r")\b")
        matching_lines = [line for line in result_analysis.splitlines() if pattern.search(line)]

        path_coordinates =[]
        x=0
        y=0
        for line in matching_lines:
            print("line: "+line)
            if "x" in line: 
                x= int(line.replace(" ","").split("=")[1])
            elif "y" in line: 
                y= int(line.replace(" ","").split("=")[1])
            path_coordinates.append([x,y])
        print(path_coordinates)

        return path_coordinates

# TODO derive problematic regions if G F (robot_state != FAILED); is false