#include <CustomNeuralNetwork/LossFunctions/BaseLossFunction.h>


float BaseLossFunction::call(float y, float y_predict) const
{
    return 0.0f;
}

float BaseLossFunction::grad(float y, float y_predict) const
{
    return 0.0f;
}

float BaseLossFunction::operator()(float y, float y_predict) const
{
    return call(y, y_predict);
}