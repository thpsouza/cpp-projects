//
// Created by thiag on 22/07/2024.
//

#ifndef LINALG_CST_LIB_MATRIXERRORS_H
#define LINALG_CST_LIB_MATRIXERRORS_H


#include <string>
#include <format>
#include "Shape.h"

namespace linalg {

    /**
     * @struct MatrixError
     * @brief Base exception class for matrix operation errors.
     * 
     * Inherits from std::runtime_error. All matrix-specific exceptions
     * should derive from this class.
     */
    struct MatrixError: public std::runtime_error {
        /**
         * @brief Constructs a MatrixError with a message.
         * @param msg Error message describing what went wrong
         */
        explicit MatrixError(std::string const &msg) : std::runtime_error(msg) {};
    };

    /**
     * @struct ValueError
     * @brief Exception for invalid value errors.
     * 
     * Thrown when an operation encounters an invalid value (e.g., division by zero).
     */
    struct ValueError : public std::runtime_error {
        /**
         * @brief Constructs a ValueError with a message.
         * @param msg Error message describing the invalid value
         */
        explicit ValueError(std::string const &msg) : std::runtime_error(msg) {};
    };

    /**
     * @struct MismatchedShapes
     * @brief Exception thrown when operand shapes don't match.
     * 
     * Raised during element-wise operations requiring compatible dimensions.
     */
    struct MismatchedShapes : public MatrixError {
        /**
         * @brief Constructs error message from two incompatible shapes.
         * @param shape1 First incompatible shape
         * @param shape2 Second incompatible shape
         */
        MismatchedShapes(Shape shape1, Shape shape2):
            MatrixError(std::format("Mismatched shapes: {} and {}",
                                    std::string(shape1), std::string(shape2))) {}
    };

    /**
     * @struct MismatchedNumberOfElements
     * @brief Exception when element counts don't match.
     * 
     * Raised when trying to assign or copy between matrices with different total elements.
     */
    struct MismatchedNumberOfElements: public MatrixError {
        /**
         * @brief Constructs error from two element counts.
         * @param N1 First element count
         * @param N2 Second element count
         */
        MismatchedNumberOfElements(size_t N1, size_t N2):
            MatrixError(std::format("Number of elements are not the same: {} and {}",
                                    N1, N2)) {}
    };

    /**
     * @struct IndexError
     * @brief Exception for out-of-bounds array access.
     * 
     * Thrown when accessing matrix elements with invalid indices.
     * Supports both 2D (i, j) and 1D (i) indexing error reporting.
     */
    struct IndexError: public MatrixError {
        /**
         * @brief Constructs error for 2D index access.
         * @param i Row index
         * @param j Column index
         * @param shape Matrix shape for context
         */
        IndexError(size_t i, size_t j, Shape shape):
            MatrixError(std::format("Indexes ({},{}) out of matrix range: {}x{}",
                                    i, j, shape.rows, shape.cols)) {}
        /**
         * @brief Constructs error for 1D index access.
         * @param i Linear index
         * @param shape Matrix shape for context
         */
        IndexError(size_t i, Shape shape):
                MatrixError(std::format("Indexes {} out of matrix range: {}",
                                        i, shape.N)) {}
    };

    /**
     * @struct ResizeError
     * @brief Exception when reshape operation is impossible.
     * 
     * Thrown when trying to reshape a matrix to incompatible dimensions
     * (total elements must remain constant).
     */
    struct ResizeError: public MatrixError {
        /**
         * @brief Constructs error from reshape attempt.
         * @param rows Target number of rows
         * @param cols Target number of columns
         * @param shape Current matrix shape
         */
        explicit ResizeError(size_t rows, size_t cols, Shape shape):
                MatrixError(std::format("Cant reshape {}x{} Matrix to {}x{}",
                                        shape.rows, shape.cols, rows, cols)) {}
    };

    /**
     * @struct DivisionByZero
     * @brief Exception for division by zero.
     * 
     * Thrown during element-wise division operations when a divisor is zero.
     */
    struct DivisionByZero : public ValueError {
        /**
         * @brief Default constructor with standard message.
         */
        DivisionByZero() : ValueError("Division by zero.") {}
    };
    
}



#endif // LINALG_CST_LIB_MATRIXERRORS_H
