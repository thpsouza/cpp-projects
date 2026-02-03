#ifndef NN_MODEL_MEAN_SQUARED_ERROR_LOSS_H
#define NN_MODEL_MEAN_SQUARED_ERROR_LOSS_H

#include "BaseLossFunction.h"
#include <LinearAlgebra/LinAlg.h>

class MeanSquaredErrorLossFunction : public BaseLossFunction {
    public:
    float call(float y_predict, float y_target) const override;
    float grad(float y_predict, float y_target) const override;
    Vector call(const Vector& y_predict, const Vector& y_target) const override;
    Vector grad(const Vector& y_predict, const Vector& y_target) const override;
};

#endif //NN_MODEL_MEAN_SQUARED_ERROR_LOSS_H