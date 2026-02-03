#include <CustomNeuralNetwork/Optimizers/AdaptativeMomentOptimizer.h>


AdaptativeMomentOptimizer::AdaptativeMomentOptimizer(float lr, float b1, float b2, float eps) : 
    learning_rate(lr), 
    beta1(b1), 
    beta2(b2), 
    epsilon(eps), 
    t(0) 
{
}


// void AdaptativeMomentOptimizer::update(float& weight, float gradient) {
//     // Increase time step once per weight update cycle 
//     // (Note: technically t should increase once per full backward pass)
//     t++; 
//     float* ptr = &weight;
//     m[ptr] = beta1 * m[ptr] + (1.0f - beta1) * gradient;
//     v[ptr] = beta2 * v[ptr] + (1.0f - beta2) * (gradient * gradient);
//     float m_hat = m[ptr] / (1.0f - std::pow(beta1, t));
//     float v_hat = v[ptr] / (1.0f - std::pow(beta2, t));
//     weight -= learning_rate * m_hat / (std::sqrt(v_hat) + epsilon);
// }