#ifndef NN_MODEL_BASE_LOSS_FUNCTION_H
#define NN_MODEL_BASE_LOSS_FUNCTION_H

class BaseLossFunction {
    public:
    BaseLossFunction() = default;
    virtual ~BaseLossFunction() = default;
    virtual float call(float y, float y_predict) const;
    virtual float grad(float y, float y_predict) const;
    float operator()(float y, float y_predict) const;
};

#endif //NN_MODEL_BASE_LOSS_FUNCTION_H