#include <mpi.h>
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int numbers[3], received[3];
    if (rank == 0) {
        int bufsize = 3 * (sizeof(int) + MPI_BSEND_OVERHEAD);
        void* buf = malloc(bufsize);
        MPI_Buffer_attach(buf, bufsize);
        for (int i = 0; i < 3; i++) {
            numbers[i] = i * 10;
            MPI_Bsend(&numbers[i], 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            std::cout << "Process 0 sent " << numbers[i] << "\n";
        }
        MPI_Buffer_detach(&buf, &bufsize);
        free(buf);
    } else if (rank == 1) {
        for (int i = 0; i < 3; i++) {
            MPI_Recv(&received[i], 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Process 1 received " << received[i] << "\n";
        }
    }
    MPI_Finalize();
}
