#include <CustomNeuralNetwork/InitializationFunctions/HeInitializationFunction.h>
#include <cmath>
#include <random>

void HeInitializationFunction::initialize(Matrix& w, Vector& b) const {
    // Static generator to get a continuous sequence of random numbers in every call to initialize().
    static std::random_device rd;
    static std::mt19937 gen(rd());

    size_t n_inputs = w.getShape().rows;
    float std_deviation = std::sqrt(2.0f / n_inputs);
    std::normal_distribution<float> dist(0.0f, std_deviation);
    for (size_t i = 0; i < n_inputs; i++) {
        w[i] = dist(gen);
    }
    b[0] = 0.0f; // Biases are usually 0 for He
}