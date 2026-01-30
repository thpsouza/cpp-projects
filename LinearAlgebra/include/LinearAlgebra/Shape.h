//
// Created by thiag on 22/07/2024.
//

#ifndef LINALG_CST_LIB_SHAPE_H
#define LINALG_CST_LIB_SHAPE_H

#include <string>

/**
 * @namespace linalg
 * @brief Linear algebra library with template-based Matrix and Vector operations.
 * 
 * Provides efficient matrix/vector operations supporting both float and double types,
 * including element-wise operations, matrix multiplication, and utility functions.
 */
namespace linalg {
    /**
     * @struct Shape
     * @brief Represents the dimensions of a matrix or vector.
     * 
     * Stores matrix dimensions (rows, cols) and total number of elements (N).
     * This struct is used throughout the library for dimension validation and shape tracking.
     */
    struct Shape {
        size_t rows;
        size_t cols;
        size_t N;    

        // ========== PUBLIC API ==========
        /**
         * @brief Default constructor.
         */
        Shape();
        
        /**
         * @brief Constructs a shape from rows and columns.
         * @param rows Number of rows
         * @param cols Number of columns
         */
        Shape(size_t rows, size_t cols);
        
        /**
         * @brief Constructs a shape with explicit element count.
         * @param rows Number of rows
         * @param cols Number of columns
         * @param N Total number of elements
         */
        Shape(size_t rows, size_t cols, size_t N);
        
        /**
         * @brief Converts shape to string representation.
         * @return String in format "rows x cols"
         */
        explicit operator std::string() const;
        
        /**
         * @brief Equality comparison operator.
         * @param other Shape to compare with
         * @return true if shapes have same dimensions, false otherwise
         */
        bool operator==(const Shape &other) const;
        
        /**
         * @brief Inequality comparison operator.
         * @param other Shape to compare with
         * @return true if shapes differ, false otherwise
         */
        bool operator!=(const Shape &other) const;
    };
}

#endif // LINALG_CST_LIB_SHAPE_H
