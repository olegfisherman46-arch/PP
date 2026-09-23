#include <iostream>
#include <omp.h>

// Интегрируемая функция
double f(double x) {
    return x * x; 
}

int main() {
    double a = 0.0, b = 1.0;
    int n = 1000000;
    double h = (b - a) / n;
    double integral = 0.5 * (f(a) + f(b));

    #pragma omp parallel for reduction(+:integral)
    for (int i = 1; i < n; ++i) {
        integral += f(a + i * h);
    }
    integral *= h;

    std::cout << "Integral value: " << integral << " (Expected: ~0.333333)" << std::endl;
    return 0;
}
