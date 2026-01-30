#ifndef NN_MODEL_BASE_ACTIVATION_FUN_H
#define NN_MODEL_BASE_ACTIVATION_FUN_H

class BaseActivationFunction {
public:
    BaseActivationFunction();
    virtual ~BaseActivationFunction();

    virtual float call(float x) const;
    virtual float grad(float x) const;

    float operator()(float x) const;
};



#endif //NN_MODEL_BASE_ACTIVATION_FUN_H