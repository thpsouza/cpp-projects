# C++ Projects Repository

A collection of C++ projects focusing on **Linear Algebra** and **Machine Learning** from scratch.

## 📁 Project Structure

```
cpp-projects/
├── README.md
├── build.ps1                          (Build script)
├── main.cpp                           (Entry point)
├── LinearAlgebra/
│   ├── README.md
│   ├── include/
│   │   └── LinearAlgebra/
│   │       ├── LinAlg.h               (PUBLIC - main entry point)
│   │       ├── Matrix.h               (PUBLIC - Matrix API)
│   │       ├── Vector.h               (PUBLIC - Vector API)
│   │       ├── Shape.h                (PUBLIC - Shape class)
│   │       └── Functions.h            (PUBLIC - utility functions)
│   └── src/
│       └── Shape.cpp
│
├── MachineLearning/
│    └── CustomNeuralNetwork/
│        ├── README.md
│        ├── include/
│        │   └── CustomNeuralNetwork/
│        │       ├── NN.h                       (Main NN class)
│        │       ├── DenseLayer.h
│        │       ├── ActivationFunctions/
│        │       │   ├── ActivationFunctions.h
│        │       │   ├── BaseActivationFunction.h
│        │       │   ├── ReLUActivationFunction.h
│        │       │   ├── SigmoidActivationFunction.h
│        │       │   └── TanhActivationFunction.h
│        │       ├── InitializationFunctions/
│        │       │   ├── InitializationFunctions.h
│        │       │   ├── BaseInitializationFunction.h
│        │       │   ├── HeInitializationFunction.h
│        │       │   └── XavierInitializationFunction.h
│        │       ├── LossFunctions/
│        │       │   ├── LossFunctions.h
│        │       │   ├── BaseLossFunction.h
│        │       │   └── MeanSquaredErrorLossFunction.h
│        │       └── Optimizers/
│        │           ├── Optimizers.h
│        │           ├── BaseOptimizer.h
│        │           ├── AdaptativeMomentOptimizer.cpp (NOT IMPLEMENTED YET)
│        │           └── StochasticGDOptimizer.h
│        └── src/
│            ├── NN.cpp
│            ├── DenseLayer.cpp
│            ├── ActivationFunctions/
│            │   ├── BaseActivationFunction.cpp
│            │   ├── ReLUActivationFunction.cpp
│            │   ├── SigmoidActivationFunction.cpp
│            │   └── TanhActivationFunction.cpp
│            │       ├── InitializationFunctions/
│            │       │   ├── BaseInitializationFunction.cpp
│            │       │   ├── HeInitializationFunction.cpp
│            │       │   └── XavierInitializationFunction.cpp
│            ├── LossFunctions/
│            │   ├── BaseLossFunction.cpp
│            │   └── MeanSquaredErrorLossFunction.cpp
│            └── Optimizers/
│                ├── BaseOptimizer.cpp
│                ├── AdaptativeMomentOptimizer.cpp (NOT IMPLEMENTED YET)
│                └── StochasticGDOptimizer.cpp
└── Utils/
    ├── include/
    │   ├── utils.h
    │   ├── Utils/       
    │   │   ├── benchmark.h
    │   │   └── print.h
    └── src/
        └── benchmark.cpp
```

## 🚀 Quick Start

### Prerequisites
- **Compiler**: Clang++ (MSYS2 clang64)
- **C++ Standard**: C++20
- **OS**: Windows (PowerShell)

### Build & Run

```powershell
# Navigate to workspace root
cd cpp-projects

# Build the project
./build.ps1

# Run the executable
./main.exe
```

### Alternative: Direct Compilation

```powershell
D:/msys64/clang64/bin/clang++.exe -std=c++20 -O3 `
  -I./LinearAlgebra/include `
  -I./MachineLearning/CustomNeuralNetwork/include `
  -I./Utils/include `
  (Get-ChildItem -Path './LinearAlgebra/src', './MachineLearning/CustomNeuralNetwork/src', './Utils/src', -Filter '*.cpp' -Recurse | ForEach-Object { $_.FullName }) `
  main.cpp -o neural-network.exe -Wall -Wextra
```

## 📚 Projects

### 1. LinearAlgebra Library
A lightweight linear algebra library with Matrix and Vector support.

**Features:**
- ✅ Matrix operations (addition, multiplication, transpose)
- ✅ Vector operations
- ✅ Shape validation
- ✅ Template-based (float/double support)

**Location:** `LinearAlgebra/`

### 2. CustomNeuralNetwork
A neural network framework built from scratch using the LinearAlgebra library.

**Features:**
- ✅ Single neuron architecture (expandable)
- ✅ Multiple activation functions (ReLU, Sigmoid, Tanh)
- ✅ Loss functions (Mean Squared Error)
- ✅ Optimizers (Stochastic Gradient Descent)
- ✅ Forward & backward propagation
- ✅ Training with fit() method

**Location:** `MachineLearning/CustomNeuralNetwork/`

## 🛠️ Build System

Currently using **direct clang++ compilation** via PowerShell script (`build.ps1`) for faster compile times.

**Future:** May migrate to CMake for larger projects.

## 📖 Usage Examples

### LinearAlgebra

```cpp
#include <LinearAlgebra/LinAlg.h>

// Create matrices
Matrix m1({{1, 2}, {3, 4}});
Matrix m2({{5, 6}, {7, 8}});

// Operations
Matrix result = m1 + m2;
Matrix product = m1 * m2;
result.print();
```

### CustomNeuralNetwork

```cpp
#include <LinearAlgebra/LinAlg.h>
#include <CustomNeuralNetwork/NN.h>

// Training data (XOR problem)
Matrix x_train({{0, 0}, {1, 0}, {0, 1}, {1, 1}});
Matrix y_train({{0}, {1}, {1}, {0}});

// Create and train neural network
int input_dim = 2;
int n_layers = 1;
int layers_dim = 2;
int output_dim = 1;
float learning_rate = 1e-2;
int epochs = 1e6;
NN network(input_dim, n_layers, layers_dim, output_dim);
network.setInitializationFunction(RANDOM);
network.setActivationFunction(ReLU);
network.setLossFunction(MSE);
network.setOptimizer(SGD, learning_rate);
network.initialize();
network.fit(x_train, y_train, epochs);

// Predict
float prediction = network.predict({1.0f, 1.0f});
std::cout << "Prediction: " << prediction << std::endl;
```

## 🔧 Development Notes

### Code Organization
- **Public headers** in `include/` - user-facing API
- **Private headers** in `src/` - internal implementation details
- **Template implementations** in `.h` and `.tpp` files

### Compilation Strategy
1. Forward declarations in headers reduce compile time
2. Full includes only in `.cpp` files
3. Templates instantiated explicitly where needed

### Performance Optimization
- Compiler flags: `-O3` (aggressive optimization)
- Link-time optimization ready
- SIMD-ready matrix operations (future)

## 🎯 TODO / Roadmap

- [ ] Add more activation functions (LeakyReLU, ELU)
- [ ] Implement more optimizers (Adam, RMSprop)
- [ ] Add convolutional layers
- [ ] Performance benchmarks
- [ ] Unit tests framework

## 📝 License

MIT License - Feel free to use for learning purposes.

## 👤 Author

Created by Thiago Souza - July 2024
Last Updated: 2026-01-31