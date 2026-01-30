//
// Created by thiag on 22/07/2024.
//

#include <LinearAlgebra/Shape.h>

namespace linalg {
    /// Constructors
    Shape::Shape() : rows(0), cols(0), N(0) {
    }

    Shape::Shape(size_t rows, size_t cols) : rows(rows), cols(cols), N(rows*cols)
    {
    }

    Shape::Shape(size_t rows, size_t cols, size_t N) : rows(rows), cols(cols), N(N)
    {
    }

    /// Operators overload
    Shape::operator std::string() const {
        return "(" + std::to_string(rows) + "," + std::to_string(cols) + ")";
    }


    bool Shape::operator==(const Shape &other) const {
        return (this->rows == other.rows) && (this->cols == other.cols);
    }

    bool Shape::operator!=(const Shape &other) const {
        return !(*this == other);
    }
}
