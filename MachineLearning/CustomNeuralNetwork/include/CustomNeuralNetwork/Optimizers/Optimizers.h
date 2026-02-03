#ifndef NN_MODEL_OPTIMIZERS_H
#define NN_MODEL_OPTIMIZERS_H

#include "BaseOptimizer.h"
#include "StochasticGDOptimizer.h"

// Convenience macros for shorter syntax
#define SGD std::make_unique<StochasticGDOptimizer>()

#endif //NN_MODEL_OPTIMIZERS_H