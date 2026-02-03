#include <CustomNeuralNetwork/InitializationFunctions/RandomInitializationFunction.h>
#include <stdlib.h>
#include <time.h>


void RandomInitializationFunction::initialize(Matrix& w, Vector& b) const {
    // Static generator to get a continuous sequence of random numbers in every call to initialize().
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    size_t n = w.getShape().N;
    for (size_t i = 0; i < n; i++) {
        w[i] = dist(gen);
    }
    b = dist(gen) * 0.1f;
}