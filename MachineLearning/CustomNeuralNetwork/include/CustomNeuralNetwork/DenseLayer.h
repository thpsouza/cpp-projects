#ifndef NN_MODEL_DENSE_LAYER_H
#define NN_MODEL_DENSE_LAYER_H

// Standard lib includes
#include <vector>
#include <memory>
#include <iostream>

// Custom lib includes
#include <LinearAlgebra/LinAlg.h>

// Forward declarations
class BaseActivationFunction;
class BaseInitializationFunction;


// Implementation
class DenseLayer {
private:
    int layer_id;
    int input_dim;
    int output_dim;
    std::unique_ptr<BaseActivationFunction> activation;    
    Vector z_cache;
    Vector last_input;
    Matrix w; 
    Vector b;
    Vector y;
    void auxiliaryActivationGenerator(std::string &buffer);

    
public:
    // Constructor/Destructor
    DenseLayer() = default;
    DenseLayer(int input_dim, int output_dim, int layer_id);
    DenseLayer(int input_dim, int output_dim, std::unique_ptr<BaseActivationFunction> activation, int layer_id);
    
    // Getters/Setters
    void setActivationFunction(std::unique_ptr<BaseActivationFunction> function);
    void setWeights(Matrix&& w);
    void setBiases(Vector&& b);
    void setParamenters(Matrix&& w, Vector&& b);
    const std::unique_ptr<BaseActivationFunction>& getActivationFunction() const;
    int getInputDim() const;
    int getOutputDim() const;
    const Matrix& getWeights() const;
    const Vector& getBiases() const;
    const Vector& getOutput() const;
    Matrix& getWeights();
    Vector& getBiases();
    Vector& getOutput();

    // Methods
    void initialize(BaseInitializationFunction* initializer);
    Vector forward(const Vector& x);
    void backward(float y_target);
    void print() const;
    void save(std::ostream& output);
    void load(std::istream &input);
};


#endif //NN_MODEL_DENSE_LAYER_H
