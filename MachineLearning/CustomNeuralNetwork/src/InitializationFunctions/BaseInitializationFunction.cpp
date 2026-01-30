#include <CustomNeuralNetwork/InitializationFunctions/BaseInitializationFunction.h>

void BaseInitializationFunction::operator()(Matrix &weights, Vector &biases) const {
    initialize(weights, biases);
}