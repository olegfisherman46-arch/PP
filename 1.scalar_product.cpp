#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    const int N = 100000;
    std::vector<double> A(N, 1.0); // Вектор из единиц
    std::vector<double> B(N, 2.0); // Вектор из двоек
    double sum = 0.0;

    // Распараллеливание цикла с суммированием через reduction для исключения состояния гонки 
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; ++i) {
        sum += A[i] * B[i];
    }

    std::cout << "Scalar product: " << sum << " (Expected: " << N * 2.0 << ")" << std::endl;
    return 0;
}
