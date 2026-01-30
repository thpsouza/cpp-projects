#include <CustomNeuralNetwork/ActivationFunctions/TanhActivationFunction.h>
#include <cmath>

float TanhActivationFunction::call(float x) const {
    return tanh(x);
}

float TanhActivationFunction::grad(float x) const {
    return 1 - pow(tanh(x),2);
}
