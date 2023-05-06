#include <vector>
#include "activation_functions.h"

using namespace std;

class HiddenLayer {
    public:
        std::vector<double> input;
        std::vector<double> output;
        std::vector

    private:

}

class NeuralNetwork {
    public:
        int num_hidden_layers;
        int neurons_per_layer;

    private:

    double activation_function(double x) {
        return sigmoid(x)
    }

    double activation_function_derivative(double x) {
        return sigmoid_derivative(x)
    }

}