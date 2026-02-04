#include <CustomNeuralNetwork/InitializationFunctions/BaseInitializationFunction.h>
#include <LinearAlgebra/LinAlg.h>


std::string BaseInitializationFunction::getName() const {
    return "UNDEFINED";
}

void BaseInitializationFunction::operator()(Matrix &weights, Vector &biases) const {
    initialize(weights, biases);
}