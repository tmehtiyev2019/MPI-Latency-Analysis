import matplotlib
matplotlib.use('Agg')  # Use a non-GUI backend that doesn't require Pillow
import matplotlib.pyplot as plt
import numpy as np

scenarios = ['1 pair', '2 pairs', '3 pairs', '4 pairs']
message_sizes = [32, 64, 128, 256, 512, 1024, 2048]  # in KB
data = {scenario: {'avg': [], 'std': []} for scenario in scenarios}

# Read data from each scenario file
for i, scenario in enumerate(scenarios, 1):
    with open(f'scenario{i}.txt', 'r') as f:
        lines = f.readlines()
    for line in lines:
        parts = line.strip().split()
        size = int(parts[0])
        avg = float(parts[1])
        std = float(parts[2])
        data[scenario]['avg'].append(avg)
        data[scenario]['std'].append(std)

# Plotting with improved error bar visibility
plt.figure(figsize=(15, 10))  # Larger figure size
x = np.arange(len(message_sizes))
width = 0.2

colors = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728']  # Distinct colors
capsize = 5  # Size of error bar caps
error_kw = dict(elinewidth=2, capsize=capsize, capthick=2)  # Thicker error bars

for i, (scenario, color) in enumerate(zip(scenarios, colors)):
    avg = data[scenario]['avg']
    std = data[scenario]['std']
    plt.bar(x + i*width, avg, width, 
            yerr=std, 
            label=scenario,
            color=color,
            error_kw=error_kw)

plt.xlabel('Message Size (KB)', fontsize=12)
plt.ylabel('Average RTT (μs)', fontsize=12)
plt.title('Round-Trip Time by Message Size and Scenario', fontsize=14, pad=20)

# Improve x-axis readability
plt.xticks(x + width*1.5, message_sizes, rotation=0)

# Add grid with lower opacity
plt.grid(True, alpha=0.3, linestyle='--')

# Move legend outside the plot
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', fontsize=10)

# Adjust layout to prevent legend cutoff
plt.tight_layout()

# Save with high DPI for better quality
plt.savefig('p1.png', dpi=300, bbox_inches='tight')
plt.close()