#include <CustomNeuralNetwork/NN.h>
#include <CustomNeuralNetwork/ActivationFunctions/ActivationFunctions.h>
#include <CustomNeuralNetwork/InitializationFunctions/InitializationFunctions.h>
#include <CustomNeuralNetwork/LossFunctions/LossFunctions.h>
#include <CustomNeuralNetwork/Optimizers/Optimizers.h>

#include <iostream>
#include <stdlib.h>
#include <stdexcept>


// Constructor/Destructor
NN::NN(int input_size, int num_hidden_layers, int hidden_layers_dim, int output_dim) :
    input_size(input_size),
    output_dim(output_dim)
    L(num_hidden_layers),
    HL(hidden_layers_dim),
    activation(std::make_unique<BaseActivationFunction>()) 
{
    int i = 0;
    layers.push_back(DenseLayer(input_size, hidden_layers_dim, SIGMOID, 1));
    for(; i < num_hidden_layers - 1; ++i) {
        layers.push_back(DenseLayer(hidden_layers_dim, hidden_layers_dim, SIGMOID, i+2));
    }
    layers.push_back(DenseLayer(hidden_layers_dim, output_dim, SIGMOID, i+2));
}

NN::NN(std::string model_name, int input_size, int num_hidden_layers, int hidden_layers_dim, int output_dim) : 
    NN(input_size, num_hidden_layers, hidden_layers_dim, output_dim)
{
    this->model_name = model_name;
}

// Getters/Setters
float NN::getOutput() const {
  return y_predict;
}

const std::vector<float> &NN::getLossHistory() const {
    return loss_history;
}

void NN::setActivationFunction(std::unique_ptr<BaseActivationFunction> function) {
    activation = std::move(function);
}

void NN::setInitializationFunction(std::unique_ptr<BaseInitializationFunction> init) {
    initializer = std::move(init);
}

void NN::setLossFunction(std::unique_ptr<BaseLossFunction> function) {
    loss = std::move(function);
}

void NN::setOptimizer(std::unique_ptr<BaseOptimizer> opt, float learning_rate) {
    optimizer = std::move(opt);
    optimizer->setLearningRate(learning_rate);
    // optimizer->setParameters(w, b);
}


// Network Methods
void NN::initialize() {
    if (!initializer) {
        throw std::runtime_error("No initialization function set! Use setInitializationFunction() before calling initialize().");
    }
    initializer->initialize(w, b);
    initialized = true;
}

void NN::forward(const float* x) { // TODO: RIGHT NOW, ITS SPECIFIC TO 1 NEURON
    float sum = 0;
    for (size_t i = 0; i < input_size; i++) {
        sum += w[i] * x[i];
    }
    sum += b.getElement(0, 0);
    z_cache = sum;
    y_predict = activation->call(sum);
}

void NN::backward(float y_target) { // TODO: RIGHT NOW, ITS SPECIFIC TO 1 NEURON
    // float dL_ds = loss->grad(y_predict, y_target);
    // float ds_dl = activation->grad(z_cache);
    // float grad = dL_ds * ds_dl;

    float dL_ds2 = loss->grad(y_predict, y_target);
    float ds2_dl2 = activation->grad(z_cache);
    float grad = 0;
    optimizer->update(w, b, grad, last_input, input_size);
}

void NN::fit(const Matrix &x_train, const Matrix &y_train, size_t epochs, int print_count) {
    // Guards
    if (!activation) {
        throw std::runtime_error("Activation function has not been set yet! Use setActivationFunction() before calling fit().");
    }
    if (!loss) {
        throw std::runtime_error("Loss function has not been set yet! Use setLossFunction() before calling fit().");
    }
    if (!optimizer) {
        throw std::runtime_error("Optimizer has not been set yet! Use setOptimizer() before calling fit().");
    }
    if (!initialized) {
        throw std::runtime_error("The weights and bias have not been initialized yet! Use initialize() before calling fit().");
    }

    // Verify if the matrix matches the NN input size
    const Shape& sample_shape = x_train.getShape();
    if (sample_shape.cols != input_size) {
        throw std::invalid_argument("Matrix columns must match NN input size 'n'");
    }   

    float average_loss;
    std::vector<float> loss_history;
    size_t print_interval = (epochs <= print_count) ? 1 : (epochs / print_count);
    loss_history.reserve(print_count+1);

    // Training loop
    std::cout << "Training:" << "\n";
    for (size_t e = 0; e < epochs; e++) {
        float sample_loss = 0;
        for (size_t i = 0; i < sample_shape.rows; i++) {
            last_input = x_train.getRow(i);
            forward(last_input);
            float y_target = y_train(i, 0);
            backward(y_target);
            sample_loss += loss->call(y_predict, y_target);
        }
        average_loss = sample_loss / sample_shape.rows;
        if (e % print_interval == 0 || e == epochs - 1) { 
            loss_history.push_back(average_loss);
            std::cout << "Epoch: " << (e + 1) << "/" << epochs 
                      << " | Loss: " << average_loss << "\n";
        }
    }       
}

float NN::predict(const std::initializer_list<float> &x)
{
    // For tests only
    if (x.size() != input_size) {
        throw std::invalid_argument("Input size does not match NN dimension!");
    }
    forward(x.begin()); 
    return y_predict;
}


// Print
void NN::print() const {
    Shape s = w.getShape();
    std::cout << "Current state of the network: \n";
    for (size_t j=0; j<s.cols; j++) {
        for (size_t i=0; i<s.rows; i++) {
            std::cout << "w" << i+1 << j+1 << " = " << w(i,j) << ", ";
        }
        std::cout << "b" << j+1 << " = " << b[j] << "\n";
    }
}

void NN::save() {
    // std::string s = std::format("{}_\n", this->model_name, shape.rows, shape.cols);
}
