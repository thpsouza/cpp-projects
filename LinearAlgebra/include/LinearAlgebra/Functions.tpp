//
// Created by thiag on 29/07/2024.
//

#include "Functions.h"
#include "Matrix.h"
#include "Vector.h"
#include <cmath>
//#include <functional>
//std::vector<double> transform(std::vector<double> x, std::function<double(double)> f) {
//    std::vector<double> ret(x.size());
//    std::transform(x.begin(), x.end(), ret.begin(), std::move(f));
//    return ret;
//}

namespace linalg {

    template <typename T>
    Matrix<T> exp(const Matrix<T>& m) {
        Matrix<T> result(m.getShape());
        std::vector<T>& temp = result.getElements();
        const std::vector<T>& values = m.getElements();
        for (size_t i = 0; i < values.size(); i++) {
            temp[i] = std::exp(values[i]);
        }
        // std::transform(values.begin(), values.end(), result.getElements().begin(),
        //             [](T x){ return std::exp(x);});
        return result;
    }

    template <typename T>
    Matrix<T> pow(const Matrix<T>& m, T n) {
        Matrix<T> result(m.getShape());
        std::vector<T>& temp = result.getElements();
        const std::vector<T>& values = m.getElements();
        for (size_t i = 0; i < values.size(); i++) {
            temp[i] = std::pow(values[i], n);
        }
        return result;
    }
    
    template <typename T>
    Matrix<T> pow(const Matrix<T>& m, int n) {
        Matrix<T> result(m.getShape());
        std::vector<T>& temp = result.getElements();
        const std::vector<T>& values = m.getElements();
        for (size_t i = 0; i < values.size(); i++) {
            temp[i] = std::pow(values[i], n);
        }
        return result;
    }


    template <typename T>
    Vector<T> exp(const Vector<T>& v) {
        Vector<T> result(v.getSize());
        std::vector<T>& temp = result.getElements();
        const std::vector<T>& values = v.getElements();
        for (size_t i = 0; i < values.size(); i++) {
            temp[i] = std::exp(values[i]);
        }
        return result;
    }

    template <typename T>
    Vector<T> pow(const Vector<T>& v, T n) {
        Vector<T> result(v.getSize());
        std::vector<T>& temp = result.getElements();
        const std::vector<T>& values = v.getElements();
        for (size_t i = 0; i < values.size(); i++) {
            temp[i] = std::pow(values[i], n);
        }
        return result;
    }

    template <typename T>
    Vector<T> pow(const Vector<T>& v, int n) {
        Vector<T> result(v.getSize());
        std::vector<T>& temp = result.getElements();
        const std::vector<T>& values = v.getElements();
        for (size_t i = 0; i < values.size(); i++) {
            temp[i] = std::pow(values[i], n);
        }
        return result;
    }
    
}