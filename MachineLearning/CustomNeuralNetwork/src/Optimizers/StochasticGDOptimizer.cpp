#include <CustomNeuralNetwork/Optimizers/StochasticGDOptimizer.h>


StochasticGDOptimizer::StochasticGDOptimizer(float lr) : BaseOptimizer(lr) {
}

void StochasticGDOptimizer::update(Matrix& w, Vector& b, float grad, const float* last_input, int signal_size) {
    for (size_t i = 0; i < signal_size; i++) {
        w[i] -= learning_rate * grad * last_input[i];
    }
    b[0] -= learning_rate * grad;
}
