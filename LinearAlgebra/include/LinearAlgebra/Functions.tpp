//
// Created by thiag on 29/07/2024.
//

#include "Functions.h"
#include "Matrix.h"
#include "Vector.h"
#include "Shape.h"
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
        // Matrix<T> result(m.getShape());
        // std::vector<T>& temp = result.getElements();
        // const std::vector<T>& values = m.getElements();
        // for (size_t i = 0; i < values.size(); i++) {
        //     temp[i] = std::exp(values[i]);
        // }
        // return result;
        return transform(m, [](T x) { return std::exp(x); });
    }

    template <typename T>
    Matrix<T> pow(const Matrix<T>& m, T n) {
        // Matrix<T> result(m.getShape());
        // std::vector<T>& temp = result.getElements();
        // const std::vector<T>& values = m.getElements();
        // for (size_t i = 0; i < values.size(); i++) {
        //     temp[i] = std::pow(values[i], n);
        // }
        // return result;
        return transform(m, [n](T x) { return std::pow(x, n); });

    }
    
    template <typename T>
    Matrix<T> pow(const Matrix<T>& m, int n) {
        return transform(m, [n](T x) { return std::pow(x, n); });
    }


    template <typename T>
    Vector<T> exp(const Vector<T>& v) {
        return transform(v, [](T x) { return std::exp(x); });
    }

    template <typename T>
    Vector<T> pow(const Vector<T>& v, T n) {
        return transform(v, [n](T x) { return std::pow(x, n); });
    }

    template <typename T>
    Vector<T> pow(const Vector<T>& v, int n) {
        return transform(v, [n](T x) { return std::pow(x, n); });
    }


    // Unary transform
    template <typename T, typename Func>
    Matrix<T> transform(const Matrix<T>& m, Func func) {
        Matrix<T> result(m.getShape());
        std::vector<T>& temp = result.getElements();
        const std::vector<T>& values = m.getElements();
        for (size_t i = 0; i < values.size(); i++) {
            temp[i] = func(values[i]);
        }
        return result;
    }

    template <typename T, typename Func>
    Vector<T> transform(const Vector<T>& v, Func func) {
        Vector<T> result(v.getSize());
        std::vector<T>& temp = result.getElements();
        const std::vector<T>& values = v.getElements();
        for (size_t i = 0; i < values.size(); i++) {
            temp[i] = func(values[i]);
        }
        return result;
    }

    // Binary transform
    template <typename T, typename Func>
    Matrix<T> transform(const Matrix<T>& m1, const Matrix<T>& m2, Func func) {
        Shape S1 = m1.getShape();
        Shape S2 = m2.getShape();
        if (S1 != S2) throw linalg::MismatchedShapes(S1, S2);

        Matrix<T> result(S1);
        std::vector<T>& temp = result.getElements();
        const std::vector<T>& values1 = m1.getElements();
        const std::vector<T>& values2 = m2.getElements();
        for (size_t i = 0; i < S1.N; i++) {
            temp[i] = func(values1[i], values2[i]);
        }
        return result;
    }

    template <typename T, typename Func>
    Vector<T> transform(const Vector<T>& v1, const Vector<T>& v2, Func func) {
        size_t N1 = v1.getSize();
        size_t N2 = v2.getSize();
        if (N1 != N2) throw linalg::MismatchedNumberOfElements(N1,N2);
        
        Vector<T> result(N1);
        std::vector<T>& temp = result.getElements();
        const std::vector<T>& values1 = v1.getElements();
        const std::vector<T>& values2 = v2.getElements();
        for (size_t i = 0; i < N1; i++) {
            temp[i] = func(values1[i], values2[i]);
        }
        return result;
    }

	// Ternary and above (ATTENTION: DOES NOT VERIFY SHAPE/SIZE)
    template <typename T, typename Func, typename... Matrices>
    Matrix<T> transform(Func func, const Matrix<T>& first, const Matrices& ...rest) {
		Shape S = first.getShape();
		if (!((rest.getShape() == S) && ...)) {
        	throw std::invalid_argument("Mismatched Shapes of matrices passed.");
    	}
		
		Matrix<T> result(S);
		const T* first_ptr = &first[0];
		const T* rest_ptr[] = { (&rest[0])... };
		T* temp_ptr = &result.getElements();
		for (size_t i = 0; i < S.N; ++i) {
			temp_ptr[i] = func(first[i], rest[i]...);
		}
		return result;
    }
    
	template <typename T, typename Func, typename... Vectors>
    Vector<T> transform(Func func, const Vector<T>& first, const Vectors& ...rest) {
		size_t N = first.getSize();
		if (!((rest.getSize() == N) && ...)) {
        	throw std::invalid_argument("Mismatched number of elements in vectors passed.");
    	}
		
		Vector<T> result(N);
		const T* first_ptr = &first[0];
		const T* rest_ptr[] = { (&rest[0])... };
		T* temp_ptr = &result.getElements();
		for (size_t i = 0; i < N; ++i) {
			temp_ptr[i] = func(first[i], rest[i]...);
		}
		return result;
    }

} // namespace linalg