#ifndef NN_MODEL_SGD_OPTIMIZER_H
#define NN_MODEL_SGD_OPTIMIZER_H

#include "BaseOptimizer.h"


class StochasticGDOptimizer : public BaseOptimizer {
public:
    explicit StochasticGDOptimizer(float lr = 1e-3);
    ~StochasticGDOptimizer() = default;
    std::string getName() const override;
    void update(Matrix& w, Vector& b, float grad, const float* input, int signal_size) override;
    void update(Matrix& w, Vector& b, const Vector& delta, const Vector& input) override;
};


#endif //NN_MODEL_SGD_OPTIMIZER_H
