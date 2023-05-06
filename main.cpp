#include "activation_functions.cpp"

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <tuple>
#include <random>

using namespace std;

double mse_loss(std::vector<double> y_true, std::vector<double> y_pred) {
    double sum = 0.0;
    for (int i = 0; i < y_true.size(); i++) {
        sum += std::pow(y_true[i] - y_pred[i], 2);
    }
    return sum / y_true.size();
}

double mse_loss_derivative(std::vector<double> y_true, std::vector<double> y_pred) {
    double sum = 0.0;
    for (int i = 0; i < y_true.size(); i++) {
        sum += 2 * (y_pred[i] - y_true[i]);
    }
    return sum / y_true.size();
}

// some linear algebra. we want to:
// 1. store data in a matrix
// 2. preform matrix products
// 3. preform matrix addition
// 4. apply an element-wise operation to a matrix
//      - scalar multiplication
//      - subtraction
// 5. compute the transpose of a matrix

// To do this, let's store the Matrix as a one dimensional std::vector


class Matrix {
    public:
        size_t num_rows;
        size_t num_cols;
        size_t num_entries;
        std::vector<double> entries;
        std::tuple<size_t, size_t> shape;

    Matrix(size_t num_rows, size_t num_cols)
    : num_rows(num_rows), num_cols(num_cols), entries({}) {
        entries.resize(num_rows * num_cols);
        shape = {num_rows, num_cols};
    }
    Matrix() : num_rows(0), num_cols(0), entries({}) {
        shape = {0, 0};
    }

    void print() {
        for (size_t i = 0; i < num_cols; i++) {
            for (size_t j = 0; j < num_rows; j++) {
                std::cout << entries[num_rows * i + j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void print_shape() {
        std::cout << "Matrix(num_rows=" << num_rows << ", num_cols=" << num_cols << ")\n"; 
    }
};


int main() {
    std::vector<double> y_true = {1, 0, 0, 1};
    std::vector<double> y_pred = {0, 0, 0, 0};

    double loss = mse_loss(y_true, y_pred);

    std::cout << sigmoid(loss) << std::endl; // 0.5

    Matrix matrix;
    matrix.print();
    matrix.print_shape();

    return 0;
}