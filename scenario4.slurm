#!/bin/bash
#SBATCH -N8
#SBATCH -n8
#SBATCH -p skylake
#SBATCH --output=scenario4.txt

mpirun -np 8 ./p1