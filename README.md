# MPI Point-to-Point Communication Latency Analysis

## Overview
This project implements and analyzes point-to-point message latency between pairs of nodes using MPI (Message Passing Interface). The implementation measures round-trip time (RTT) for different message sizes across various node pair configurations.

## Implementation Details

### Core Components
- **p1.c**: Main MPI program implementing point-to-point communication
- **plot_p1.py**: Python script for data visualization
- **Batch scripts**: SLURM job scripts for different scenarios

### Message Sizes
- Range: 32KB to 2MB
- Specific sizes: 32KB, 64KB, 128KB, 256KB, 512KB, 1MB, 2MB
- 10 iterations per size (first iteration skipped for warm-up)

### Test Scenarios
1. One pair (2 nodes)
2. Two pairs (4 nodes)
3. Three pairs (6 nodes)
4. Four pairs (8 nodes)

## Methodology

### Data Collection
- Used `gettimeofday()` for high-precision timing measurements
- Implemented synchronous send/receive using `MPI_Send()` and `MPI_Recv()`
- Collected statistics (average RTT and standard deviation) for the first pair (rank 0) only
- Skipped first iteration to avoid warm-up effects

### Execution Environment
- Platform: Skylake partition
- One process per node (-N and -n parameters are equal)
- Batch job submission using SLURM

## Results Analysis

### Performance Trends


### Scenario Comparison


### Network Configuration Insights


### Unusual Data Points


## Running the Code

### Prerequisites
```bash
# Load required modules (if any)
module load mpi

# Compile the MPI program
mpicc p1.c -lm -o p1

# Set up Python environment
source myenv/bin/activate
pip3 install --user numpy matplotlib --only-binary :all: