#include "activation_functions.cpp"

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <tuple>
#include <random>
#include <functional> // enables references to functions as input

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
        // colums are stacked in order
        std::vector<double> entries;
        std::tuple<size_t, size_t> shape;

    Matrix(size_t num_rows, size_t num_cols):
    num_rows(num_rows), num_cols(num_cols), entries({}) {
        entries.resize(num_rows * num_cols);
        shape = {num_rows, num_cols};
    }
    Matrix() : num_rows(0), num_cols(0), entries({}) {
        shape = {0, 0};
    }

    void print() {
        if (num_rows == 0 && num_cols == 0) {
            std::cout << "Matrix object is empty\n";
        }
        else {
            for (size_t i = 0; i < num_cols; i++) {
                for (size_t j = 0; j < num_rows; j++) {
                    std::cout << entries[num_rows * i + j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }

    void print_shape() {
        std::cout << "Matrix(num_rows=" << num_rows << ", num_cols=" << num_cols << ")\n"; 
    }

    double& operator()(size_t i, size_t j) {
        // return a reference to the element in the i-th column and j-th row (zero-indexed)
        return entries[num_rows * i + j];
    }

    // naive matrix multiplication (change later!!!)
    Matrix multiply(Matrix &other_matrix) {
        // assumes num_cols == matrix.num_rows
        Matrix new_matrix(other_matrix.num_cols, num_rows);
        for (size_t i = 0; i < new_matrix.num_rows; i++) {
            for (size_t j = 0; j < new_matrix.num_cols; j++) {
                for (size_t k = 0; k < other_matrix.num_rows; k ++) {
                    new_matrix(i, j) += (*this)(j, k) * other_matrix(k, i);
                }
            }
        }
        return new_matrix;
    }

    Matrix multiply_elementwise(Matrix &other_matrix) {
        // assume shape == other_matrix.shape
        Matrix new_matrix((*this));
        for (size_t i = 0; i < num_rows; i++) {
            for (size_t j = 0; j < num_cols; j++) {
                new_matrix(i, j) = (*this)(i, j) * other_matrix(i, j);
            }
        }
        return new_matrix;
    }

    Matrix multiply_scalar(double scalar) {
        Matrix new_matrix((*this));
        for (size_t i = 0; i < num_rows; i++) {
            for (size_t j = 0; j < num_cols; j++) {
                new_matrix(i, j) = (*this)(i, j) * scalar;
            }
        }
        return new_matrix;
    }

    Matrix add_elementwise(Matrix &other_matrix) {
        Matrix new_matrix(num_rows, get<1>(other_matrix.shape));
        for (size_t i = 0; i < num_rows; ++i) {
            for (size_t j = 0; j < num_cols; ++j) {
                new_matrix(i, j) = (*this)(i, j) + other_matrix(i, j);
            }
        }
        return new_matrix;
    }
    Matrix operator+(Matrix &other_matrix) {
        return add_elementwise(other_matrix);
    }

    Matrix subtract_elementwise(Matrix &other_matrix) {
        Matrix new_matrix(num_rows, get<1>(other_matrix.shape));
        for (size_t i = 0; i < num_rows; ++i) {
            for (size_t j = 0; j < num_cols; ++j) {
                new_matrix(i, j) = (*this)(i, j) - other_matrix(i, j);
            }
        }
        return new_matrix;
    }
    Matrix operator+(Matrix &other_matrix) {
        return add_elementwise(other_matrix);
    }

    Matrix transpose() {
        Matrix transpose(num_cols, num_rows);
        for (size_t i = 0; i < num_cols; i++) {
            for (size_t j = 0; j < num_rows; j++) {
                transpose(i, j) = (*this)(j, i);
            }
        }
        return transpose;
    }

    Matrix apply_function_elementwise(const std::function<double(const double&)> &f) {
        Matrix new_matrix((*this));
        for (size_t i = 0; i < num_rows; i++) {
            for (size_t j = 0; j < num_cols; j++) {
                new_matrix(i, j) = f((*this)(i, j));
            }
        }
        return new_matrix;
    }
};

struct matrix {
    static Matrix ones(size_t num_rows, size_t num_cols) {
        Matrix M(num_rows, num_cols);
        for (size_t i = 0; i < num_rows; i++){
            for (size_t j = 0; j < num_cols; j++) {
                M(i, j) = 1.0;
            }
        }
        return M;
    }

    static Matrix randn(size_t num_rows, size_t num_cols) {
        Matrix M(num_rows, num_cols);

        std::random_device rd{};
        std::mt19937 gen{rd()};

        // Gaussian distribution with mean = 0
        // and standard deviation = 1 / sqrt(num_entries)

        double n(M.num_entries);
        double stdev{1 / sqrt(n)};
        std::normal_distribution<double> d{0, stdev};

        // fill each element using distribution
        for (size_t i = 0; i < num_rows; i++){
            for (size_t j = 0; j < num_cols; j++) {
                M(i, j) = d(gen);
            }
        }
        return M;
    }
};


class MultiLayerPerceptron {
    public:
        std::vector<size_t> units_per_layer;
        std::vector<Matrix> weights;
        std::vector<Matrix> biases;
        std::vector<Matrix> activations;
        float r; // learning rate

    MultiLayerPerceptron(std::vector<size_t> units_per_layer, float r=.01f):
    units_per_layer(units_per_layer), weights(), biases(), activations(), r(r) {
        for (size_t i = 0; i < units_per_layer.size(); i++) {
            size_t num_in{units_per_layer[i]};
            size_t num_out{units_per_layer[i+1]};

            // without random variables
            auto W = matrix::ones(num_out, num_in);
            auto b = matrix::ones(num_out, 1);

            weights.push_back(W);
            biases.push_back(b);

            activations.resize(units_per_layer.size());
        }
    }

    double forward(Matrix M) {
        activations[0] = M;
        Matrix prev(M);

        for (int i = 0; i < units_per_layer.size() - 1; i++) {
            // output is f(WX + b) for weights W, input X,
            // bias b, and activation function f
            Matrix output = (weights[i].multiply(prev)) + biases[i];
            output = apply_function_elementwise(sigmoid);
            
            prev = output;
            activations[i+1] = output;
        }
        // last 'prev' is network output
        return prev;
    }
};


int main() {
    std::vector<double> y_true = {1, 0, 0, 1};
    std::vector<double> y_pred = {0, 0, 0, 0};

    double loss = mse_loss(y_true, y_pred);

    std::cout << sigmoid(loss) << std::endl; // 0.5

    auto M = matrix::randn(2, 2);
    M.print_shape();
    M.print();

    return 0;
}