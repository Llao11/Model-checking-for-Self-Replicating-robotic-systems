import matplotlib.pyplot as plt

# Sample data
elapsed_times  = [1.5466690063476562, 1.4560039043426514, 13.270666599273682, 65.1186695098877, 97.3830099105835,313.8782398700714 ]  # Field sizes
field_sizes = [4, 5, 6, 7, 8, 9]    # Elapsed times corresponding to each field size

# Create the plot
plt.figure(figsize=(8, 6))
plt.plot(field_sizes,elapsed_times, marker='o', linestyle='-', color='b')

# Labeling the axes
plt.xlabel('Field Size')
plt.ylabel('Elapsed Time (seconds)')

# Title of the graph
plt.title('Elapsed Time vs Field Size')

# Display the grid
plt.grid(True)

# Show the plot
plt.show()