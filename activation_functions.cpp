#include "activation_functions.h"
#include <cmath>

inline double my_tanh(double x) {
    return (std::exp(x) - std::exp(-x)) / (std::exp(x) + std::exp(-x));
}

inline double tanh_derivative(double x) {
    double y = tanh(x);
    return 1 - std::pow(y, 2);
}

inline double sigmoid(double x) {
    return 1 / (1 + std::exp(-x));
}

inline double sigmoid_derivative(double x) {
    double y = sigmoid(x);
    return x - std::pow(x, 2);
}