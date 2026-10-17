#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const long long N = 10000000;
    MPI_Barrier(MPI_COMM_WORLD);
    double t0 = MPI_Wtime();

    long long chunk = N / size;
    long long start = rank * chunk + 1;
    long long end   = (rank == size - 1) ? N : start + chunk - 1;

    long long local = 0, total = 0;
    for (long long i = start; i <= end; i++) local += i;

    MPI_Reduce(&local, &total, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double t1 = MPI_Wtime();
    if (rank == 0)
        std::cout << "Sum = " << total << "  Time = " << (t1 - t0) << " s\n";

    MPI_Finalize();
}
