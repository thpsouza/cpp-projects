#ifndef NN_MODEL_HE_INITIALIZATION_FUNCTION_H
#define NN_MODEL_HE_INITIALIZATION_FUNCTION_H

#include "BaseInitializationFunction.h"

class HeInitializationFunction : public BaseInitializationFunction {
public:
    std::string getName() const override;
    void initialize(Matrix& w, Vector& b) const override;
};

#endif //NN_MODEL_HE_INITIALIZATION_FUNCTION_H