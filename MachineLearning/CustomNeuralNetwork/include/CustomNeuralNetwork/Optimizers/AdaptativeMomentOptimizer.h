#ifndef NN_MODEL_ADAM_OPTIMIZER_H
#define NN_MODEL_ADAM_OPTIMIZER_H

#include "BaseOptimizer.h"
#include <unordered_map>
#include <cmath>

class AdaptativeMomentOptimizer : public BaseOptimizer {
private:
    float learning_rate, beta1, beta2, epsilon;
    int t; // Time step
    
    // Maps to store the first and second moments for each weight's memory address
    std::unordered_map<float*, float> m; 
    std::unordered_map<float*, float> v;

public:
    AdaptativeMomentOptimizer(float lr = 0.001f, float b1 = 0.9f, float b2 = 0.999f, float eps = 1e-8f);
    // void update(float& weight, float gradient) override;
};


#endif //NN_MODEL_ADAM_OPTIMIZER_H