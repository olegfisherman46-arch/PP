#include <mpi.h>
#include <iostream>
#include <vector>

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
        int num_slaves = size - 1;
        std::vector<double> data(num_slaves);
        for (int i = 0; i < num_slaves; ++i) {
            data[i] = (i + 1) * 11.11; // Заполнение массива данных
        }

        for (int dest = 1; dest < size; ++dest) {
            // Пересылаем data[dest-1] в процесс dest
            MPI_Send(&data[dest - 1], 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
        }
    } else {
        double received_double;
        MPI_Recv(&received_double, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Process " << rank << " received data: " << received_double << std::endl;
    }

    MPI_Finalize();
    return 0;
}
