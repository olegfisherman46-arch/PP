#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) std::cerr << "Run with at least 2 processes!" << std::endl;
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        int data_buffer[4];
        for (int src = 1; src < size; ++src) {
            MPI_Recv(data_buffer, 4, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Master received from process " << src << ": ";
            for (int i = 0; i < 4; ++i) {
                std::cout << data_buffer[i] << " ";
            }
            std::cout << std::endl;
        }
    } else {
        int my_array[4] = {rank, rank + 1, rank + 2, rank + 3};
        // Отправляем целиком массив из 4 элементов за один вызов
        MPI_Send(my_array, 4, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
