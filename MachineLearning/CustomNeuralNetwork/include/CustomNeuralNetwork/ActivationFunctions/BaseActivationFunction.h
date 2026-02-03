#ifndef NN_MODEL_BASE_ACTIVATION_FUN_H
#define NN_MODEL_BASE_ACTIVATION_FUN_H

// Standard lib includes
#include <vector>
#include <string>

// Forward declarations
class Matrix;

// Implementation
class BaseActivationFunction {
public:
    BaseActivationFunction();
    virtual ~BaseActivationFunction();

    virtual std::string getName() const;

    virtual float call(float x) const;
    virtual float grad(float x) const;
    float operator()(float x) const;
    
    virtual Matrix call(const Matrix& x) const;
    virtual Matrix grad(const Matrix& x) const;
    Matrix operator()(const Matrix& x) const;
};



#endif //NN_MODEL_BASE_ACTIVATION_FUN_H