#ifndef NN_MODEL_INITIALIZATION_FUNCTIONS_H
#define NN_MODEL_INITIALIZATION_FUNCTIONS_H

#include <memory>
#include "BaseInitializationFunction.h"
#include "HeInitializationFunction.h"
#include "RandomInitializationFunction.h"
#include "XavierInitializationFunction.h"

// Convenience macros for shorter syntax
#define HE std::make_unique<HeInitializationFunction>()
#define RANDOM std::make_unique<RandomInitializationFunction>()
#define XAVIER std::make_unique<XavierInitializationFunction>()

#endif //NN_MODEL_INITIALIZATION_FUNCTIONS_H