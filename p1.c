#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#define NUM_ITERATIONS 10
#define SKIP_ITER 1

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_size % 2 != 0) {
        if (rank == 0) fprintf(stderr, "Even number of processes required.\n");
        MPI_Finalize();
        return 1;
    }

    // Determine partner (even ranks send to odd)
    int is_sender = (rank % 2 == 0);
    int partner = is_sender ? rank + 1 : rank - 1;

    // Message sizes from 32KB to 2MB (in bytes)
    const int sizes[] = {32768, 65536, 131072, 262144, 524288, 1048576, 2097152};
    const int num_sizes = sizeof(sizes) / sizeof(int);

    double *avg_rtt = NULL, *stddev = NULL;
    if (rank == 0) {
        avg_rtt = malloc(num_sizes * sizeof(double));
        stddev = malloc(num_sizes * sizeof(double));
    }

    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];
        char *buffer = malloc(size);
        if (!buffer) {
            fprintf(stderr, "Rank %d: Failed to allocate %d bytes.\n", rank, size);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }


        double rtts[NUM_ITERATIONS - SKIP_ITER];
        for (int iter = 0; iter < NUM_ITERATIONS; iter++) {
            MPI_Barrier(MPI_COMM_WORLD); // Sync all processes

            if (is_sender) {
                struct timeval start, end;
                gettimeofday(&start, NULL);
                MPI_Send(buffer, size, MPI_BYTE, partner, 0, MPI_COMM_WORLD);
                MPI_Recv(buffer, size, MPI_BYTE, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                gettimeofday(&end, NULL);

                if (iter >= SKIP_ITER) {
                    double elapsed = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec);
                    rtts[iter - SKIP_ITER] = elapsed;
                }
            } else {
                MPI_Recv(buffer, size, MPI_BYTE, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(buffer, size, MPI_BYTE, partner, 0, MPI_COMM_WORLD);
            }
        }

        if (is_sender && rank == 0) { // Only rank 0 collects data
            double sum = 0.0, sum_sq = 0.0;
            for (int i = 0; i < NUM_ITERATIONS - SKIP_ITER; i++) sum += rtts[i];
            avg_rtt[s] = sum / (NUM_ITERATIONS - SKIP_ITER);

            for (int i = 0; i < NUM_ITERATIONS - SKIP_ITER; i++)
                sum_sq += (rtts[i] - avg_rtt[s]) * (rtts[i] - avg_rtt[s]);
            stddev[s] = sqrt(sum_sq / (NUM_ITERATIONS - SKIP_ITER));
        }

        free(buffer);
    }

    if (rank == 0) {
        for (int s = 0; s < num_sizes; s++)
            printf("%d %.6e %.6e\n", sizes[s] / 1024, avg_rtt[s], stddev[s]);
        free(avg_rtt);
        free(stddev);
    }

    MPI_Finalize();
    return 0;
}
