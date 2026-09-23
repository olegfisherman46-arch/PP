#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        double X = 42.42; // Вещественное число на главном процессе
        std::cout << "Process 0: Opposite of X is " << -X << std::endl;
    } else {
        std::cout << "Subordinate process. My rank is: " << rank << std::endl;
    }

    MPI_Finalize();
    return 0;
}
