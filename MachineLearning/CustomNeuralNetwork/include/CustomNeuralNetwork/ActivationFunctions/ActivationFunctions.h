#ifndef NN_MODEL_ACTIVATION_FUNCTIONS_H
#define NN_MODEL_ACTIVATION_FUNCTIONS_H

#include <memory>
#include "BaseActivationFunction.h"
#include "SigmoidActivationFunction.h"
#include "ReLUActivationFunction.h"
#include "TanhActivationFunction.h"

// Convenience macros for shorter syntax
#define LINEAR std::make_unique<BaseActivationFunction>()
#define SIGMOID std::make_unique<SigmoidActivationFunction>()
#define RELU std::make_unique<ReLUActivationFunction>()
#define TANH std::make_unique<TanhActivationFunction>()

#endif //NN_MODEL_ACTIVATION_FUNCTIONS_H