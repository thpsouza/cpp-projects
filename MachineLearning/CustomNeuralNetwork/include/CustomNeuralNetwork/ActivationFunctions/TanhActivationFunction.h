#ifndef NN_MODEL_TANH_ACTIVATION_FUN_H
#define NN_MODEL_TANH_ACTIVATION_FUN_H

#include "BaseActivationFunction.h"

class TanhActivationFunction : public BaseActivationFunction {
public:
    // Constructor/Destructor
    // TanhActivationFunction() {};
    // ~TanhActivationFunction() {};

    // Override methods from base class
    float call(float x) const override;
    float grad(float x) const override;
};

#endif //NN_MODEL_TANH_ACTIVATION_FUN_H

