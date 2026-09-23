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
        for (int src = 1; src < size; ++src) {
            int received_val;
            // Принимаем сообщения строго по порядку возрастания рангов src
            MPI_Recv(&received_val, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Master received from process " << src << " value: " << received_val << std::endl;
        }
    } else {
        int send_val = rank * 10; // Уникальное число для отправки
        MPI_Send(&send_val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
