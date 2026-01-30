#ifndef NN_MODEL_SIGMOID_ACTIVATION_FUN_H
#define NN_MODEL_SIGMOID_ACTIVATION_FUN_H

#include "BaseActivationFunction.h"

class SigmoidActivationFunction : public BaseActivationFunction {
public:
    // Constructor/Destructor
    // SigmoidActivationFunction() {};
    // ~SigmoidActivationFunction() {};

    // Override methods from base class
    float call(float x) const override;
    float grad(float x) const override;
};

#endif //NN_MODEL_SIGMOID_ACTIVATION_FUN_H

