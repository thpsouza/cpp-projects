#include <CustomNeuralNetwork/InitializationFunctions/XavierInitializationFunction.h>
#include <LinearAlgebra/LinAlg.h>
#include <cmath>
#include <random>


std::string XavierInitializationFunction::getName() const {
    return "XAVIER";
}

void XavierInitializationFunction::initialize(Matrix& w, Vector& b) const {
    // Static generator to get a continuous sequence of random numbers in every call to initialize().
    static std::random_device rd;
    static std::mt19937 gen(rd());

    size_t n = w.getShape().N;
    float std_deviation = std::sqrt(1.0f / n);
    std::normal_distribution<float> dist(0.0f, std_deviation);
    for (size_t i = 0; i < n; i++) {
        w[i] = dist(gen);
    }
    // By default, biases are initialized to zero.
    b = 0.0f;
}