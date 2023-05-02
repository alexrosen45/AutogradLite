#include <cmath>

double tanh(double x) {
    return (std::exp(x) - std::exp(-x)) / (std::exp(x) + std::exp(-x));
}

double tanh_derivative(double x) {
    double y = tanh(x);
    return 1 - std::pow(y, 2);
}