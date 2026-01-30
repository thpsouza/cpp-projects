#include <CustomNeuralNetwork/ActivationFunctions/BaseActivationFunction.h>


// Constructor/Destructor 
BaseActivationFunction::BaseActivationFunction() {
}

BaseActivationFunction::~BaseActivationFunction() {
}


// Methods
float BaseActivationFunction::call(float x) const {
    return x;
}

float BaseActivationFunction::grad(float x) const {
    return 1;
}

// Overloads
float BaseActivationFunction::operator()(float x) const {
    return call(x);
}
