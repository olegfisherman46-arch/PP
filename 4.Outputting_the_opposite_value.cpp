#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Моделируем чтение: каждый процесс берет число, зависящее от его ранга
    double val = (rank + 1) * 1.5;
    double opp_val = -val;

    std::cout << "Process " << rank << ": read " << val << ", opposite is " << opp_val << std::endl;

    MPI_Finalize();
    return 0;
}
