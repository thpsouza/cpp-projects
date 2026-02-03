#include <iostream>
#include <random>
#include <algorithm>
#include <utility>
#include "MatrixErrors.h"
#include "Matrix.h"

namespace linalg {

    /// Constructors
    // For column vectors
    template <typename T>
    Matrix<T>::Matrix(std::vector<T> values) :
        shape(values.size(),1,values.size()),
        values(std::move(values))
    {
    }

    template <typename T>
    Matrix<T>::Matrix(size_t rows, size_t cols) :
        shape(rows, cols),
        values(rows*cols)
    {
    }

    template <typename T>
    Matrix<T>::Matrix(size_t value, size_t rows, size_t cols) :
        shape(rows, cols),
        values(rows*cols, value)
    {
    }

    template <typename T>
    Matrix<T>::Matrix(Shape shape) :
        shape(shape),
        values(shape.N)
    {
    }

    template <typename T>
    Matrix<T>::Matrix(std::vector<T> values, size_t rows, size_t cols) :
        shape(rows, cols),
        values(std::move(values))
    {
    }

    template <typename T>
    Matrix<T>::Matrix(std::vector<T> values, Shape shape) :
        shape(shape),
        values(std::move(values))
    {
    }

    template <typename T>
    Matrix<T>::Matrix(std::initializer_list<T> values) :
        shape(1, values.size()),
        values(values)
    {
    }

    template <typename T>
    Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> values) {
        // Infer shape from vector size
        shape = Shape(values.size(), values.begin()->size());
        
        // Flattening the 2D array into 1D
        std::vector<T> flattened;
        flattened.reserve(shape.N);
        for (const auto& row : values) {
            // Checking if all rows are the same size
            if (row.size() != shape.cols) {
                throw std::invalid_argument("The rows must be the same size.\n");
            }
            for (auto& value : row) {
                flattened.push_back(value);
            }
        }
        this->values = flattened;
    }

    
    /// Getter/Setter
    template <typename T>
    void Matrix<T>::setName(const std::string& name) {
        class_name = name;
    }

    template <typename T>
    void Matrix<T>::setElement(T newElement, size_t i, size_t j) {
        if (i>=shape.rows || j>=shape.cols) {
            throw IndexError(i, j, shape);
        }
        values[i*shape.cols + j] = newElement;
    }
    template <typename T>
    void Matrix<T>::setElement(T newElement, size_t i) {
        if (i>=shape.N) {
            throw IndexError(i, shape);
        }
        values[i] = newElement;
    }

    template <typename T> void Matrix<T>::setElements(std::vector<T> values) {
        resize(1, values.size());
        this->values = std::move(values);
    }

    template <typename T>
    void Matrix<T>::setElements(std::initializer_list<T> values) {
        resize(1, values.size());
        this->values = std::move(values);
    }
    
    template <typename T>
    void Matrix<T>::setElements(std::initializer_list<std::initializer_list<T>> values) {
        *this = Matrix<T>(values);
    }

    template <typename T>
    void Matrix<T>::setShape(size_t rows, size_t cols)  {
        // Guard to check if matrix is resizeable
        if (!isResizeable(*this, Shape(rows,cols))) {
            throw ResizeError(rows, cols, shape);
        }
        // Guards to deal with row and column vectors
        if (rows == 0) {
            shape.N = cols;
        }
        else if (cols == 0) {
            shape.N = rows;
        }
        else {
            shape.N = rows * cols;
        }
        shape.rows = rows;
        shape.cols = cols;
    }

    
    template <typename T>
    const Shape &Matrix<T>::getShape() const {
        return shape;
    }

    template <typename T>
    T Matrix<T>::getElement(size_t i) const {
        if (i>=shape.N) {
            throw IndexError(i, shape);
        }
        return values[i];
    }

    template <typename T>
    T &Matrix<T>::getElement(size_t i) {
        if (i>=shape.N) {
            throw IndexError(i, shape);
        }
        return values[i];
    }

    template <typename T>
    T Matrix<T>::getElement(size_t i, size_t j) const {
        if (i>=shape.rows || j>=shape.cols) {
            throw IndexError(i,j,shape);
        }
        return values[i*shape.cols + j];
    }

    template <typename T>
    T& Matrix<T>::getElement(size_t i, size_t j) {
        if (i>=shape.rows || j>=shape.cols) {
            throw IndexError(i, j, shape);
        }
        return values[i*shape.cols + j];
    }


    template <typename T>
    const std::vector<T>& Matrix<T>::getElements() const {
        return values;
    }

    template <typename T>
    std::vector<T> &Matrix<T>::getElements() {
        return values;
    }

    template <typename T>
    const T* Matrix<T>::getRow(size_t i) const {
        return this->operator()(i);
    }

    template <typename T>
    void Matrix<T>::resize(size_t newRows, size_t newCols) {
        shape.rows = newRows;
        shape.cols = newCols;
        shape.N = newRows*newCols;
        values.resize(shape.N);
    }

    // TODO: IMPLEMENT GET ROW FUNCTIONS
    // template <typename T>
    // std::vector<T> Matrix<T>::getRow(size_t k) const {
    //     return std::vector<T>();
    // }

    // template <typename T>
    // std::vector<T> &Matrix<T>::getRow(size_t k) {
    //     return std::vector<T>();
    // }

    /// Initializers
    template <typename T>
    Matrix<T> Matrix<T>::random(size_t rows, size_t cols, T floor, T ceil) {
        // First create an instance of an engine.
        std::random_device rnd_device;
        // Specify the engine and distribution.
        std::mt19937 mersenne_engine {rnd_device()};  // Generates random integers
        std::uniform_real_distribution<T> dist {floor, ceil};
        auto gen = [&](){
            return dist(mersenne_engine);
        };
        Matrix<T> M(rows, cols);
        std::generate(M.values.begin(), M.values.end(), gen);
        return M;
    }

    template <typename T>
    Matrix<T> Matrix<T>::random(Shape shape, T floor, T ceil) {
        return random(shape.rows, shape.cols, floor, ceil);
    }

    template <typename T>
    Matrix<T> Matrix<T>::zeros(size_t rows, size_t cols) {
        return {rows, cols};
    }

    template <typename T>
    Matrix<T> Matrix<T>::zeros(Shape shape) {
        return Matrix<T>(shape);
    }

    template <typename T>
    Matrix<T> Matrix<T>::ones(size_t rows, size_t cols) {
        std::vector<T> temp(rows*cols,1);
        return {std::move(temp), rows, cols};
    }

    template <typename T>
    Matrix<T> Matrix<T>::ones(Shape shape) {
        return ones(shape.rows, shape.cols);
    }

    template <typename T>
    Matrix<T> Matrix<T>::id(size_t rows, size_t cols) {
        Matrix<T> temp = Matrix<T>::zeros(rows, cols);
        for (size_t i=0; i<rows; i++) {
            for (size_t j=0; j<cols; j++) {
                if (i==j) {
                    temp.setElement(1,i,j);
                }
            }
        }
        return temp;
    }

    template <typename T>
    Matrix<T> Matrix<T>::id(Shape shape) {
        return id(shape.rows, shape.cols);
    }


    /// Methods
    // Pretty - printing
    template <typename T>
    void Matrix<T>::print() const {
        Matrix<T>::print(*this);
    }

    template <typename T>
    void Matrix<T>::print(const Matrix<T>& m) {
        std::cout << std::string(m) << std::endl;
    }

    // Copying
    template <typename T>
    Matrix<T> Matrix<T>::copy(const Matrix<T> &m) {
        return {m.values, m.shape};
    }

    // Operations
    template <typename T>
    Matrix<T> Matrix<T>::BaseNumberOp(const Matrix<T>&A, T x, int op) {
        Matrix<T> result(A.shape);
        switch (op) {
            case ADD:
                for (size_t i = 0; i < A.shape.N; i++) {result[i] = A[i] + x;}
                break;
            case SUB:
                for (size_t i = 0; i < A.shape.N; i++) {result[i] = A[i] - x;}
                break;
            case MUL:
                for (size_t i = 0; i < A.shape.N; i++) {result[i] = A[i] * x;}
                break;
            case DIV:
                if (x == 0) {
                    throw DivisionByZero();
                }
                for (size_t i = 0; i < A.shape.N; i++) {result[i] = A[i] / x;}
                break;
            default:
                std::cout << "Error." << std::endl;
        }
        return result;
    }

    template <typename T>
    Matrix<T> Matrix<T>::BaseMatricesOp(const Matrix<T> &A, const Matrix<T> &B, int op) {
        // Guard different shapes (for matrices)
        if (A.shape != B.shape) {
            throw MismatchedShapes(A.shape, B.shape);
        }
        // Guard different sizes (for vectors)
        else if (A.shape.N != B.shape.N) {
            throw MismatchedNumberOfElements(A.shape.N, B.shape.N);
        }
        // Operations
        Matrix<T> result(A.shape);
        switch (op) {
            case ADD:
                for (size_t i = 0; i < A.shape.N; i++) {result[i] = A[i] + B[i];}
                break;
            case SUB:
                for (size_t i = 0; i < A.shape.N; i++) {result[i] = A[i] - B[i];}
                break;
            case MUL:
                for (size_t i = 0; i < A.shape.N; i++) {result[i] = A[i] * B[i];}
                break;
            case DIV:
                for (size_t i = 0; i < A.shape.N; i++) {result[i] = A[i] / B[i];}
                break;
            default:
                std::cout << "Error." << std::endl;
        }
        return result;
    }

    template <typename T>
    Matrix<T> Matrix<T>::sum(const Matrix<T> &A, const Matrix<T> &B, bool subtract) {
        if (subtract) {
            return Matrix<T>::BaseMatricesOp(A, B, SUB);
        }
        return Matrix<T>::BaseMatricesOp(A, B, ADD);
    }

    template <typename T>
    Matrix<T> Matrix<T>::sum(const Matrix<T> &B, bool subtract) const {
        return sum(*this, B, subtract);
    }

    template <typename T>
    T Matrix<T>::accumulate() const {
        T S = 0;
        for (size_t i=0; i<this->shape.N; i++) {
            S+=this->values[i];
        }
        return S;
    }

    template <typename T>
    T Matrix<T>::mean() const {
        return this->accumulate() / (T)this->shape.N;
    }

    template <typename T>
    Matrix<T> Matrix<T>::multiply(const Matrix<T> &A, const Matrix<T> &B, bool divide) {
        if (divide) {
            return Matrix<T>::BaseMatricesOp(A, B, DIV);
        }
        return Matrix<T>::BaseMatricesOp(A, B, MUL);
    }

    template <typename T>
    Matrix<T> Matrix<T>::multiply(const Matrix<T> &B, bool divide) const {
        return multiply(*this, B, divide);
    }

    template <typename T>
    Matrix<T> Matrix<T>::dot(const Matrix<T> &A, const Matrix<T> &B) {
        if (A.shape.cols != B.shape.rows) {
            throw MismatchedShapes(A.shape, B.shape);
        }
        // Caches
        const T* A_ptr = A.values.data();
        size_t A_rows = A.shape.rows;
        size_t A_cols = A.shape.cols;
        const T* B_ptr = B.values.data();
        size_t B_cols = B.shape.cols;
        Matrix<T> result(A_rows, B_cols);
        T* result_ptr = result.values.data();
        // Looping first through A matrix
        for (size_t i=0; i<A_rows; i++) {
            for (size_t k=0; k<A_cols; k++) {
                T A_ik = A_ptr[i*A_cols + k];     
                // Internal loop with sequential acesses in memory (only j changes)
                for (size_t j=0; j<B_cols; j++) {
                    result_ptr[i*B_cols + j] += A_ik * B_ptr[k*B_cols + j];
                }
            }
        }
        return result;
    }

    // template <typename T>
    // Matrix<T> Matrix<T>::dot2(const Matrix<T> &A, const Matrix<T> &B) {
    //     if (A.shape.cols != B.shape.rows) {
    //         throw MismatchedShapes(A.shape, B.shape);
    //     }
    //     size_t A_cols = A.shape.cols;
    //     size_t B_cols = B.shape.cols;
    //     size_t A_rows = A.shape.rows;
    //     Matrix<T> result(A_rows, B_cols);
    //     for (size_t i=0; i<A_rows; i++) {
    //         for (size_t j=0; j<A_cols; j++) {
    //             for (size_t k=0; k<B_cols; k++) {
    //                 result(i,j) += A(i,k) * B(k,j);
    //             }
    //         }
    //     }
    //     return result;
    // }
    
    template <typename T>
    Matrix<T> Matrix<T>::dot(const Matrix<T> &B) const {
        return dot(*this, B);
    }

    template <typename T>
    Matrix<T> Matrix<T>::dotAdd(const Matrix<T> &W, const Matrix<T> &X, const Matrix<T> &B) {
        if (W.shape.cols != X.shape.rows) {
            throw MismatchedShapes(W.shape, X.shape);
        }
        if (W.shape.rows != B.shape.rows) {
            throw MismatchedShapes(W.shape, B.shape);
        }
        // Caches
        const T* W_ptr = W.values.data();
        const T* X_ptr = X.values.data();
        const T* B_ptr = B.values.data();
        size_t W_rows = W.shape.rows;
        size_t W_cols = W.shape.cols;
        size_t X_cols = X.shape.cols;
        Matrix<T> result(W_rows, X_cols);
        T* result_ptr = result.values.data();
        // dotAdd logic:
        for (size_t i=0; i<W_rows; i++) {
            // Applying biases first
            T bias_i = B_ptr[i];
            for (size_t j=0; j<X_cols; j++) {
                result_ptr[i*X_cols + j] = bias_i;
            }
            // Multiplication 
            for (size_t k=0; k<W_cols; k++) {
                T W_ik = W_ptr[i*W_cols + k];     
                // Internal loop with sequential acesses in memory (only j changes)
                for (size_t j=0; j<X_cols; j++) {
                    result_ptr[i*X_cols + j] += W_ik * X_ptr[k*X_cols + j];
                }
            }
        }
        return result;
    }

    template <typename T>
    Matrix<T> Matrix<T>::dotAdd(const Matrix<T> &X, const Matrix<T> &B) const {
        return dotAdd(*this, X, B);
    }

    template <typename T>
    inline void transposeBlock(T* A, T* B, size_t rows, size_t cols, size_t block_size) {
        // #pragma omp parallel for collapse(2)
        for (size_t i=0; i<rows; i+=block_size) {
            for (size_t j=0; j<cols; j+=block_size) {
                size_t i_end = std::min(i + block_size, rows);
                size_t j_end = std::min(j + block_size, cols);
                for (size_t bi = i; bi < i_end; bi++) {
                    for (size_t bj = j; bj < j_end; bj++) {
                        B[bj * rows + bi] = A[bi * cols + bj];
                    }
                }
            }
        }
    }
    
    template <typename T>
    void Matrix<T>::transpose() {
        // Dynamic calculation of block_size
        size_t block_size;
        size_t min_dim = std::min(shape.rows, shape.cols);
        if (min_dim < 16) block_size = 1;
        else if (min_dim < 64) block_size = 16;
        else if (min_dim < 128) block_size = 32;
        else block_size = 64;
        // Transposing logic
        std::vector<T> transposed_values(shape.N);
        T* A = values.data();
        T* B = transposed_values.data();
        transposeBlock(A, B, shape.rows, shape.cols, block_size);
        values = std::move(transposed_values);
        std::swap(shape.rows, shape.cols);
    }

    // template <typename T>
    // void Matrix<T>::transpose() {
    //     // is_transposed = !is_transposed;
    //     std::vector<T> transposed_values(shape.N);    
    //     for (size_t i = 0; i < shape.rows; ++i) {
    //         for (size_t j = 0; j < shape.cols; ++j) {
    //             transposed_values[j*shape.rows + i] = values[i*shape.cols + j];
    //         }
    //     }
    //     values = std::move(transposed_values);
    //     std::swap(shape.rows, shape.cols);
    // }
    
    template <typename T>
    void Matrix<T>::transpose(Matrix<T> &A) {
        A.transpose();
    }

    template <typename T>
    bool Matrix<T>::isResizeable(const Matrix<T>& A, Shape newShape) {
        if (
                (A.shape.rows == 0 && (A.shape.cols != newShape.N)) ||
                (A.shape.cols == 0 && (A.shape.rows != newShape.N)) ||
                (A.shape.rows*A.shape.cols != newShape.N)
                )
        {
            return false;
        }
        return true;
    }

    /// Overloaded operators
    // Number operations
    template <typename T>
    Matrix<T> Matrix<T>::operator+(T x) const {
        return Matrix<T>::BaseNumberOp(*this, x, ADD);
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator-(T x) const {
        return Matrix<T>::BaseNumberOp(*this, x, SUB);
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator*(T x) const {
        return Matrix<T>::BaseNumberOp(*this, x, MUL);
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator/(T x) const {
        return Matrix<T>::BaseNumberOp(*this, x, DIV);
    }

    // Matrices operations
    template <typename T>
    Matrix<T> Matrix<T>::operator+(const Matrix<T>& B) const {
        return Matrix<T>::BaseMatricesOp(*this, B, ADD);
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator-(const Matrix<T> &B) const {
        return Matrix<T>::BaseMatricesOp(*this, B, SUB);
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator*(const Matrix<T> &B) const {
        return Matrix<T>::BaseMatricesOp(*this, B, MUL);
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator/(const Matrix<T> &B) const {
        return Matrix<T>::BaseMatricesOp(*this, B, DIV);
    }

    // Matrix assign operations
    template <typename T>
    Matrix<T> &Matrix<T>::operator=(const Matrix<T> &B) {
        if (this != &B) {
            shape = B.shape;
            values = B.values;
        }
        return *this;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator=(Matrix<T> &&B) noexcept {
        if (this != &B) {
            shape = std::move(B.shape);
            values = std::move(B.values);
        }
        return *this;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &B) {
        *this = *this + B;
        return *this;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &B) {
        *this = *this - B;
        return *this;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &B) {
        *this = *this * B;
        return *this;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator/=(const Matrix<T> &B) {
        *this = *this / B;
        return *this;
    }

    // Scalar assign operations
    template <typename T>
    Matrix<T> &Matrix<T>::operator=(T x) {
        // for (size_t i = 0; i < this->shape.N; i++) {
        //     this->values[i] = x;
        // }
        std::fill(values.begin(), values.end(), x);
        return *this;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator+=(T x) {
        *this = *this + x;
        return *this;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator-=(T x) {
        *this = *this - x;
        return *this;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator*=(T x) {
        *this = *this * x;
        return *this;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator/=(T x) {
        *this = *this / x;
        return *this;
    }

    // Comparison /// Composing comparisons would require to loop through the array multiple times.
    template <typename T>
    Matrix<T> Matrix<T>::operator>(T x) const {
        Matrix<T> bools(this->shape);
        for (size_t i = 0; i<this->shape.N; i++) {
            if (this->values[i] > x) {
                bools.setElement(1, i);
            }
        }
        return bools;
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator<(T x) const {
        Matrix<T> bools(this->shape);
        for (size_t i = 0; i<this->shape.N; i++) {
            if (this->values[i] < x) {
                bools.setElement(1, i);
            }
        }
        return bools;
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator==(T x) const {
        Matrix<T> bools(this->shape);
        for (size_t i = 0; i<this->shape.N; i++) {
            if (this->values[i] == x) {
                bools.setElement(1, i);
            }
        }
        return bools;
    }

    template <typename T>
    Matrix<int> Matrix<T>::operator==(const Matrix<T> &B) const {
        Matrix<int> bools(shape);
        for (size_t i = 0; i<shape.N; i++) {
            bools.setElement((values[i] == B.getElement(i)), i);
        }
        return bools;
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator!=(T x) const {
        Matrix<T> bools(this->shape);
        for (size_t i = 0; i<this->shape.N; i++) {
            if (this->values[i] != x) {
                bools.setElement(1, i);
            }
        }
        return bools;
    }

    template <typename T>
    Matrix<T>::operator bool() const {
        return std::ranges::none_of(
                this->values.cbegin(),
                this->values.cend(),
                [](T x){return (x == 0);});
    }

    // Indexing
    // template <typename T>
    // std::vector<T> Matrix<T>::operator()(size_t i) const {
    //     std::vector<T> ret(shape.cols);
    //     for (size_t j = 0; j < shape.cols; j++) {
    //         ret[j] = getElement(i, j);
    //     }
    //     return ret;
    // }

    template <typename T>
    const T* Matrix<T>::operator()(size_t i) const {
        // if (i >= shape.rows) throw IndexError(i, shape);
        return &values[i * shape.cols];
    }

    template <typename T>
    T Matrix<T>::operator()(size_t i, size_t j) const {
        return getElement(i,j);
    }

    template <typename T>
    T& Matrix<T>::operator()(size_t i, size_t j) {
        return getElement(i,j);
    }

    template <typename T>
    T& Matrix<T>::operator[](size_t idx) {
        return values[idx];
    }

    template <typename T>
    T Matrix<T>::operator[](size_t idx) const {
        return values[idx];
    }


    // String representation
    template <typename T>
    Matrix<T>::operator std::string() const {
        std::string s = std::format("{} ({}x{}):\n", this->class_name, shape.rows, shape.cols);
        for (size_t i=0; i<shape.rows; i++) {
            s += " [ ";
            for (size_t j=0; j<shape.cols; j++) {
                s += std::format("{:>10.6f} ", getElement(i, j));
                
            }
            s += "]\n";
        }
        // Remove last "\n"
        if (!s.empty()) {
            s.pop_back();
        }
        return s;
    }

}