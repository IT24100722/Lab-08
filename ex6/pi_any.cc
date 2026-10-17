#include <mpi.h>
#include <iostream>
#include <random>
#include <vector>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const long long N = 10000000;
    long long n_local = N / size;
    if (rank == size - 1) n_local += N % size;

    MPI_Barrier(MPI_COMM_WORLD);
    double t0 = MPI_Wtime();

    std::mt19937 gen(12345 + rank);
    std::uniform_real_distribution<double> d(0.0, 1.0);
    long long hits = 0;
    for (long long i = 0; i < n_local; i++) {
        double x = d(gen), y = d(gen);
        if (x*x + y*y <= 1.0) hits++;
    }

    if (rank != 0) {
        MPI_Send(&hits, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    } else {
        long long total = hits, h;
        std::vector<int> order;
        MPI_Status st;
        for (int k = 1; k < size; k++) {
            MPI_Recv(&h, 1, MPI_LONG_LONG, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &st);
            total += h;
            order.push_back(st.MPI_SOURCE);
        }
        double t1 = MPI_Wtime();
        std::cout << "Pi = " << 4.0 * total / N << "  Time = " << (t1 - t0) << " s\n";
        std::cout << "Arrival order:";
        for (int s : order) std::cout << " " << s;
        std::cout << "\n";
    }
    MPI_Finalize();
}
