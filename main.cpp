#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;

double mse_loss(std::vector<double> y_true, std::vector<double> y_pred) {
    double sum = 0.0;
    for (int i = 0; i < y_true.size(); i++) {
        sum += std::pow(y_true[i] - y_pred[i], 2);
    }
    return sum / y_true.size();
}

int main() {
    std::vector<double> y_true = {1, 0, 0, 1};
    std::vector<double> y_pred = {0, 0, 0, 0};

    std::cout << mse_loss(y_true, y_pred) << std::endl; // 0.5

    return 0;
}