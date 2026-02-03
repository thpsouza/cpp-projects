#ifndef LINALG_FWD_H
#define LINALG_FWD_H

namespace linalg {
    template <typename T> class Matrix;
    template <typename T> class Vector;
    struct Shape;
}

using precision = float; // changeable to double if needed

using Matrix = linalg::Matrix<precision>;
using Vector = linalg::Vector<precision>;
using Shape  = linalg::Shape;

#endif //LINALG_FWD_H