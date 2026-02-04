#ifndef NN_MODEL_BASE_LOSS_FUNCTION_H
#define NN_MODEL_BASE_LOSS_FUNCTION_H

// Std lib includes
#include <string>

// Forward declarations
#include <LinearAlgebra/LinAlgFwds.h>


// Implementation
class BaseLossFunction {
public:
    BaseLossFunction() = default;
    virtual ~BaseLossFunction() = default;

    virtual std::string getName() const;

    virtual float call(float y_predict, float y_target) const;
    virtual float grad(float y_predict, float y_target) const;
    float operator()(float y_predict, float y_target) const;
       
    virtual Vector call(const Vector& y_predict, const Vector& y_target) const;
    virtual Vector grad(const Vector& y_predict, const Vector& y_target) const;
    Vector operator()(const Vector& y_predict, const Vector& y_target) const;
};

#endif //NN_MODEL_BASE_LOSS_FUNCTION_H