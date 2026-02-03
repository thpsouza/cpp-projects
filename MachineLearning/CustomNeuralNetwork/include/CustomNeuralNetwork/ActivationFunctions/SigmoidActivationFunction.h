#ifndef NN_MODEL_SIGMOID_ACTIVATION_FUN_H
#define NN_MODEL_SIGMOID_ACTIVATION_FUN_H

#include "BaseActivationFunction.h"


class SigmoidActivationFunction : public BaseActivationFunction {
public:
    // Constructor/Destructor
    // SigmoidActivationFunction() {};
    // ~SigmoidActivationFunction() {};

    // Override methods from base class
    std::string getName() const override;
    float call(float x) const override;
    float grad(float x) const override;
    Matrix call(const Matrix& x) const override;
    Matrix grad(const Matrix& x) const override;
};

#endif //NN_MODEL_SIGMOID_ACTIVATION_FUN_H

