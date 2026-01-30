#ifndef NN_MODEL_LOSS_FUNCTIONS_H
#define NN_MODEL_LOSS_FUNCTIONS_H

#include "BaseLossFunction.h"
#include "MeanSquaredErrorLossFunction.h"

// Convenience macros for shorter syntax
#define MSE std::make_unique<MeanSquaredErrorLossFunction>()

#endif //NN_MODEL_LOSS_FUNCTIONS_H