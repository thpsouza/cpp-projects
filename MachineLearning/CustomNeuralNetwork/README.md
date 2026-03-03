# CustomNeuralNetwork Framework

A C++ neural network framework built from scratch using the LinearAlgebra library.

## Features

- **Neural Network Class** - Configurable feedforward network
  - Flexible architecture design
  - Forward pass computation
  - Backward pass with gradient computation

- **Activation Functions**
  - ReLU (Rectified Linear Unit)
  - Sigmoid
  - Tanh

- **Loss Functions**
  - Mean Squared Error (MSE)

- **Optimizers**
  - Stochastic Gradient Descent (SGD)

- **Benchmarking Tools** - In-built performance measurement utilities


## 📁 Project Structure

```
MachineLearning/
└── CustomNeuralNetwork/
    ├── README.md
    ├── include/
    │   └── CustomNeuralNetwork/
    │       ├── NN.h
    │       ├── DenseLayer.h
    │       ├── ActivationFunctions/
    │       │   ├── ActivationFunctions.h
    │       │   ├── BaseActivationFunction.h
    │       │   ├── ReLUActivationFunction.h
    │       │   ├── SigmoidActivationFunction.h
    │       │   └── TanhActivationFunction.h
    │       ├── InitializationFunctions/
    │       │   ├── InitializationFunctions.h
    │       │   ├── BaseInitializationFunction.h
    │       │   ├── RandomInitializationFunction.h
    │       │   ├── HeInitializationFunction.h
    │       │   └── XavierInitializationFunction.h
    │       ├── LossFunctions/
    │       │   ├── LossFunctions.h
    │       │   ├── BaseLossFunction.h
    │       │   └── MeanSquaredErrorLossFunction.h
    │       └── Optimizers/
    │           ├── Optimizers.h
    │           ├── BaseOptimizer.h
    │           ├── AdaptativeMomentOptimizer.cpp (NOT IMPLEMENTED YET)
    │           └── StochasticGDOptimizer.h
    └── src/
        ├── NN.cpp
        ├── DenseLayer.cpp
        ├── ActivationFunctions/
        │   ├── BaseActivationFunction.cpp
        │   ├── ReLUActivationFunction.cpp
        │   ├── SigmoidActivationFunction.cpp
        │   └── TanhActivationFunction.cpp
        ├── InitializationFunctions/
        │   ├── BaseInitializationFunction.cpp
        │   ├── RandomInitializationFunction.cpp
        │   ├── HeInitializationFunction.cpp
        │   └── XavierInitializationFunction.cpp
        ├── LossFunctions/
        │   ├── BaseLossFunction.cpp
        │   └── MeanSquaredErrorLossFunction.cpp
        └── Optimizers/
            ├── BaseOptimizer.cpp
            ├── AdaptativeMomentOptimizer.cpp (NOT IMPLEMENTED YET)
            └── StochasticGDOptimizer.cpp
```


## Building

Manual compilation:

```powershell
clang++.exe -std=c++20 -c 
-I./CustomNeuralNetwork/include 
MachineLearning/CustomNeuralNetwork/src/**.cpp 
MachineLearning/CustomNeuralNetwork/src/ActivationFunctions/**.cpp 
MachineLearning/CustomNeuralNetwork/src/LossFunctions/**.cpp 
MachineLearning/CustomNeuralNetwork/src/Optimizers/**.cpp 
main.cpp -o main.exe
```

CMake:

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```


## Dependencies

- **LinearAlgebra** - Custom linear algebra library from parent directory


## 🎯 Current Limitations

- ⚠️ No batch normalization
- ⚠️ No regularization (L1/L2)
- ⚠️ Limited optimizer support


## Future Enhancements

- [ ] Batch normalization
- [ ] Dropout regularization
- [ ] More optimizers (Adam, RMSprop)
- [ ] Convolutional layers
- [ ] Recurrent layers
- [ ] GPU acceleration
