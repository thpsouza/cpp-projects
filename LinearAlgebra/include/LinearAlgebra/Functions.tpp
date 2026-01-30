//
// Created by thiag on 29/07/2024.
//

#include "Functions.h"
#include "Matrix.h"
#include <cmath>
#include <algorithm>
//#include <functional>
//std::vector<double> transform(std::vector<double> x, std::function<double(double)> f) {
//    std::vector<double> ret(x.size());
//    std::transform(x.begin(), x.end(), ret.begin(), std::move(f));
//    return ret;
//}

namespace linalg {

    template <typename T>
    Matrix<T> exp(const Matrix<T>& m) {
        std::vector<T> values = m.getElements();
        Matrix<T> temp(m.getShape());
        std::transform(values.begin(), values.end(), temp.getElements().begin(),
                    [](T x){ return std::exp(x);});
        return temp;
    }

    template <typename T>
    Matrix<T> pow(const Matrix<T>& m, T n) {
        std::vector<T> values = m.getElements();
        Matrix<T> temp(m.getShape());
        std::transform(values.begin(), values.end(), temp.getElements().begin(),
                    [&](T x){ return std::pow(x, n);});
        return temp;
    }
    
}