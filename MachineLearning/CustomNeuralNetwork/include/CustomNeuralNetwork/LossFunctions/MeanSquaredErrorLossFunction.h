#ifndef NN_MODEL_MEAN_SQUARED_ERROR_LOSS_H
#define NN_MODEL_MEAN_SQUARED_ERROR_LOSS_H

#include "BaseLossFunction.h"

class MeanSquaredErrorLossFunction : public BaseLossFunction {
    public:
    float call(float y, float y_predict) const override;
    float grad(float y, float y_predict) const override;
};

#endif //NN_MODEL_MEAN_SQUARED_ERROR_LOSS_H