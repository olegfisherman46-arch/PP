#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int A = rank + 5;
    int doubled = A * 2;

    if (rank == 0) {
        std::cout << "[Master] Total processes in COMM_WORLD: " << size << std::endl;
    }

    // Синхронизируем вывод для красоты в консоли
    MPI_Barrier(MPI_COMM_WORLD);

    std::cout << "Process " << rank << ": doubled value = " << doubled << std::endl;

    MPI_Finalize();
    return 0;
}
