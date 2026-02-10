#ifndef NN_MODEL_BASE_OPTIMIZER_H
#define NN_MODEL_BASE_OPTIMIZER_H

// Std lib includes
#include <string>

// Forward Declarations
#include <LinearAlgebra/LinAlgFwds.h>


class BaseOptimizer {
protected:
    float learning_rate;
    // std::vector<float>* parameters;
    
public:
    BaseOptimizer() = default;
    BaseOptimizer(float lr);
    virtual ~BaseOptimizer() = default;

    // Setters/Getters
    virtual std::string getName() const;
    void setLearningRate(float lr);
    float getLearningRate() const;
    // void setParameters(Matrix& weights, Vector& biases);

    // Updates a single weight given its gradient
    virtual void update(Matrix& w, Vector& b, float grad, const float* input, int signal_size) = 0;
    virtual void update(Matrix& weights, Vector& b, const Vector& delta, const Vector& input) = 0;
};


#endif // NN_MODEL_BASE_OPTIMIZER_H
