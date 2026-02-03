#include <CustomNeuralNetwork/DenseLayer.h>
#include <CustomNeuralNetwork/ActivationFunctions/ActivationFunctions.h>
#include <iomanip>


// Constructors
DenseLayer::DenseLayer(int input_dim, int output_dim, int layer_id) :
    input_dim(input_dim), 
    output_dim(output_dim),
    w(output_dim, input_dim),
    b(output_dim),
    z_cache(output_dim),
    layer_id(layer_id)
{
    w.setName(std::format("DenseLayer{}_weights", this->layer_id));
    b.setName(std::format("DenseLayer{}_biases", this->layer_id));
    y.setName(std::format("DenseLayer{}_output", this->layer_id));
}
    
DenseLayer::DenseLayer(int input_dim, int output_dim, std::unique_ptr<BaseActivationFunction> activation, int layer_id) : 
    input_dim(input_dim), 
    output_dim(output_dim),
    activation(std::move(activation)),
    w(output_dim, input_dim),
    b(output_dim),
    z_cache(output_dim),
    layer_id(layer_id)
{
    w.setName(std::format("DenseLayer{}_weights", this->layer_id));
    b.setName(std::format("DenseLayer{}_biases", this->layer_id));
    y.setName(std::format("DenseLayer{}_output", this->layer_id));
    // z_cache.setName(std::format("DenseLayer{}_cache", this->layer_id));
}

// Getters/Setters
void DenseLayer::setActivationFunction(std::unique_ptr<BaseActivationFunction> function) {
    activation = std::move(function);
}
void DenseLayer::setWeights(Matrix&& w) {
    this->w = std::move(w); 
}
void DenseLayer::setBiases(Vector&& b) {
    this->b = std::move(b);
}
void DenseLayer::setParamenters(Matrix&& w, Vector&& b) {
    this->w = std::move(w); 
    this->b = std::move(b);
}
const Matrix &DenseLayer::getWeights() const {
    return w;
}
const Vector &DenseLayer::getBiases() const {
    return b;
}
const Vector &DenseLayer::getOutput() const {
    return y;
}
Matrix &DenseLayer::getWeights() {
    return w;
}
Vector &DenseLayer::getBiases() {
    return b;
}
Vector &DenseLayer::getOutput() {
    return y;
}


// Methods
Vector DenseLayer::forward(const Vector& x) {
    last_input = x;
    z_cache = w.dotAdd(x, b);
    y = activation->call(z_cache);
    return y;
}

void DenseLayer::backward(float y_target) {
    
}

void DenseLayer::print() {
    std::cout << std::format("DenseLayer{}:", layer_id) << "\n"; 
    w.print();
    b.print();
}

void DenseLayer::save(std::ostream &output) {
    output << "LAYER " << layer_id << " DENSE " 
    << output_dim << " " << input_dim << " "
    << activation->getName();
    output << "\nWEIGHTS\n";;
    output << std::setprecision(std::numeric_limits<float>::max_digits10);
    for (size_t i = 0; i < w.getShape().rows; i++) {
        for (size_t j = 0; j < w.getShape().cols; j++) {
            output << w.getElement(i,j) << " ";
        output << "\n";
        }
    }
    output << "\nBIASES\n";
    output << std::setprecision(std::numeric_limits<float>::max_digits10);
    for (size_t i = 0; i < b.getSize(); i++) {
        output << b[i] << " ";
    }
    output << "\n";
}