#include <CustomNeuralNetwork/ActivationFunctions/BaseActivationFunction.h>
#include <LinearAlgebra/LinAlg.h>


// Constructor/Destructor 
BaseActivationFunction::BaseActivationFunction() {
}

BaseActivationFunction::~BaseActivationFunction() {
}

// Getters/Setters
std::string BaseActivationFunction::getName() const {
    return "LINEAR";
}

// Methods
float BaseActivationFunction::call(float x) const {
    return x;
}

float BaseActivationFunction::grad(float x) const {
    return 1;
}

Matrix BaseActivationFunction::call(const Matrix& x) const {
    return x;
}

Matrix BaseActivationFunction::grad(const Matrix& x) const {
    return Matrix();
}


// Overloads
float BaseActivationFunction::operator()(float x) const {
    return call(x);
}

Matrix BaseActivationFunction::operator()(const Matrix& x) const {
    return call(x);
}
