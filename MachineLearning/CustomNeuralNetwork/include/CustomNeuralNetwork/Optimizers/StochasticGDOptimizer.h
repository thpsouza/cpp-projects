#ifndef NN_MODEL_SGD_OPTIMIZER_H
#define NN_MODEL_SGD_OPTIMIZER_H

#include "BaseOptimizer.h"


class SGDOptimizer : public BaseOptimizer {
private:
    float learning_rate;

public:
    explicit SGDOptimizer(float lr = 0.01f);
    ~SGDOptimizer() = default;

    void update(float& weight, float gradient) override;

    // Setters/Getters
    void setLearningRate(float lr);
    float getLearningRate() const;
};


#endif //NN_MODEL_SGD_OPTIMIZER_H
