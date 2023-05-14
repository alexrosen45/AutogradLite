// experimentational network

class MultiLayerPerceptron {
    public:
        size_t input_size;
        size_t output_size;
        size_t hidden_size;

    MultiLayerPerceptron(size_t input_size, size_t output_size, size_t hidden_size):
    input_size(input_size), output_size(output_size), hidden_size(hidden_size) {
        for (size_t i = 0; i < units_per_layer.size(); i++) {
            size_t num_in{units_per_layer[i]};
            size_t num_out{units_per_layer[i+1]};

            // without random variables
            auto W = matrix::randn(num_out, num_in);
            auto b = matrix::randn(num_out, 1);

            weights.push_back(W);
            bias_vectors.push_back(b);

            activations.resize(units_per_layer.size());
        }
    }
};