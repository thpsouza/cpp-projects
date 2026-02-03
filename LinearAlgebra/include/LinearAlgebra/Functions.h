//
// Created by thiag on 29/07/2024.
//

#ifndef LINALG_CST_LIB_FUNCTIONS_H
#define LINALG_CST_LIB_FUNCTIONS_H

#include "Matrix.h"
#include "Vector.h"
#include <cmath>
#include <algorithm>

namespace linalg {
    /**
     * @defgroup Functions Element-wise Mathematical Functions
     * @brief Mathematical functions applied element-wise to matrix elements.
     * @{
     */
   
    /**
     * @brief Computes the exponential (e^x) for each element of the matrix.
     * 
     * Applies the natural exponential function to every element in the matrix.
     * 
     * @tparam T Numeric type (float, double, etc.)
     * @param m Input matrix
     * @return New matrix with exponential of each element
     * 
     * @see pow()
     */
    template <typename T>
    Matrix<T> exp(const Matrix<T>& m);

    /**
     * @brief Raises each matrix element to a power.
     * 
     * Computes m[i]^n for each element in the matrix.
     * 
     * @tparam T Numeric type (float, double, etc.)
     * @param m Input matrix
     * @param n Exponent to raise each element to
     * @return New matrix with each element raised to power n
     * 
     * @see exp()
     */
    template <typename T>
    Matrix<T> pow(const Matrix<T>& m, T n);
    template <typename T>
    Matrix<T> pow(const Matrix<T>& m, int n);

        /**
     * @brief Computes the exponential (e^x) for each element of the vector.
     * 
     * Applies the natural exponential function to every element in the vector.
     * 
     * @tparam T Numeric type (float, double, etc.)
     * @param m Input vector
     * @return New vector with exponential of each element
     * 
     * @see pow()
     */
    template <typename T>
    Vector<T> exp(const Vector<T>& m);

    /**
     * @brief Raises each vector element to a power.
     * 
     * Computes m[i]^n for each element in the vector.
     * 
     * @tparam T Numeric type (float, double, etc.)
     * @param m Input vector
     * @param n Exponent to raise each element to
     * @return New vector with each element raised to power n
     * 
     * @see exp()
     */
    template <typename T>
    Vector<T> pow(const Vector<T>& m, T n);
    template <typename T>
    Vector<T> pow(const Vector<T>& m, int n);


    template <typename T, typename Func>
    Matrix<T> transform(const Matrix<T> &m, Func func);
    template <typename T, typename Func>
    Vector<T> transform(const Vector<T> &v, Func func);

    /** @} */ // End of Functions group
}

#include "Functions.tpp"

#endif // LINALG_CST_LIB_FUNCTIONS_H
