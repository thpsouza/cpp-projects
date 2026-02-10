#include <CustomNeuralNetwork/LossFunctions/MeanSquaredErrorLossFunction.h>
#include <LinearAlgebra/LinAlg.h>
#include <cmath>


std::string MeanSquaredErrorLossFunction::getName() const {
    return "MSE";
}

float MeanSquaredErrorLossFunction::call(float y_predict, float y_target) const {
    return pow(y_target - y_predict, 2);
}

float MeanSquaredErrorLossFunction::grad(float y_predict, float y_target) const {
    return 2.0f * (y_predict - y_target);
}

Vector MeanSquaredErrorLossFunction::call(const Vector& y_predict, const Vector& y_target) const {
    return linalg::pow(y_target - y_predict, 2);
}

Vector MeanSquaredErrorLossFunction::grad(const Vector& y_predict, const Vector& y_target) const {
    return linalg::transform(y_predict, y_target, [](float p, float t) { return 2.0f*(p - t); });
}
