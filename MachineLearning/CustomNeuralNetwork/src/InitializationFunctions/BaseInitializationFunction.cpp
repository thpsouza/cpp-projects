#include <CustomNeuralNetwork/InitializationFunctions/BaseInitializationFunction.h>
#include <LinearAlgebra/LinAlg.h>


void BaseInitializationFunction::operator()(Matrix &weights, Vector &biases) const {
    initialize(weights, biases);
}