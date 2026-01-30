#include <CustomNeuralNetwork/ActivationFunctions/SigmoidActivationFunction.h>
#include <cmath>

float SigmoidActivationFunction::call(float x) const {
    return 1.0f/(1 + exp(-x));
}

float SigmoidActivationFunction::grad(float x) const {
    float aux = call(x);
    return aux * (1 - aux);
}
