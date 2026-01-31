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

    template <typename T> 
    Vector<T>::Vector(Matrix<T> &&matrix) : Matrix<T>(std::move(matrix)) { 
    }

    // Methods
    template <typename T>
    void Vector<T>::setSize(size_t N) {
        this->resize(N, 1);
        this->setShape(N, 1);
    }

    // ========== OPERATORS: ASSIGNMENT ==========
    template <typename T>
    Vector<T>& Vector<T>::operator=(T x) {
        return Vector<T>(Matrix<T>::operator=(x));
    }
    template <typename T>
    Vector<T> &Vector<T>::operator+=(const Vector<T> &B) {
        return Vector<T>(Matrix<T>::operator+=(B));
    }
    template <typename T>
    Vector<T> &Vector<T>::operator-=(const Vector<T> &B) {
        return Vector<T>(Matrix<T>::operator-=(B));
    }
    template <typename T>
    Vector<T> &Vector<T>::operator*=(const Vector<T> &B) {
        return Vector<T>(Matrix<T>::operator*=(B));
    }
    template <typename T>
    Vector<T> &Vector<T>::operator/=(const Vector<T> &B) {
        return Vector<T>(Matrix<T>::operator/=(B));
    }

    // ========== OPERATORS: SCALAR ==========
    template <typename T>
    Vector<T> Vector<T>::operator+(T x) const {
        return Vector<T>(Matrix<T>::operator+(x));
    }
    template <typename T>
    Vector<T> Vector<T>::operator-(T x) const {
        return Vector<T>(Matrix<T>::operator-(x));
    }
    template <typename T>
    Vector<T> Vector<T>::operator*(T x) const {
        return Vector<T>(Matrix<T>::operator*(x));
    }
    template <typename T>
    Vector<T> Vector<T>::operator/(T x) const {
        return Vector<T>(Matrix<T>::operator/(x));
    }
    

    // ========== OPERATORS: MATRIX-MATRIX ==========
    template <typename T>
    Vector<T> Vector<T>::operator+(const Vector<T>& B) const {
        return Vector<T>(Matrix<T>::operator+(B));
    }
    template <typename T>
    Vector<T> Vector<T>::operator-(const Vector<T>& B) const {
        return Vector<T>(Matrix<T>::operator-(B));
    }
    template <typename T>
    Vector<T> Vector<T>::operator*(const Vector<T>& B) const {
        return Vector<T>(Matrix<T>::operator*(B));
    }
    template <typename T>
    Vector<T> Vector<T>::operator/(const Vector<T>& B) const {
        return Vector<T>(Matrix<T>::operator/(B));
    }

}