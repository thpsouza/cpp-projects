#ifndef NN_MODEL_H
#define NN_MODEL_H

// Standard lib includes
#include <vector>
#include <string>

// Custom lib includes
#include <LinearAlgebra/LinAlg.h>

// Forward declarations
class BaseActivationFunction;
class BaseInitializationFunction;
class BaseLossFunction;
class BaseOptimizer;
class DenseLayer;


// Implementation
class NN {
private:
    std::string model_name;
    int input_size;
    int output_size;
    int layers_num = 0;
    // int HL;

    std::vector<DenseLayer> layers;
    std::vector<float> loss_history;
    bool initialized = false;

    std::unique_ptr<BaseInitializationFunction> initializer;
    std::unique_ptr<BaseActivationFunction> activation;
    std::unique_ptr<BaseLossFunction> loss;
    std::unique_ptr<BaseOptimizer> optimizer;

    Vector y_predict;
    Vector input_buffer;
    Vector target_buffer;
    const float* input_ptr;
    const float* target_ptr;

public:
    // Constructor/Destructor
    NN() = default;
    NN(int input_size, int output_size);
    NN(const std::string& model_name, int input_size, int output_size);
    NN(int input_size, int hidden_layers_num, int hidden_layers_dim, int output_size);
    NN(const std::string& model_name, int input_size, int hidden_layers_num, int hidden_layers_dim, int output_size);

    // Getters/Setters
    const Vector& getOutput() const;
    const std::vector<float>& getLossHistory() const;
    std::vector<DenseLayer>& getLayers();
    void setActivationFunction(std::unique_ptr<BaseActivationFunction> function);
    void setInitializationFunction(std::unique_ptr<BaseInitializationFunction> init);
    void setLossFunction(std::unique_ptr<BaseLossFunction> function);
    void setOptimizer(std::unique_ptr<BaseOptimizer> opt, float learning_rate=1e-3);

    // Methods
    void addLayer(DenseLayer& layer);
    void initialize();
    void forward(const float* input);
    void forward(const Vector& x);
    void backward(const float* target);
    void backward(const Vector& y_target);
    void fit(const Matrix& x_train, const Matrix& y_train, size_t epochs=100, int print_count=20);
    Vector& predict(Vector& x);
    Vector& predict(const std::initializer_list<float>& x);

    void validateNetwork(const std::string& caller) const;
    void print() const;
    void save();
    void save(const std::string& file_name);
    void auxiliaryInitializerGenerator(std::string &buffer);
    void auxiliaryLossGenerator(std::string &buffer);
    void auxiliaryOptimizerGenerator(std::string &buffer, float lr);
    void auxiliaryPreAllocatorFunction();
    void load(const std::string &file_name);
};


#endif //NN_MODEL_H
