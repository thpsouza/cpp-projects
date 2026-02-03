#include <CustomNeuralNetwork/Optimizers/BaseOptimizer.h>


BaseOptimizer::BaseOptimizer(float lr) : learning_rate(lr) {
}

void BaseOptimizer::setLearningRate(float lr) {
  	learning_rate = lr;
}

float BaseOptimizer::getLearningRate() const {
    return learning_rate;
}

// void BaseOptimizer::setParameters(Matrix& weights, Vector& biases) {
//   for (size_t i = 0; i < input_size; i++) {
//         optimizer->addParameter(w[i]);
//     }
//     optimizer->addParameter(b[0]);
//     parameters.push_back(&param);
// }