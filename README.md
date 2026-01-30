# C++ Projects Repository

A collection of C++ projects focusing on **Linear Algebra** and **Machine Learning** from scratch.

## 📁 Project Structure

```
cpp-projects/
├── README.md
├── build.ps1                          (Build script - PowerShell)
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
│       ├── Shape.cpp
│
└── MachineLearning/
    └── CustomNeuralNetwork/
        ├── README.md
        ├── include/
        │   └── CustomNeuralNetwork/
        │       ├── NN.h                       (Main NN class)
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
  -I./MachineLearning/CustomNeuralNetwork/src `
  (Get-ChildItem -Path './LinearAlgebra/src', './MachineLearning/CustomNeuralNetwork/src' -Filter '*.cpp' -Recurse | ForEach-Object { $_.FullName }) `
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

### Why not CMake?
- Faster iteration during development
- Simpler configuration
- Easier to debug

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
NN network();
network.initialize();
network.setActivationFunction(SIGMOID);
network.setLossFunction(MSE);
network.fit(x_train, y_train, 1000, 0.1);

// Predict
float prediction = network.predict({1.0f, 1.0f});
std::cout << "Prediction: " << prediction << std::endl;
```

## 🔧 Development Notes

### Code Organization
- **Public headers** in `include/` - user-facing API
- **Private headers** in `src/` - internal implementation details
- **Template implementations** in `.hpp` files

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

Created by Thiago - July 2024