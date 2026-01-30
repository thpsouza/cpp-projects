//
// Created by thiag on 29/07/2024.
//

#ifndef LINALG_CST_LIB_FUNCTIONS_H
#define LINALG_CST_LIB_FUNCTIONS_H

#include "Matrix.h"
#include <cmath>
#include <algorithm>

namespace linalg {
    /**
     * @defgroup Functions Element-wise Mathematical Functions
     * @brief Mathematical functions applied element-wise to matrix elements.
     * @{
     */
   
    /**
     * @brief Computes the exponential (e^x) for each element.
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
    
    /** @} */ // End of Functions group
}

#include "Functions.tpp"

#endif // LINALG_CST_LIB_FUNCTIONS_H
