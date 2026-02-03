#include <CustomNeuralNetwork/LossFunctions/MeanSquaredErrorLossFunction.h>
#include <cmath>


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
    return (y_predict - y_target) * 2.0f;
}
