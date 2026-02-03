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
        this->class_name = "Vector";
    }    
    
    template <typename T>
    Vector<T>::Vector(size_t N) : Matrix<T>(N, 1) {
        this->class_name = "Vector";
    }

    template <typename T>
    Vector<T>::Vector(std::vector<T> values) : Matrix<T>(std::move(values)) {
        this->setShape(values.size(), 1);
        this->class_name = "Vector";
    }

    template <typename T>
    Vector<T>::Vector(std::initializer_list<T> values) : Matrix<T>(values) {
        this->setShape(values.size(), 1);
        this->class_name = "Vector";
    }

    template <typename T>
    Vector<T>::Vector(const Shape& shape) : Matrix<T>(shape) {
        if (shape.cols != 1 && shape.N != 0) {
            throw MismatchedShapes(shape, Shape(shape.rows, 1));
        }
        this->class_name = "Vector";
    }

    template <typename T> 
    Vector<T>::Vector(Matrix<T> &&matrix) : Matrix<T>(std::move(matrix)) { 
        if (this->shape.cols != 1 && this->shape.N != 0) {
            throw MismatchedShapes(this->shape, Shape(this->shape.rows, 1));
        }
        this->class_name = "Vector";
    }

    // Methods
    template <typename T> 
    void Vector<T>::setElements(std::vector<T> values) {
        setSize(values.size());
        this->values = std::move(values);
    }
    
    template <typename T>
    void Vector<T>::setElements(std::initializer_list<T> values) {
        setSize(values.size());
        this->values = std::move(values);
    }

    template <typename T>
    void Vector<T>::setSize(size_t N) {
        this->resize(N, 1);
        this->setShape(N, 1);
    }

    template <typename T> 
    size_t Vector<T>::getSize() const {
        return this->getShape().N;
    }

    // ========== OPERATORS: ASSIGNMENT ==========
    template <typename T>
    Vector<T>& Vector<T>::operator=(T x) {
        return Vector<T>(Matrix<T>::operator=(x));
    }
    template <typename T>
    Vector<T>& Vector<T>::operator=(std::initializer_list<T> x) {
        this->Matrix<T>::operator=(x);
        this->setSize(x.size());
        return *this;
    }
    // template <typename T>
    // Vector<T>& Vector<T>::operator=(const Vector<T>& B) {
    //     return Vector<T>(Matrix<T>::operator=(B));
    // }
    // template <typename T>
    // Vector<T>& Vector<T>::operator=(Vector<T> &&B) noexcept {
    //     return Vector<T>(Matrix<T>::operator=(B));
    // }
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
    

    // ========== OPERATORS: VECTOR-VECTOR ==========
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