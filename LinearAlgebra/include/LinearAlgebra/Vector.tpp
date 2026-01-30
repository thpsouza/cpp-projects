//
// Created by thiag on 22/07/2024.
//

#include <utility>
#include "Vector.h"

namespace linalg {

    // Constructors
    template <typename T>
    Vector<T>::Vector() : Matrix<T>() {
        // this->shape.cols = 1;
    }    
    
    template <typename T>
    Vector<T>::Vector(size_t N) : Matrix<T>(N, 1) {
    }

    template <typename T>
    Vector<T>::Vector(std::vector<T> values) : Matrix<T>(std::move(values)) {
        this->setShape(values.size(), 1);
    }

    template <typename T>
    Vector<T>::Vector(std::initializer_list<T> values) : Matrix<T>(values) {
        this->setShape(values.size(), 1);
    }

    // Methods
    template <typename T>
    void Vector<T>::setSize(size_t N) {
        this->resize(N, 1);
        this->setShape(N, 1);
    }

    // Operators
    template <typename T>
    Vector<T> &Vector<T>::operator=(T x) {
        Matrix<T>::operator=(x);
        return *this;
    }
}