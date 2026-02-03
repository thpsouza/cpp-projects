#include <CustomNeuralNetwork/ActivationFunctions/SigmoidActivationFunction.h>
#include <LinearAlgebra/LinAlg.h>
#include <cmath>


std::string SigmoidActivationFunction::getName() const {
    return "SIGMOID";
}

float SigmoidActivationFunction::call(float x) const {
    return 1.0f/(1 + std::exp(-x));
}

float SigmoidActivationFunction::grad(float x) const {
    float aux = call(x);
    return aux * (1 - aux);
}

Matrix SigmoidActivationFunction::call(const Matrix& m) const {
    return linalg::transform(m, [this](float x) { return this->call(x); });
}

Matrix SigmoidActivationFunction::grad(const Matrix& m) const {
    return linalg::transform(m, [this](float x) { return this->grad(x); });
}