#ifndef NN_MODEL_XAVIER_INITIALIZATION_FUN_H
#define NN_MODEL_XAVIER_INITIALIZATION_FUN_H

#include "BaseInitializationFunction.h"

class XavierInitializationFunction : public BaseInitializationFunction {
public:
    void initialize(Matrix& w, Vector& b) const override;
};

#endif //NN_MODEL_XAVIER_INITIALIZATION_FUN_H
