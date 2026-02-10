#include <CustomNeuralNetwork/Optimizers/StochasticGDOptimizer.h>
#include <LinearAlgebra/LinAlg.h>


StochasticGDOptimizer::StochasticGDOptimizer(float lr) : BaseOptimizer(lr) {
}

std::string StochasticGDOptimizer::getName() const {
    return "SGD";
}

void StochasticGDOptimizer::update(Matrix& w, Vector& b, float grad, const float* input, int signal_size) {
    for (size_t i = 0; i < signal_size; i++) {
        w[i] -= learning_rate * grad * input[i];
    }
    b[0] -= learning_rate * grad;
}

void StochasticGDOptimizer::update(Matrix &w, Vector &b,
                                   const Vector &delta,
                                   const Vector &input) {
    Shape S = w.getShape();
    for (size_t i = 0; i < S.rows; i++) {
        float cache = learning_rate * delta[i];
        for (size_t j = 0; j < S.cols; j++) {
            w[i*S.cols + j] -= cache * input[j];
        }
        b[i] -= cache;        
    }
}