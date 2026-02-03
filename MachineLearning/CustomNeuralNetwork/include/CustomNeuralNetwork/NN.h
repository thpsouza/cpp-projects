#ifndef NN_MODEL_H
#define NN_MODEL_H

// Standard lib includes
#include <vector>
#include <string>

// Custom lib includes
#include <LinearAlgebra/LinAlg.h>
#include <CustomNeuralNetwork/DenseLayer.h>

// Forward declarations
class BaseActivationFunction;
class BaseInitializationFunction;
class BaseLossFunction;
class BaseOptimizer;

// Implementation
class NN {
private:
    std::string model_name;
    int input_size;
    int output_dim;

    std::vector<DenseLayer> layers;
    std::vector<float> loss_history;
    bool initialized = false;

    std::unique_ptr<BaseInitializationFunction> initializer;
    std::unique_ptr<BaseActivationFunction> activation;
    std::unique_ptr<BaseLossFunction> loss;
    std::unique_ptr<BaseOptimizer> optimizer;

    Vector y;
    const Vector* last_input;

public:
    // Constructor/Destructor
    NN(int input_size, int num_hidden_layers, int hidden_layers_dim, int output_dim);
    NN(std::string model_name, int input_size, int num_hidden_layers, int hidden_layers_dim, int output_dim);

    // Getters/Setters
    float getOutput() const;
    const std::vector<float>& getLossHistory() const;
    void setActivationFunction(std::unique_ptr<BaseActivationFunction> function);
    void setInitializationFunction(std::unique_ptr<BaseInitializationFunction> init);
    void setLossFunction(std::unique_ptr<BaseLossFunction> function);
    void setOptimizer(std::unique_ptr<BaseOptimizer> opt, float learning_rate=1e-3);

    // Methods
    void initialize();
    void forward(const float* x);
    void backward(float y_target);
    void fit(const Matrix& x_train, const Matrix& y_train, size_t epochs=100, int print_count=20);
    float predict(const std::initializer_list<float>& x);

    void print() const;
    void save();
};


#endif //NN_MODEL_H
