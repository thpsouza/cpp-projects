#include <CustomNeuralNetwork/NN.h>
#include <CustomNeuralNetwork/DenseLayer.h>
#include <CustomNeuralNetwork/ActivationFunctions/ActivationFunctions.h>
#include <CustomNeuralNetwork/InitializationFunctions/InitializationFunctions.h>
#include <CustomNeuralNetwork/LossFunctions/LossFunctions.h>
#include <CustomNeuralNetwork/Optimizers/Optimizers.h>

#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <fstream>
#include <chrono>


// Constructor/Destructor
NN::NN(int input_size) : input_size(input_size)
{
}

NN::NN(const std::string& model_name, int input_size) : model_name(model_name), input_size(input_size)
{
}

NN::NN(int input_size, int hidden_layers_number, int hidden_layers_dim, int output_dim) :
    input_size(input_size),
    // output_dim(output_dim),
    layers_num(hidden_layers_number+1),
    // HL(hidden_layers_dim),
    activation(std::make_unique<BaseActivationFunction>()) 
{
    int i = 0;
    layers.push_back(DenseLayer(input_size, hidden_layers_dim, SIGMOID, 1));
    for(; i < hidden_layers_number - 1; ++i) {
        layers.push_back(DenseLayer(hidden_layers_dim, hidden_layers_dim, SIGMOID, i+2));
    }
    layers.push_back(DenseLayer(hidden_layers_dim, output_dim, SIGMOID, i+2));
}

NN::NN(const std::string& model_name, int input_size, int hidden_layers_number, int hidden_layers_dim, int output_dim) : 
    NN(input_size, hidden_layers_number, hidden_layers_dim, output_dim)
{
    this->model_name = model_name;
}

// Getters/Setters
const Vector& NN::getOutput() const {
  return y_predict;
}

const std::vector<float> &NN::getLossHistory() const {
    return loss_history;
}

std::vector<DenseLayer> &NN::getLayers() {
    return layers;
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
void NN::addLayer(DenseLayer& layer) {
    if (!layers.empty()) {
        if (layer.getInputDim() != layers.back().getOutputDim()) {
            throw std::invalid_argument("Layer input dimension must match previous layer output dimension!");
        }
    }
    layers.push_back(std::move(layer));
    layers_num += 1;
}


void NN::initialize() {
    if (!initializer) {
        throw std::runtime_error("No initialization function set! Use setInitializationFunction() before calling initialize().");
    }
    for (auto& layer : layers) {
        layer.initialize(initializer.get());
    }
    initialized = true;
}   

void NN::forward(const Vector& x) { // TODO: RIGHT NOW, ITS SPECIFIC TO XOR MODEL
    y_predict = layers[0].forward(x);
    y_predict = layers[1].forward(y_predict);
}

void NN::backward(Vector y_target) {
    // float dL_ds = loss->grad(y_predict, y_target);
    // float ds_dl = activation->grad(z_cache);
    // float grad = dL_ds * ds_dl;
    // optimizer->update(w, b, grad, last_input, input_size);
}

void NN::fit(const Matrix &x_train, const Matrix &y_train, size_t epochs, int print_count) {
    validateNetwork("fit");

    // Verify if the matrix matches the NN input size
    const Shape& sample_shape = x_train.getShape();
    if (sample_shape.cols != input_size) {
        throw std::invalid_argument("Matrix columns must match NN input size 'n'");
    }   

    float average_loss;
    size_t print_interval = (epochs <= print_count) ? 1 : (epochs / print_count);
    loss_history.reserve(print_count+1);

    // Training loop
    // std::cout << "Training:" << "\n";
    // for (size_t e = 0; e < epochs; e++) {
    //     float sample_loss = 0;
    //     for (size_t i = 0; i < sample_shape.rows; i++) {
    //         last_input = x_train.getRow(i);
    //         forward(last_input);
    //         float y_target = y_train(i, 0);
    //         backward(y_target);
    //         sample_loss += loss->call(y_predict, y_target);
    //     }
    //     average_loss = sample_loss / sample_shape.rows;
    //     if (e % print_interval == 0 || e == epochs - 1) { 
    //         loss_history.push_back(average_loss);
    //         std::cout << "Epoch: " << (e + 1) << "/" << epochs 
    //                   << " | Loss: " << average_loss << "\n";
    //     }
    // }       
}

Vector& NN::predict(const std::initializer_list<float>& x)
{
    // For tests only
    if (x.size() != input_size) {
        throw std::invalid_argument("Input size does not match NN dimension!");
    }
    buffer = x;
    forward(buffer); 
    return y_predict;
}


// Other methods
void NN::validateNetwork(const std::string& caller) const {
    if (layers.empty()) {
        throw std::runtime_error(
            std::format("No layers were added. Use addLayer() before calling {}().", caller)
        );
    }
    for (size_t i = 0; i < layers.size(); ++i) {
        if (!layers[i].getActivationFunction()) { 
            throw std::runtime_error(
                std::format("Layer {} activation function has not been set! Use layer.setActivationFunction() before calling {}().", 
                    i, caller)
            );
        }
    }
    if (!initialized) {
        throw std::runtime_error(
            std::format("The weights and bias have not been initialized yet! Use initialize() before calling {}().", caller)
        );
    }
    if (!loss) {
        throw std::runtime_error(
            std::format("Loss function has not been set yet! Use setLossFunction() before calling {}().", caller)
        );
    }
    if (!optimizer) {
        throw std::runtime_error(
            std::format("Optimizer function has not been set yet! Use setOptimizer() before calling {}().", caller)
        );
    }
}

void NN::print() const {
    validateNetwork("print");
    std::cout << "\n========================================\n";
    std::cout << std::format("NEURAL NETWORK SUMMARY: {}\n", model_name.empty() ? "Unnamed" : model_name);
    std::cout << std::format("LAYER COUNT {}\n", this->layers_num);
    std::cout << std::format("INITIALIZER {}\n", initializer->getName());
    std::cout << std::format("LOSS {}\n", loss->getName());
    std::cout << std::format("OPTIMIZER {} {}\n", optimizer->getName(), optimizer->getLearningRate());
    std::cout << "========================================\n";
    
    if (layers.empty()) {
        std::cout << " [Empty Network]\n";
    } else {
        for (auto& layer : layers) {
            layer.print();
            std::cout << "\n";
            // std::cout << "===============================\n";
        }
    }
    
    std::cout << "========================================\n";
}

void NN::save() {
    auto now = std::chrono::system_clock::now();
    std::string file_name = std::format("Model_{}_{:%Y%m%d_%H%M}.txt", this->model_name, now);
    this->save(file_name);
}

void NN::save(const std::string& file_name) {
    validateNetwork("save");
    std::ofstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for saving!" << std::endl;
    } else {
        file << std::format("MODEL {}\n", this->model_name);
        file << std::format("LAYER COUNT {}\n", this->layers_num);
        file << std::format("INITIALIZER {}\n", initializer->getName());
        file << std::format("LOSS {}\n", loss->getName());
        file << std::format("OPTIMIZER {} {}\n", optimizer->getName(), optimizer->getLearningRate());
        file << "------\n";
        for (auto& layer : layers) {
            layer.save(file);
            file << "-----\n";
        }
        std::cout << "Model saved to: " << file_name << std::endl;
    }
}


inline void NN::auxiliaryInitializerGenerator(std::string& buffer) {
    // Handle activation (MAY BE MOVED TO ITS OWN GENERATOR CLASS)
    if (buffer == "RANDOM") setInitializationFunction(RANDOM);
    else if (buffer == "XAVIER") setInitializationFunction(XAVIER);
    else if (buffer == "HE") setInitializationFunction(HE);
}

inline void NN::auxiliaryLossGenerator(std::string& buffer) {
    // Handle activation (MAY BE MOVED TO ITS OWN GENERATOR CLASS)
    if (buffer == "MSE") setLossFunction(MSE);
}

inline void NN::auxiliaryOptimizerGenerator(std::string& buffer, float lr) {
    // Handle activation (MAY BE MOVED TO ITS OWN GENERATOR CLASS)
    if (buffer == "SGD") setOptimizer(SGD, lr);
    // else if (buffer == "ADAM") setOptimizer(ADAM);
}

void NN::load(const std::string &file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::runtime_error(std::format("Could not load file: {}", file_name));
    }
    
    // Buffer to read the stream
    std::string buffer;
    
    // Summary
    file >> buffer >> model_name; // MODEL {NAME}
    file >> buffer >> buffer >> layers_num; // LAYER COUNT {NUMBER}
    
    // Initialization Function
    file >> buffer >> buffer; // INITIALIZER {FUNCTION}
    auxiliaryInitializerGenerator(buffer);
    this->initialized = true;
    
    // Loss Function
    file >> buffer >> buffer; // LOSS {FUNCTION}
    auxiliaryLossGenerator(buffer);
    
    // Optimizer
    float lr;
    file >> buffer >> buffer >> lr; // OPTIMIZER {OPTIMIZER} {LR}
    auxiliaryOptimizerGenerator(buffer, lr);
    
    // Layers
    file >> buffer; // Separator '-----'
    layers.clear();
    for (int i = 0; i < layers_num; i++) {
        DenseLayer layer;
        layer.load(file);
        layers.push_back(std::move(layer));
        file >> buffer; // Separator '-----'
    }
    std::cout << "Model loaded: " << model_name << "\n";
}