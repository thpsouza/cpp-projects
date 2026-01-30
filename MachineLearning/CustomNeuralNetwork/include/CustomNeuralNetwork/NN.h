#ifndef NN_MODEL_H
#define NN_MODEL_H

#include <memory>
#include <vector>
#include <LinearAlgebra/LinAlg.h>
#include <CustomNeuralNetwork/ActivationFunctions/ActivationFunctions.h>
#include <CustomNeuralNetwork/LossFunctions/LossFunctions.h>
// #include <CustomNeuralNetwork/Optimizers/Optimizers.h"
// #include <CustomNeuralNetwork/InitializationFunctions/InitializationFunctions.h>

class NN {
private:
    // int input_dim;
    // int hidden_layers;
    // int hidden_layers_dim;
    // int output_dim;

    int n;
    Matrix w; 
    Vector b;
    float y;
    float cache;
    std::vector<float> loss_history;
    bool initialized = false;
    std::unique_ptr<BaseActivationFunction> activation;
    std::unique_ptr<BaseLossFunction> loss;
    // std::unique_ptr<BaseOptimizer> optimizer;

public:
    // Constructor/Destructor
    NN(int n);
    // ~NN();

    // Getters/Setters
    float getOutput() const;
    const std::vector<float>& getLossHistory() const;
    void setActivationFunction(std::unique_ptr<BaseActivationFunction> function);
    void setLossFunction(std::unique_ptr<BaseLossFunction> function);

    // Methods
    void initialize();
    void forward(const float* x);
    void backward();
    void fit(const Matrix& x_train, const Matrix& y_train, int epochs=100, float lr=1e-3);
    float predict(const std::initializer_list<float>& x);

    void print() const;
};


#endif //NN_MODEL_H
