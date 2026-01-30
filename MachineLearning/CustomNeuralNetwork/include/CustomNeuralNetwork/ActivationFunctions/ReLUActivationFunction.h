#ifndef NN_MODEL_RELU_ACTIVATION_FUN_H
#define NN_MODEL_RELU_ACTIVATION_FUN_H

#include "BaseActivationFunction.h"

class ReLUActivationFunction : public BaseActivationFunction {
public:
    // Constructor/Destructor
    // ReLUActivationFunction() {};
    // ~ReLUActivationFunction() {};

    // Override methods from base class
    float call(float x) const override;
    float grad(float x) const override;
};

#endif //NN_MODEL_RELU_ACTIVATION_FUN_H
