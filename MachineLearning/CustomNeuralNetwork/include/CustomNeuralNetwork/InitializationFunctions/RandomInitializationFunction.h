#ifndef NN_MODEL_RANDOM_INITIALIZATION_FUNCTION_H
#define NN_MODEL_RANDOM_INITIALIZATION_FUNCTION_H

#include "BaseInitializationFunction.h"

class RandomInitializationFunction : public BaseInitializationFunction {
public:
    void initialize(Matrix& w, Vector& b) const override;
};

#endif