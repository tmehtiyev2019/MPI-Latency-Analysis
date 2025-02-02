#!/bin/bash
#SBATCH -N4
#SBATCH -n4
#SBATCH -p skylake
#SBATCH --output=scenario2.txt

mpirun -np 4 ./p1