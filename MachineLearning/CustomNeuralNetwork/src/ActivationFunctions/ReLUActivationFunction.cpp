#include <CustomNeuralNetwork/ActivationFunctions/ReLUActivationFunction.h>


float ReLUActivationFunction::call(float x) const {
    if (x>0) return x;
    else return 0.0f;
}

float ReLUActivationFunction::grad(float x) const {
    if (x>0) return 1.0f;
    else return 0.0f;
}