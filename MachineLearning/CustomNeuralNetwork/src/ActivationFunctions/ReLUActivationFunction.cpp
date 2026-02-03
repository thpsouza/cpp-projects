#include <CustomNeuralNetwork/ActivationFunctions/ReLUActivationFunction.h>
#include <LinearAlgebra/LinAlg.h>


std::string ReLUActivationFunction::getName() const {
    return "RELU";
}

float ReLUActivationFunction::call(float x) const {
    if (x>0) return x;
    else return 0.0f;
}

float ReLUActivationFunction::grad(float x) const {
    if (x>0) return 1.0f;
    else return 0.0f;
}

Matrix ReLUActivationFunction::call(const Matrix& x) const {
    // Manually implemented to be faster than (x>0)*x
    Matrix result = x;
    for (size_t i = 0; i<result.getShape().N; i++) {
        if (result[i] < 0) {
            result.setElement(0, i);
        }
    }
    return result;
}

Matrix ReLUActivationFunction::grad(const Matrix& x) const {
    return (x>0);
}