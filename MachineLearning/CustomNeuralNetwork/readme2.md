# CustomNeuralNetwork

A C++ neural network framework built from scratch using the LinearAlgebra library.

## 📁 Structure

```
CustomNeuralNetwork/
├── README.md
├── include/
│   └── CustomNeuralNetwork/
│       ├── NN.h
│       ├── ActivationFunctions/
│       │   ├── ActivationFunctions.h
│       │   ├── BaseActivationFunction.h
│       │   ├── ReLUActivationFunction.h
│       │   ├── SigmoidActivationFunction.h
│       │   └── TanhActivationFunction.h
│       ├── LossFunctions/
│       │   ├── LossFunctions.h
│       │   ├── BaseLossFunction.h
│       │   └── MeanSquaredErrorLossFunction.h
│       └── Optimizers/
│           ├── Optimizers.h
│           ├── BaseOptimizer.h
│           └── StochasticGDOptimizer.h
└── src/
    ├── NN.cpp
    ├── ActivationFunctions/
    │   ├── BaseActivationFunction.cpp
    │   ├── ReLUActivationFunction.cpp
    │   ├── SigmoidActivationFunction.cpp
    │   └── TanhActivationFunction.cpp
    ├── LossFunctions/
    │   ├── BaseLossFunction.cpp
    │   └── MeanSquaredErrorLossFunction.cpp
    └── Optimizers/
        ├── BaseOptimizer.cpp
        └── StochasticGDOptimizer.cpp
```

## 🚀 Quick Start

### Create a Simple Neural Network

```cpp
#include "LinearAlgebra/include/AlgLin.h"
#include "MachineLearning/CustomNeuralNetwork/include/NN.h"

// Training data
Matrix x_train({{0, 0}, {1, 0}, {0, 1}, {1, 1}});
Matrix y_train({{0}, {0}, {0}, {1}});

// Create network (input size = 2)
NN network(2);
network.initialize();

// Configure network
network.setActivationFunction(std::make_unique<SigmoidActivationFunction>());
network.setLossFunction(std::make_unique<MeanSquaredErrorLossFunction>());

// Train
network.fit(x_train, y_train, 1000, 0.1);

// Predict
float prediction = network.predict({1.0f, 1.0f});
```

## ✨ Features

### Activation Functions

| Function | Equation | Use Case |
|----------|----------|----------|
| **ReLU** | max(0, x) | Hidden layers |
| **Sigmoid** | 1/(1+e^-x) | Binary classification |
| **Tanh** | (e^x - e^-x)/(e^x + e^-x) | Hidden layers, [-1, 1] output |

### Loss Functions

| Function | Formula | Use Case |
|----------|---------|----------|
| **MSE** | 1/n Σ(ŷ - y)² | Regression, classification |

### Optimizers

| Optimizer | Update Rule | Learning Rate |
|-----------|------------|-----------------|
| **SGD** | w = w - lr × ∇L | Configurable |

## 📖 API Reference

### NN Class

```cpp
// Constructor
NN(int inputSize);

// Configuration
void setActivationFunction(std::unique_ptr<BaseActivationFunction> func);
void setLossFunction(std::unique_ptr<BaseLossFunction> func);

// Training & Prediction
void initialize();
void fit(const Matrix& x_train, const Matrix& y_train, 
         int epochs = 100, float lr = 1e-3);
float predict(const std::initializer_list<float>& x);

// Getters
float getOutput() const;
const std::vector<float>& getLossHistory() const;
```

### BaseActivationFunction

```cpp
class BaseActivationFunction {
    virtual float activate(float x) const = 0;
    virtual float derivative(float x) const = 0;
};
```

### BaseLossFunction

```cpp
class BaseLossFunction {
    virtual float compute(const Matrix& predictions, 
                         const Matrix& targets) const = 0;
    virtual Matrix derivative(const Matrix& predictions, 
                             const Matrix& targets) const = 0;
};
```

## 🔧 Compilation

Automatically compiled with main build script:

```powershell
./build.ps1
```

## 📊 Example: XOR Problem

```cpp
#include "LinearAlgebra/include/AlgLin.h"
#include "MachineLearning/CustomNeuralNetwork/include/NN.h"
#include <iostream>

int main() {
    // XOR training data
    Matrix x_train({
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    });
    
    Matrix y_train({
        {0},
        {1},
        {1},
        {0}
    });

    // Create and configure network
    NN nn(2);
    nn.initialize();
    nn.setActivationFunction(std::make_unique<SigmoidActivationFunction>());
    nn.setLossFunction(std::make_unique<MeanSquaredErrorLossFunction>());

    // Train
    nn.fit(x_train, y_train, 5000, 0.5);

    // Test predictions
    std::cout << "Predictions:" << std::endl;
    std::cout << "0 XOR 0 = " << nn.predict({0, 0}) << std::endl;
    std::cout << "0 XOR 1 = " << nn.predict({0, 1}) << std::endl;
    std::cout << "1 XOR 0 = " << nn.predict({1, 0}) << std::endl;
    std::cout << "1 XOR 1 = " << nn.predict({1, 1}) << std::endl;

    // Loss history
    const auto& loss_hist = nn.getLossHistory();
    std::cout << "\nFinal loss: " << loss_hist.back() << std::endl;

    return 0;
}
```

## 🎯 Current Limitations

- ⚠️ Single neuron architecture (multi-layer in development)
- ⚠️ No batch normalization
- ⚠️ No regularization (L1/L2)
- ⚠️ Limited optimizer support

## 🔮 Roadmap

- [ ] Multi-layer architecture
- [ ] Batch normalization
- [ ] Dropout regularization
- [ ] More optimizers (Adam, RMSprop)
- [ ] Convolutional layers
- [ ] Recurrent layers
- [ ] GPU acceleration

## 📄 License

MIT License