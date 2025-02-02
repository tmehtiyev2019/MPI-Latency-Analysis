#!/bin/bash

# Submit first job and get its ID
job1=$(sbatch scenario1.slurm | cut -d ' ' -f 4)
echo "Submitted scenario 1, job ID: $job1"

# Submit second job with dependency on first
job2=$(sbatch --dependency=afterok:$job1 scenario2.slurm | cut -d ' ' -f 4)
echo "Submitted scenario 2, job ID: $job2"

# Submit third job with dependency on second
job3=$(sbatch --dependency=afterok:$job2 scenario3.slurm | cut -d ' ' -f 4)
echo "Submitted scenario 3, job ID: $job3"

# Submit fourth job with dependency on third
job4=$(sbatch --dependency=afterok:$job3 scenario4.slurm | cut -d ' ' -f 4)
echo "Submitted scenario 4, job ID: $job4"