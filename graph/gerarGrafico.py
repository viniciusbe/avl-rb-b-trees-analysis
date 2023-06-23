import pandas as pd
from matplotlib import pyplot as plt

# Set the figure size
plt.rcParams["figure.figsize"] = [7.00, 3.50]
plt.rcParams["figure.autolayout"] = True
plt.rcParams["figure.dpi"] = 600

plt.rcParams["lines.linewidth"] = 1

# Make a list of columns
headers = ['AVL', 'RN', 'B-1', 'B-5', 'B-10']

# Read a CSV file
df = pd.read_csv("graph/adicao.csv", names=headers)

# Plot the lines
df.plot()

plt.savefig('graph/adicao.png')