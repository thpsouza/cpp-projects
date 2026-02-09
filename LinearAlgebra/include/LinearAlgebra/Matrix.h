//
// Created by thiag on 22/07/2024.
//

#ifndef LINALG_CST_LIB_MATRIX_H
#define LINALG_CST_LIB_MATRIX_H

#include <vector>
#include <string>
#include "Shape.h"

namespace linalg {

    /**
     * @class Matrix
     * @brief Template-based matrix class supporting both float and double types.
     * 
     * Provides a comprehensive linear algebra interface with element-wise operations,
     * matrix multiplication, initialization functions, and operator overloads.
     * The matrix is stored as a 1D vector internally but supports 2D indexing.
     * 
     * @tparam T Numeric type (float, double, or other numeric types)
     * 
     * ## Public API Overview
     * - **Construction**: Variadic constructors for different input formats
     * - **Element Access**: Getters/setters for individual or bulk element access
     * - **Initialization**: Static factories for common matrices (zeros, ones, identity, random)
     * - **Operations**: Addition, subtraction, multiplication, division (element-wise and matrix)
     * - **Operators**: Comprehensive overloading for intuitive syntax
     * - **Utilities**: Copy, sum, mean, reshaping, and string conversion
     * 
     * ## Implementation Details
     * - Internally stored as flat std::vector for cache efficiency
     * - Shape tracks rows, columns, and total elements (N)
     * - All operations validate dimensions for safety
     * 
     * @see Shape, Vector, MatrixError
     */
    template <typename T>
    class Matrix {
    protected:
        Shape shape;
        std::vector<T> values;
        std::string class_name = "Matrix";

    private:
        enum OperationType {ADD, SUB, MUL, DIV};

        /**
         * @brief Helper for element-wise operations with scalars.
         * @private
         */
        static Matrix<T> BaseNumberOp(const Matrix<T>&A, T x, int op);
        
        /**
         * @brief Helper for element-wise operations between matrices.
         * @private
         */
        static Matrix<T> BaseMatricesOp(const Matrix<T>& A, const Matrix<T>& B, int op);

    public:
        // ========== CONSTRUCTORS ==========
        
        /**
         * @brief Default constructor. Creates empty matrix.
         */
        Matrix() = default;
        
        Matrix(const Matrix& other) = default;
        Matrix(Matrix&& other) noexcept = default;

        /**
         * @brief Constructs column vector from flat values.
         * Creates an Nx1 matrix from the provided values.
         * @param values Vector of elements
         */
        explicit Matrix(std::vector<T> values);
        
        
        /**
         * @brief Constructs matrix with given dimensions.
         * Initializes all elements to zero.
         * @param rows Number of rows
         * @param cols Number of columns
         */
        Matrix(size_t rows, size_t cols);
        Matrix(size_t value, size_t rows, size_t cols);
        
        
        /**
         * @brief Constructs matrix from Shape object.
         * Initializes all elements to zero.
         * @param shape Desired matrix dimensions
         */
        explicit Matrix(Shape shape);
        
        /**
         * @brief Constructs matrix from flat values with dimensions.
         * @param values Flattened element vector (row-major order)
         * @param rows Number of rows
         * @param cols Number of columns
         */
        Matrix(std::vector<T> values, size_t rows, size_t cols);
        
        /**
         * @brief Constructs matrix from values with Shape object.
         * @param values Flattened element vector
         * @param shape Desired dimensions
         */
        Matrix(std::vector<T> values, Shape shape);
        
        /**
         * @brief Constructs a single row matrix from 1D initializer list.
         * @param values Initializer list
         */
        Matrix(std::initializer_list<T> values);

        /**
         * @brief Constructs matrix from 2D initializer list.
         * Automatically infers dimensions from data.
         * 
         * @param values 2D nested initializer list (each row is an initializer_list)
         * @throw std::invalid_argument if rows have different lengths
         */
        Matrix(std::initializer_list<std::initializer_list<T>> values);

        // ========== ELEMENT ACCESS ==========
        void setName(const std::string& name);

        /**
         * @brief Sets single element at 2D position.
         * @param newElement Value to set
         * @param i Row index
         * @param j Column index
         * @throw IndexError if indices are out of bounds
         */
        void setElement(T newElement, size_t i, size_t j);
        
        /**
         * @brief Sets single element at 1D index.
         * @param newElement Value to set
         * @param i Linear index (row-major order)
         * @throw IndexError if index is out of bounds
         */
        void setElement(T newElement, size_t i);
        
        void setElements(std::vector<T> values);
        void setElements(std::initializer_list<T> values);
        void setElements(std::initializer_list<std::initializer_list<T>> values);

        /**
         * @brief Reshapes matrix to new dimensions.
         * Total element count must remain constant.
         * @param rows New number of rows
         * @param cols New number of columns
         * @throw ResizeError if total elements don't match
         */
        void setShape(size_t rows, size_t cols);
        
        /**
         * @brief Gets element at 2D position.
         * @param i Row index
         * @param j Column index
         * @return Element value
         * @throw IndexError if indices are out of bounds
         */
        [[nodiscard]] T getElement(size_t i, size_t j) const;
        
        /**
         * @brief Gets mutable reference to element at 2D position.
         * @param i Row index
         * @param j Column index
         * @return Reference to element
         * @throw IndexError if indices are out of bounds
         */
        T& getElement(size_t i, size_t j);
        
        /**
         * @brief Gets element at 1D index.
         * @param i Linear index
         * @return Element value
         * @throw IndexError if index is out of bounds
         */
        [[nodiscard]] T getElement(size_t i) const;
        
        /**
         * @brief Gets mutable reference to element at 1D index.
         * @param i Linear index
         * @return Reference to element
         */
        T& getElement(size_t i);

        /**
         * @brief Gets imutable reference to internal element vector.
         * @return Reference to internal values vector
         */
        const std::vector<T>& getElements() const;

        /**
         * @brief Gets mutable reference to internal element vector.
         * @warning Direct access bypasses bounds checking
         * @return Reference to internal values vector
         */
        std::vector<T>& getElements();

        /**
         * @brief Gets matrix shape (const reference).
         * Preferred for efficiency - returns reference instead of copy.
         * @return Const reference to shape
         */
        const Shape& getShape() const;
        
        /**
         */
        const T* getRow(size_t i) const;

        /**
         * @brief Resizes the matrix to new total number of elements.
         * @param newRows new number of rows
         * @param newCols new number of cols
         */
        void resize(size_t newRows, size_t newCols);

        // ========== INITIALIZATION ==========
        
        /**
         * @brief Creates random matrix with values in range [floor, ceil).
         * @param rows Number of rows
         * @param cols Number of columns
         * @param floor Minimum value (default 0)
         * @param ceil Maximum value (default 1)
         * @return New random matrix
         */
        static Matrix<T> random(size_t rows, size_t cols, T floor=0, T ceil=1);
        
        /**
         * @brief Creates random matrix from shape.
         * @param shape Matrix dimensions
         * @param floor Minimum value
         * @param ceil Maximum value
         * @return New random matrix
         */
        static Matrix<T> random(Shape shape, T floor=0, T ceil=1);
        
        /**
         * @brief Creates matrix filled with zeros.
         * @param rows Number of rows
         * @param cols Number of columns
         * @return New zero matrix
         */
        static Matrix<T> zeros(size_t rows, size_t cols);
        
        /**
         * @brief Creates zero matrix from shape.
         * @param shape Matrix dimensions
         * @return New zero matrix
         */
        static Matrix<T> zeros(Shape shape);
        
        /**
         * @brief Creates matrix filled with ones.
         * @param rows Number of rows
         * @param cols Number of columns
         * @return New ones matrix
         */
        static Matrix<T> ones(size_t rows, size_t cols);
        
        /**
         * @brief Creates ones matrix from shape.
         * @param shape Matrix dimensions
         * @return New ones matrix
         */
        static Matrix<T> ones(Shape shape);
        
        /**
         * @brief Creates identity (diagonal) matrix.
         * @param rows Number of rows
         * @param cols Number of columns
         * @return New identity matrix
         */
        static Matrix<T> id(size_t rows, size_t cols);
        
        /**
         * @brief Creates identity matrix from shape.
         * @param shape Matrix dimensions
         * @return New identity matrix
         */
        static Matrix<T> id(Shape shape);

        // ========== OPERATIONS ==========
        
        /**
         * @brief Prints matrix to stdout.
         */
        void print() const;
        
        /**
         * @brief Static print function for matrices.
         * @param m Matrix to print
         */
        static void print(const Matrix<T>& m);
        
        /**
         * @brief Creates deep copy of matrix.
         * @param m Source matrix
         * @return Independent copy with same values
         */
        static Matrix<T> copy(const Matrix<T>& m);
        
        /**
         * @brief Element-wise addition or subtraction of two matrices.
         * @param A First operand
         * @param B Second operand
         * @param subtract If true, performs subtraction (A - B), else addition (A + B)
         * @return Result matrix
         * @throw MismatchedShapes if dimensions don't match
         */
        static Matrix<T> sum(const Matrix<T>& A, const Matrix<T>&B, bool subtract=false);
        
        /**
         * @brief Element-wise multiplication or division of two matrices.
         * @param A First operand
         * @param B Second operand
         * @param divide If true, performs division (A / B), else multiplication (A * B)
         * @return Result matrix
         * @throw MismatchedShapes if dimensions don't match
         * @throw DivisionByZero if dividing by zero element
         */
        static Matrix<T> multiply(const Matrix<T>& A, const Matrix<T>& B, bool divide=false);
        
        /**
         * @brief Matrix multiplication (dot product).
         * Performs standard linear algebra matrix multiplication: (m x n) * (n x p) = (m x p)
         * @param A First operand
         * @param B Second operand
         * @return Result matrix with shape (A.rows x B.cols)
         * @throw MismatchedShapes if A.cols != B.rows
         */
        static Matrix<T> dot(const Matrix<T>& A, const Matrix<T>& B);
        // static Matrix<T> dot2(const Matrix<T>& A, const Matrix<T>& B);
        static Matrix<T> transposedDot(const Matrix<T> &W, const Matrix<T> &X);
        static Matrix<T> dotTransposed(const Matrix<T> &W, const Matrix<T> &X);
        static Matrix<T> dotAdd(const Matrix<T> &W, const Matrix<T> &X, const Matrix<T> &B);

        /**
         * 
         */
        static void transpose(Matrix<T>& A);


        /**
         * @brief Sums all elements in matrix.
         * @return Sum of all elements
         */
        [[nodiscard]] T accumulate() const;
        
        /**
         * @brief Computes mean of all elements.
         * @return Average value of all elements
         */
        [[nodiscard]] T mean() const;
        
        /**
         * @brief Instance method for element-wise sum.
         * @param B Second operand
         * @param subtract If true, subtracts B from this matrix
         * @return Result of this + B or this - B
         * @throw MismatchedShapes if dimensions don't match
         */
        [[nodiscard]] Matrix<T> sum(const Matrix<T>&B, bool subtract=false) const;
        
        /**
         * @brief Instance method for element-wise multiplication/division.
         * @param B Second operand
         * @param divide If true, divides this by B
         * @return Result of this * B or this / B
         */
        [[nodiscard]] Matrix<T> multiply(const Matrix<T>& B, bool divide=false) const;
        
        /**
         * @brief Instance method for matrix multiplication.
         * @param B Second operand
         * @return Result of matrix product (this * B)
         * @throw MismatchedShapes if this.cols != B.rows
         */
        [[nodiscard]] Matrix<T> dot(const Matrix<T>& B) const;
        [[nodiscard]] Matrix<T> dotAdd(const Matrix<T> &X, const Matrix<T> &B) const;
        [[nodiscard]] Matrix<T> transposedDot(const Matrix<T> &X) const;
        [[nodiscard]] Matrix<T> dotTransposed(const Matrix<T> &X) const;

        /**
         * 
         */
        void transpose();

        /**
         * @brief Checks if matrix can be safely reshaped.
         * @param A Matrix to check
         * @param newShape Target shape
         * @return true if reshape is valid (same total elements), false otherwise
         */
        static bool isResizeable(const Matrix<T> &A, Shape newShape);

        // ========== OPERATORS: SCALAR ==========
        
        /**
         * @brief Element-wise addition with scalar.
         * @param x Scalar to add
         * @return New matrix with x added to each element
         */
        Matrix<T> operator+(T x) const;
        
        /**
         * @brief Element-wise subtraction with scalar.
         * @param x Scalar to subtract
         * @return New matrix with x subtracted from each element
         */
        Matrix<T> operator-(T x) const;
        
        /**
         * @brief Element-wise multiplication with scalar.
         * @param x Scalar to multiply
         * @return New matrix with each element multiplied by x
         */
        Matrix<T> operator*(T x) const;
        
        /**
         * @brief Element-wise division with scalar.
         * @param x Scalar to divide by
         * @return New matrix with each element divided by x
         * @throw DivisionByZero if x is zero
         */
        Matrix<T> operator/(T x) const;

        // ========== OPERATORS: MATRIX-MATRIX ==========
        
        /**
         * @brief Element-wise addition of two matrices.
         * @param B Second operand
         * @return Sum matrix
         * @throw MismatchedShapes if dimensions differ
         */
        Matrix<T> operator+(const Matrix<T>& B) const;
        
        /**
         * @brief Element-wise subtraction of two matrices.
         * @param B Second operand
         * @return Difference matrix
         * @throw MismatchedShapes if dimensions differ
         */
        Matrix<T> operator-(const Matrix<T>& B) const;
        
        /**
         * @brief Element-wise multiplication of two matrices.
         * @param B Second operand
         * @return Element-wise product
         * @throw MismatchedShapes if dimensions differ
         */
        Matrix<T> operator*(const Matrix<T>& B) const;
        
        /**
         * @brief Element-wise division of two matrices.
         * @param B Second operand
         * @return Element-wise quotient
         * @throw MismatchedShapes if dimensions differ
         * @throw DivisionByZero if any element of B is zero
         */
        Matrix<T> operator/(const Matrix<T>& B) const;

        // ========== OPERATORS: ASSIGNMENT ==========
        
        /**
         * @brief Assignment operator.
         * @param B Matrix to assign
         * @return Reference to this matrix
         */
        Matrix<T>& operator=(const Matrix<T>& B);
        Matrix<T>& operator=(Matrix<T>&& B) noexcept;
        
        /**
         * @brief In-place element-wise addition.
         * @param B Matrix to add
         * @return Reference to this matrix
         */
        Matrix<T>& operator+=(const Matrix<T>& B);
        
        /**
         * @brief In-place element-wise subtraction.
         * @param B Matrix to subtract
         * @return Reference to this matrix
         */
        Matrix<T>& operator-=(const Matrix<T>& B);
        
        /**
         * @brief In-place element-wise multiplication.
         * @param B Matrix to multiply
         * @return Reference to this matrix
         */
        Matrix<T>& operator*=(const Matrix<T>& B);
        
        /**
         * @brief In-place element-wise division.
         * @param B Matrix to divide by
         * @return Reference to this matrix
         */
        Matrix<T>& operator/=(const Matrix<T>& B);

        // ========== OPERATORS: SCALAR ASSIGNMENT ==========
        
        /**
         * @brief Assignment from scalar (fills all elements).
         * @param x Scalar value
         * @return Reference to this matrix
         */
        Matrix<T>& operator=(T x);
        
        /**
         * @brief In-place scalar addition.
         * @param x Scalar to add
         * @return Reference to this matrix
         */
        Matrix<T>& operator+=(T x);
        
        /**
         * @brief In-place scalar subtraction.
         * @param x Scalar to subtract
         * @return Reference to this matrix
         */
        Matrix<T>& operator-=(T x);
        
        /**
         * @brief In-place scalar multiplication.
         * @param x Scalar to multiply
         * @return Reference to this matrix
         */
        Matrix<T>& operator*=(T x);
        
        /**
         * @brief In-place scalar division.
         * @param x Scalar to divide by
         * @return Reference to this matrix
         */
        Matrix<T>& operator/=(T x);

        // ========== OPERATORS: COMPARISON ========== 
        
        /**
         * @brief Element-wise greater than comparison.
         * @param x Scalar to compare
         * @return Binary matrix (1 where true, 0 where false)
         */
        Matrix<T> operator>(T x) const;
        
        /**
         * @brief Element-wise less than comparison.
         * @param x Scalar to compare
         * @return Binary matrix (1 where true, 0 where false)
         */
        Matrix<T> operator<(T x) const;
        
        /**
         * @brief Element-wise equality comparison.
         * @param x Scalar to compare
         * @return Binary matrix (1 where equal, 0 where not)
         */
        Matrix<T> operator==(T x) const;

        Matrix<int> operator==(const Matrix<T>& B)const;
        
        /**
         * @brief Element-wise inequality comparison.
         * @param x Scalar to compare
         * @return Binary matrix (1 where not equal, 0 where equal)
         */
        Matrix<T> operator!=(T x) const;

        // ========== OPERATORS: CONVERSION & INDEXING ==========
        
        /**
         * @brief Converts matrix to boolean.
         * @return true if matrix has elements, false if empty
         */
        explicit operator bool() const;

        /**
         * @brief Gets const pointer to first element of row (read-only reference).
         * Allows reading row elements without copying the entire row.
         * @param i Row index
         * @return Const pointer to first element of row i
         */
        const T* operator()(size_t i) const;

        /**
         * @brief Gets element at 2D position (const).
         * @param i Row index
         * @param j Column index
         * @return Element value
         */
        T operator()(size_t i, size_t j) const;
                
        /**
         * @brief Gets mutable reference to element at 2D position.
         * @param i Row index
         * @param j Column index
         * @return Reference to element
         */
        T& operator()(size_t i, size_t j);

        /**
         * @brief Gets element at 1D index (const).
         * @param idx Linear index
         * @return Element value
         */
        T operator[](size_t idx) const;
        
        /**
         * @brief Gets mutable reference to element at 1D index.
         * @param idx Linear index
         * @return Reference to element
         */
        T& operator[](size_t idx);

        /**
         * @brief Converts matrix to string representation.
         * @return String with all elements and shape info
         */
        explicit operator std::string() const;
    };

}

#include "Matrix.tpp"


#endif // LINALG_CST_LIB_MATRIX_H