#!/bin/bash
#SBATCH -N2
#SBATCH -n2
#SBATCH -p skylake
#SBATCH --output=scenario1.txt

mpirun -np 2 ./p1