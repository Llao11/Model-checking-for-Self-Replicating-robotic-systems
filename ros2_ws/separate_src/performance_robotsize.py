import matplotlib.pyplot as plt

# Sample data
elapsed_times  = [9.936768531799316, 9.46236538887024, 10.556655645370483, 10.744861841201782, 10.66709852218628]  # Field sizes
field_sizes = [2, 3, 4, 5, 6]    # Elapsed times corresponding to each field size

# Create the plot
plt.figure(figsize=(8, 6))
plt.plot(field_sizes,elapsed_times, marker='o', linestyle='-', color='b')

# Labeling the axes
plt.xlabel('Robot Size')
plt.ylabel('Elapsed Time (seconds)')

# Title of the graph
plt.title('Elapsed Time vs Field Size')

# Display the grid
plt.grid(True)

# Show the plot
plt.show()