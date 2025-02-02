#!/bin/bash
#SBATCH -N6
#SBATCH -n6
#SBATCH -p skylake
#SBATCH --output=scenario3.txt

mpirun -np 6 ./p1