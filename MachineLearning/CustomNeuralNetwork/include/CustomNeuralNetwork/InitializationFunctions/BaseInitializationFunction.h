#ifndef NN_MODEL_BASE_INITIALIZATION_FUN_H
#define NN_MODEL_BASE_INITIALIZATION_FUN_H

// Std lib includes:
#include <string>

// Forward declarations
#include <LinearAlgebra/LinAlgFwds.h>


// Implementation
class BaseInitializationFunction {
public:
    BaseInitializationFunction() = default;
    virtual ~BaseInitializationFunction() = default;
    virtual std::string getName() const = 0;
    virtual void initialize(Matrix& weights, Vector& biases) const = 0;
    void operator()(Matrix& weights, Vector& biases) const;
};



#endif //NN_MODEL_BASE_INITIALIZATION_FUN_H