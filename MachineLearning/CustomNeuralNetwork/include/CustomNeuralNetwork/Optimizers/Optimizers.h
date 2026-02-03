#ifndef NN_MODEL_OPTIMIZERS_H
#define NN_MODEL_OPTIMIZERS_H

#include "BaseOptimizer.h"
#include "StochasticGDOptimizer.h"
#include "AdaptativeMomentOptimizer.h"

// Convenience macros for shorter syntax
#define SGD std::make_unique<StochasticGDOptimizer>()
#define ADAM std::make_unique<AdaptativeMomentOptimizer>()

#endif //NN_MODEL_OPTIMIZERS_H