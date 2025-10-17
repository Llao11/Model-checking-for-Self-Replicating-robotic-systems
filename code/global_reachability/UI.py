import tkinter as tk
import Generate_model


# Predefined colors for part types
COLOR_PALETTE = [
    "white",
    "lightgreen",
    "lightcoral",
    "lightyellow",
    "lightpink",
    "lightgray",
    "lightcyan",
    "lightgoldenrod",
]

# Global variables for dynamic UI components
center_grid_frame = None
right_column_frame = None
part_list = []  # To store parsed part types
default_parts = "None, Base,Yaw,Pitch"
default_robot_size = 6
default_grid_size = 6
output_text = None  # Output field reference
canvas = None  # Canvas for drawing lines
cell_buttons = {}  # Dictionary to store button references with their grid positions
nusmv_model = Generate_model.Generate_model()
field_size_val = 1  # initial field size value
cell_values = {}
robot_sequence_values = {}

# Functions for button actions


def on_set():
    global center_grid_frame, right_column_frame, part_list, canvas, cell_buttons
    # Parse part types
    part_types_str = part_entry.get()
    part_list = [
        p.strip() for p in part_types_str.replace(",", " ").split() if p.strip()
    ]
    # Parse robot size and field size
    try:
        robot_size_val = int(robot_entry.get().strip())
        field_size_val = int(field_entry.get().strip())
    except ValueError:
        return  # If invalid input, do nothing
    if not part_list or robot_size_val <= 0 or field_size_val <= 0:
        return  # Ensure values are positive and valid
    # Clear previous grids
    if center_grid_frame is not None:
        center_grid_frame.destroy()
    if right_column_frame is not None:
        right_column_frame.destroy()
    if canvas is not None:
        canvas.destroy()  # Clear previous lines
    # Create new frames for central grid and right column
    center_grid_frame = tk.Frame(center_frame)
    center_grid_frame.pack()

    right_column_frame = tk.Frame(right_frame)
    right_column_frame.pack()
    # Create a Canvas for drawing lines
    canvas = tk.Canvas(center_grid_frame, width=500, height=500, bg="white")
    canvas.grid(
        row=0,
        column=0,
        columnspan=field_size_val,
        rowspan=field_size_val,
        sticky="nsew",
    )

    cell_buttons = {}  # Reset button dictionary

    # Generate the central grid of Option Menu buttons
    for r in range(field_size_val):
        for c in range(field_size_val):
            var = tk.StringVar(value=part_list[0] if part_list else "")

            # Create a button
            btn = tk.Menubutton(
                center_grid_frame, text=var.get(), relief=tk.RAISED, width=2, height=1
            )
            menu = tk.Menu(btn, tearoff=0)
            for index, part in enumerate(part_list):
                menu.add_command(
                    label=part,
                    command=lambda v=var, b=btn, p=part: update_cell(v, b, p),
                )
            btn.config(menu=menu, bg=get_color(var.get()))

            # Store button reference with grid coordinates
            cell_buttons[(r, c)] = btn
            cell_values[(r, c)] = var

            # Place button inside the grid
            btn.grid(row=r, column=c, padx=15, pady=15, sticky="nsew")

    # Ensure cells remain square
    for i in range(field_size_val):
        center_grid_frame.columnconfigure(i, weight=1)
        center_grid_frame.rowconfigure(i, weight=1)

    tk.Button(center_grid_frame, text="Load model", command=on_load_model).grid(
        row=field_size_val, column=0, columnspan=2, padx=5, pady=5
    )
    tk.Button(center_grid_frame, text="Save model", command=on_save_model).grid(
        row=field_size_val, column=2, columnspan=2, padx=5, pady=5
    )

    # Generate the right column of OptionMenus
    for i in range(robot_size_val):
        var = tk.StringVar(value=part_list[0] if part_list else "")
        option = tk.OptionMenu(right_column_frame, var, *part_list)
        option.pack(pady=2)
        robot_sequence_values[i] = var

    # NUSMV part
    model_respond = nusmv_model.setup(field_size_val)
    set_output_text(
        model_respond + "\nConfigure the field, the robot and press Generate model"
    )


def update_cell(var, btn, part):
    """Update the selected cell with the chosen part type and its associated color"""
    var.set(part)
    btn.config(text=part, bg=get_color(part))


def get_color(part):
    """Return a color based on the part's index in the list"""
    if part in part_list:
        index = part_list.index(part)
        # Cycle through colors if needed
        return COLOR_PALETTE[index % len(COLOR_PALETTE)]
    return "white"  # Default color


def on_generate():
    # Parse robot size and field size
    try:
        field_size_val = int(field_entry.get().strip())
    except ValueError:
        return  # If invalid input, do nothing

    grid = [["NONE" for _ in range(field_size_val)] for _ in range(field_size_val)]
    for (r, c), var in cell_values.items():
        if (
            0 <= r < field_size_val and 0 <= c < field_size_val
        ):  # Ensure indices are within bounds
            grid[r][c] = var.get()
    print(len(grid))

    object_types = {f for row in grid for f in row}

    grid_str = "[\n"
    for row in grid:
        grid_str += "    [" + ",".join(row) + "],\n"
    grid_str = grid_str[:-2] + "\n];"
    print(grid_str)

    if canvas is not None:
        canvas.delete("all")  # Clear previous lines

    # Convert list to string and show it in the output field

    # TODO receive robot_sequence from right column
    robot_sequence = []
    for i, var in robot_sequence_values.items():
        # print(i, var.get())
        robot_sequence.append(var.get())
    # robot_sequence=robot_sequence[:-1] + ']'

    # robot_sequence = ["TYPE1","TYPE2","TYPE2","TYPE3"]
    print(robot_sequence)
    model_respond = nusmv_model.generate(grid_str, robot_sequence, object_types)
    set_output_text(model_respond)


def on_verify():
    """Draw predefined lines on the central grid"""
    output, path = nusmv_model.verify()
    print_to_output = ""
    for line in output:
        if not line.startswith("***"):
            print_to_output = print_to_output + line
    set_output_text(print_to_output)

    # Draw the lines on the canvas
    if path == []:
        set_output_text("No path found")
    else:
        for i in range(len(path) - 1):
            draw_line_between_cells(
                path[i][0], path[i][1], path[i + 1][0], path[i + 1][1]
            )

    # print_to_output = "NuSMV output: \n"+ output + "Path coordinates:" + str(path)


def draw_line_between_cells(x1, y1, x2, y2):
    """Draw a line from one button center to another"""
    if (x1, y1) in cell_buttons and (x2, y2) in cell_buttons:
        btn1 = cell_buttons[(x1, y1)]
        btn2 = cell_buttons[(x2, y2)]

        # Compute canvas coordinates of the buttons
        x1_canvas = btn1.winfo_x() + btn1.winfo_width() // 2
        y1_canvas = btn1.winfo_y() + btn1.winfo_height() // 2
        x2_canvas = btn2.winfo_x() + btn2.winfo_width() // 2
        y2_canvas = btn2.winfo_y() + btn2.winfo_height() // 2

        # Draw a line between them
        if canvas is None:
            raise ValueError("Canvas is None")
        canvas.create_line(
            x1_canvas, y1_canvas, x2_canvas, y2_canvas, fill="black", width=3
        )


def set_output_text(text):
    """Update the output field with the given text"""
    if output_text is None:
        raise ValueError("Output field text is None")
    output_text.config(state=tk.NORMAL)  # Enable editing temporarily
    output_text.insert(tk.END, text)  # Insert new text
    output_text.config(state=tk.DISABLED)  # Make it read-only again


def clear_output_text():
    """Update the output field with the given text"""
    if output_text is None:
        raise ValueError("Output field text is None")
    output_text.config(state=tk.NORMAL)  # Enable editing temporarily
    output_text.delete(1.0, tk.END)  # Clear previous text
    output_text.config(state=tk.DISABLED)  # Make it read-only again


def on_save_model():
    on_generate()


def on_load_model():
    pass


# Main application window
root = tk.Tk()
root.title("SRRS 2D reachability model checking")

# Left Panel: Input fields and buttons
left_frame = tk.Frame(root)
left_frame.grid(row=0, column=0, padx=10, pady=10, sticky="nw")

tk.Label(left_frame, text="Part Types:").grid(row=0, column=0, sticky="e")
part_entry = tk.Entry(left_frame)
part_entry.grid(row=0, column=1, padx=5, pady=2)
part_entry.insert(0, default_parts)

tk.Label(left_frame, text="Robot Size:").grid(row=1, column=0, sticky="e")
robot_entry = tk.Entry(left_frame)
robot_entry.grid(row=1, column=1, padx=5, pady=2)
robot_entry.insert(0, str(default_robot_size))

tk.Label(left_frame, text="Field Size:").grid(row=2, column=0, sticky="e")
field_entry = tk.Entry(left_frame)
field_entry.grid(row=2, column=1, padx=5, pady=2)
field_entry.insert(0, str(default_grid_size))

tk.Button(left_frame, text="1. Create field", command=on_set).grid(
    row=3, column=0, padx=5, pady=5
)
tk.Button(left_frame, text="2. Generate model", command=on_generate).grid(
    row=3, column=1, padx=5, pady=5
)
tk.Button(left_frame, text="3. Verify model", command=on_verify).grid(
    row=3, column=2, padx=5, pady=5
)

# Output Field
output_text = tk.Text(left_frame, height=30, width=50, state=tk.DISABLED, wrap=tk.WORD)
output_text.grid(row=4, column=0, columnspan=3, pady=5)
tk.Button(left_frame, text="Clear output", command=clear_output_text).grid(
    row=5, column=0, padx=5, pady=5
)

# Center Panel
center_frame = tk.Frame(root)
center_frame.grid(row=0, column=1, padx=10, pady=10)

# Right Panel
right_frame = tk.Frame(root)
right_frame.grid(row=0, column=2, padx=10, pady=10, sticky="nw")

root.mainloop()
