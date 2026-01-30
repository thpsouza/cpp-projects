#include <CustomNeuralNetwork/LossFunctions/MeanSquaredErrorLossFunction.h>
#include <cmath>


float MeanSquaredErrorLossFunction::call(float y, float y_predict) const {
    return pow(y - y_predict, 2);
}

float MeanSquaredErrorLossFunction::grad(float y, float y_predict) const {
    return 2.0f * (y_predict - y);
}
