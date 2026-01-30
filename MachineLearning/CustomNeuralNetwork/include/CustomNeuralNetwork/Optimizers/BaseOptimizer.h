#ifndef NN_MODEL_BASE_OPTIMIZER_H
#define NN_MODEL_BASE_OPTIMIZER_H


class BaseOptimizer {
public:
    BaseOptimizer() = default;
    virtual ~BaseOptimizer() = default;

    // Updates a single weight given its gradient
    virtual void update(float& weight, float gradient) = 0;

    // TODO: Later add batch update methods to support matrix operations
    // virtual void updateBatch(Matrix& weights, const Matrix& gradients);
};


#endif // NN_MODEL_BASE_OPTIMIZER_H
