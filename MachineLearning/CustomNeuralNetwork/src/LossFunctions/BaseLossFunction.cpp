#include <CustomNeuralNetwork/LossFunctions/BaseLossFunction.h>
#include <LinearAlgebra/LinAlg.h>


float BaseLossFunction::call(float y_predict, float y_target) const
{
    return 0.0f;
}

float BaseLossFunction::grad(float y_predict, float y_target) const
{
    return 0.0f;
}

float BaseLossFunction::operator()(float y_predict, float y_target) const
{
    return call(y_predict, y_target);
}

Vector BaseLossFunction::call(const Vector& y_predict, const Vector& y_target) const {
  return Vector();
}

Vector BaseLossFunction::grad(const Vector& y_predict, const Vector& y_target) const {
  return Vector();
}

Vector BaseLossFunction::operator()(const Vector& y_predict, const Vector& y_target) const {
  return call(y_predict, y_target);
}
