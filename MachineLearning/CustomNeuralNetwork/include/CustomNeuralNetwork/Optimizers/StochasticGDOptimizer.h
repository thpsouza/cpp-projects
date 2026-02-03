#ifndef NN_MODEL_SGD_OPTIMIZER_H
#define NN_MODEL_SGD_OPTIMIZER_H

#include "BaseOptimizer.h"


class StochasticGDOptimizer : public BaseOptimizer {
public:
    explicit StochasticGDOptimizer(float lr = 1e-3);
    ~StochasticGDOptimizer() = default;

    void update(Matrix& w, Vector& b, float grad, const float* last_input, int signal_size) override;
};


#endif //NN_MODEL_SGD_OPTIMIZER_H
