//
// Created by thiag on 22/07/2024.
//

#ifndef LINALG_CST_LIB_VECTOR_H
#define LINALG_CST_LIB_VECTOR_H

#include "Matrix.h"
#include "Shape.h"

namespace linalg {
    /**
     * @class Vector
     * @brief Specialization of Matrix representing a column vector.
     * 
     * A Vector is a Matrix with a single column (Nx1 shape). It inherits all
     * matrix operations but is semantically a vector. Useful for representing
     * one-dimensional data while maintaining compatibility with matrix operations.
     * 
     * @tparam T Numeric type (float, double, etc.)
     * 
     * @see Matrix
     */
    template <typename T>
    class Vector : public Matrix<T> {
    private:
        using Matrix<T>::setShape;
        using Matrix<T>::resize;
    public:
        using Matrix<T>::operator=;

        /**
         * @brief Default constructor. Creates empty vector.
         */
        Vector();
        
        /**
         * @brief Constructs a vector .
         * Creates a column vector (Nx1). Initialize all values to zero.
         * 
         * @param N Number of elements in the vector
         */
        Vector(size_t N);
        
        /**
         * @brief Constructs vector from values.
         * Creates a column vector (Nx1) from the provided values.
         * 
         * @param values Vector of elements
         */
        explicit Vector(std::vector<T> values);
        
        /**
         * @brief Constructs a vector from initializer list.
         * @param values Initializer list
         */
        Vector(std::initializer_list<T> values);
        
        /**
         * @brief Constructs a vector from a Shape.
         * @param shape Dimensions (must be Nx1)
         */
        Vector(const Shape& shape);


        Vector(Matrix<T>&& matrix);


        // ========== METHODS ============
        /**
         * @brief set the size of the vector to new total number of elements.
         * @param N new number of elements
         */
        void setSize(size_t N);
        
        
        // ========== OPERATORS: ASSIGNMENT ==========
        /**
         * @brief Assignment operator.
         * @param B Value to assign to all positions in vector
         * @return Reference to this vector
         */
        Vector<T>& operator=(T x);
        
        /**
         * @brief In-place element-wise addition.
         * @param B Matrix to add
         * @return Reference to this matrix
         */
        Vector<T>& operator+=(const Vector<T>& B);
        
        /**
         * @brief In-place element-wise subtraction.
         * @param B Vector to subtract
         * @return Reference to this matrix
         */
        Vector<T>& operator-=(const Vector<T>& B);
        
        /**
         * @brief In-place element-wise multiplication.
         * @param B Vector to multiply
         * @return Reference to this matrix
         */
        Vector<T>& operator*=(const Vector<T>& B);
        
        /**
         * @brief In-place element-wise division.
         * @param B Vector to divide by
         * @return Reference to this matrix
         */
        Vector<T>& operator/=(const Vector<T>& B);


        // ========== OPERATORS: SCALAR ==========
        /**
         * @brief Element-wise addition with scalar.
         * @param x Scalar to add
         * @return New vector with x added to each element
         */
        Vector<T> operator+(T x) const;
        
        /**
         * @brief Element-wise subtraction with scalar.
         * @param x Scalar to subtract
         * @return New vector with x subtracted from each element
         */
        Vector<T> operator-(T x) const;
        
        /**
         * @brief Element-wise multiplication with scalar.
         * @param x Scalar to multiply
         * @return New vector with each element multiplied by x
         */
        Vector<T> operator*(T x) const;
        
        /**
         * @brief Element-wise division with scalar.
         * @param x Scalar to divide by
         * @return New vector with each element divided by x
         * @throw DivisionByZero if x is zero
         */
        Vector<T> operator/(T x) const;


        // ========== OPERATORS: VECTOR-VECTOR ==========
        Vector<T> operator+(const Vector<T>& B) const;
        Vector<T> operator-(const Vector<T>& B) const;
        Vector<T> operator*(const Vector<T>& B) const;
        Vector<T> operator/(const Vector<T>& B) const;
    };
}

#include "Vector.tpp"


#endif // LINALG_CST_LIB_VECTOR_H
