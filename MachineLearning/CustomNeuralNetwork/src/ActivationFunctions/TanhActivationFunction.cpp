#include <CustomNeuralNetwork/ActivationFunctions/TanhActivationFunction.h>
#include <cmath>


std::string TanhActivationFunction::getName() const {
    return "TANH";
}

float TanhActivationFunction::call(float x) const {
    return tanh(x);
}

float TanhActivationFunction::grad(float x) const {
    return 1 - pow(tanh(x),2);
}

Matrix TanhActivationFunction::call(const Matrix& m) const {
    return linalg::transform(m, [this](float x) { return this->call(x); });
}

Matrix TanhActivationFunction::grad(const Matrix& m) const {
    return linalg::transform(m, [this](float x) { return this->grad(x); });
}