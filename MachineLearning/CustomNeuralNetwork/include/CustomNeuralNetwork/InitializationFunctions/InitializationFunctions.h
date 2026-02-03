#ifndef NN_MODEL_INITIALIZATION_FUNCTIONS_H
#define NN_MODEL_INITIALIZATION_FUNCTIONS_H

#include "BaseInitializationFunction.h"
#include "RandomInitializationFunction.h"
#include <memory>

// Convenience macros for shorter syntax
#define RANDOM std::make_unique<RandomInitializationFunction>()

#endif //NN_MODEL_INITIALIZATION_FUNCTIONS_H