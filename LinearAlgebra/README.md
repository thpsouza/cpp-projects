# Linear Algebra Library

A lightweight, header-based linear algebra library for C++ with support for matrices and vectors.

## Features

- **Matrix Class** - Template-based matrix supporting float, double, and other numeric types
  - Element-wise operations (add, subtract, multiply, divide)
  - Matrix multiplication (dot product)
  - Broadcasting and reshaping
  - Optimized transpose with cache-friendly block tiling

- **Vector Class** - Specialized matrix representing column vectors
  - All matrix operations
  - Row access via operator()

- **Utility Functions**
  - Random matrix generation
  - Matrix initialization (zeros, ones, identity)
  - Accumulate and mean calculations


## 📁 Structure

```
LinearAlgebra/
├── README.md
├── CMakeLists.txt
├── include/
│   └── LinearAlgebra/
│       ├── LinAlg.h               (Main header - include this)
│       ├── LinAlgFwds.h           (Forward declarations)
│       ├── Matrix.h               (Matrix class)
│       ├── Matrix.tpp
│       ├── Vector.h               (Vector class)
│       ├── Vector.tpp
|       ├── MatrixErrors.h         (Custom error classes)
│       ├── Shape.h                (Shape validation)
│       ├── Shape.tpp
│       ├── Functions.h            (Utility functions)
│       └── Functions.tpp
└── src/
    └── Shape.cpp
```


## Usage

### Basic Operations

```cpp
#include <LinearAlgebra/LinAlg.h>

// Create matrices
Matrix<float> A(3, 3);
Matrix<float> B = Matrix<float>::random(3, 3, 0.0f, 1.0f);

// Element-wise operations
Matrix<float> C = A + B;
Matrix<float> D = A * B;  // Element-wise multiplication

// Matrix multiplication
Matrix<float> E = A.dot(B);

// In-place operations
A += B;
A *= 2.0f;

// Row access
Vector<float> row = A(0);  // Get first row
```

### Transpose Operations

Two transpose implementations available:

```cpp
Matrix<float> M = Matrix<float>::random(1000, 1000);

// Optimized block transpose
M.transpose();
M.print();
```

### 📊 Data Types

Uses template-based design supporting:
- **float** (default, set in LinAlg.h)
- **double** (changeable)

```cpp
// In LinAlg.h
using precision = float;  // Change to double if needed

using Matrix = linalg::Matrix<precision>;
using Vector = linalg::Vector<precision>;
```


## Performance

The library uses optimized algorithms:
- **Cache-aware transpose** with configurable block size
- **Template specialization** for compile-time optimization
- **Move semantics** for efficient memory handling
- **SIMD-friendly** data layout (row-major)

## Building

Manual compilation:

```powershell
clang++.exe -std=c++20 -c -I./LinearAlgebra/include LinearAlgebra/src/Shape.cpp main.cpp -o main.exe
```

CMake:

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

## API Documentation

See the inline documentation in:
- [Matrix.h](include/LinearAlgebra/Matrix.h) - Main matrix class
- [Vector.h](include/LinearAlgebra/Vector.h) - Vector specialization
- [Shape.h](include/LinearAlgebra/Shape.h) - Shape management
