#include <CustomNeuralNetwork/Optimizers/StochasticGDOptimizer.h>


SGDOptimizer::SGDOptimizer(float lr) : learning_rate(lr) {
}

void SGDOptimizer::update(float& weight, float gradient) {
    weight -= learning_rate * gradient;
}

void SGDOptimizer::setLearningRate(float lr) {
    learning_rate = lr;
}

float SGDOptimizer::getLearningRate() const {
    return learning_rate;
}
