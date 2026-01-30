#include <CustomNeuralNetwork/NN.h>
#include <LinearAlgebra/LinAlg.h>
#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <time.h>


// Constructor/Destructor
NN::NN(int n) : n(n), activation(std::make_unique<BaseActivationFunction>()) {
    w.resize(n, 1);
    b.setSize(1);
}

// NN::~NN() {
// }


// Getters/Setters
float NN::getOutput() const {
    return y;
}

const std::vector<float> &NN::getLossHistory() const {
    return loss_history;
}

void NN::setActivationFunction(std::unique_ptr<BaseActivationFunction> function) {
    activation = std::move(function);
}

void NN::setLossFunction(std::unique_ptr<BaseLossFunction> function) {
    loss = std::move(function);
}

// void NN::setOptimizer(std::unique_ptr<BaseOptimizer> opt) {
//     optimizer = std::move(opt);
// }


// Network Methods
void NN::initialize() {
    initialized = true;
    srand(time(0));
    // #TODO: create the initialization functions
    for (size_t i = 0; i < n; i++) {
        w[i] = (float) rand()/ (float) RAND_MAX;
    }
    b = (float) rand()/ (float) RAND_MAX;
}

void NN::forward(const float* x) { // TODO: RIGHT NOW, ITS SPECIFIC TO 1 NEURON
    float sum = 0;
    for (size_t i = 0; i < n; i++) {
        sum += w[i] * x[i];
    }
    sum += b.getElement(0, 0);
    cache = sum;
    y = activation->call(sum);
}

void NN::fit(const Matrix &x_train, const Matrix &y_train, int epochs, float lr) {
    // Check if loss function has been set
    if (!initialized) {
        throw std::invalid_argument("The weights and bias have not been initialized yet! Use initialize() before calling fit().");
    }

    // Check if loss function has been set
    if (!loss) {
        throw std::invalid_argument("Loss function has not been set yet! Use setLossFunction() before calling fit().");
    }

    // Ensure the matrix matches the NN input size
    const Shape& sample_shape = x_train.getShape();
    if (sample_shape.cols != n) {
        throw std::invalid_argument("Matrix columns must match NN input size 'n'");
    }   

    std::vector<float> loss_history;
    loss_history.reserve(epochs);

    for (size_t e = 0; e < epochs; e++) {
        float sample_loss = 0;
        for (size_t i = 0; i < sample_shape.rows; i++) {
            const float* sample_ptr = x_train.getRow(i);
            forward(sample_ptr);
            sample_loss += loss->call(y, y_train(i, 0));
        }
        loss_history.push_back(sample_loss / sample_shape.rows);

        // if (e % 10 == 0) {  
        //     std::cout << "Epoch " << e << " / " << epochs 
        //               << " - Loss: " << loss_history[e] << "\n";
        // }

        std::cout << loss_history[e] << "\n";
    }       
}


float NN::predict(const std::initializer_list<float> &x)
{
    // For tests only
    if (x.size() != n) {
        throw std::invalid_argument("Input size does not match NN dimension!");
    }
    forward(x.begin()); 
    return y;
}

// Print
void NN::print() const {
    for (size_t i = 0; i < n; i++) {
        std::cout << w[i] << ", ";
    }
    b.print();
}   