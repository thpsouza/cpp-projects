#include <CustomNeuralNetwork/DenseLayer.h>
#include <CustomNeuralNetwork/ActivationFunctions/ActivationFunctions.h>
#include <CustomNeuralNetwork/InitializationFunctions/InitializationFunctions.h>
#include <CustomNeuralNetwork/Optimizers/Optimizers.h>
#include <iomanip>


// Constructors
DenseLayer::DenseLayer(int input_dim, int output_dim, int layer_id) :
    layer_id(layer_id),
    input_dim(input_dim), 
    output_dim(output_dim),
    w(output_dim, input_dim),
    b(output_dim)
{
    w.setName(std::format("DenseLayer{}_weights", this->layer_id));
    b.setName(std::format("DenseLayer{}_biases", this->layer_id));
    y.setName(std::format("DenseLayer{}_output", this->layer_id));
}
    
DenseLayer::DenseLayer(int input_dim, int output_dim, std::unique_ptr<BaseActivationFunction> activation, int layer_id) : 
    layer_id(layer_id),
    input_dim(input_dim), 
    output_dim(output_dim),
    activation(std::move(activation)),
    w(output_dim, input_dim),
    b(output_dim)
{
    w.setName(std::format("DenseLayer{}_weights", this->layer_id));
    b.setName(std::format("DenseLayer{}_biases", this->layer_id));
    y.setName(std::format("DenseLayer{}_output", this->layer_id));
    // z.setName(std::format("DenseLayer{}_cache", this->layer_id));
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
const std::unique_ptr<BaseActivationFunction>& DenseLayer::getActivationFunction() const {
    return activation;
}
int DenseLayer::getInputDim() const { 
    return input_dim; 
}
int DenseLayer::getOutputDim() const { 
    return output_dim; 
}
const Vector &DenseLayer::getInput() const {
    return x;
}
const Matrix &DenseLayer::getWeights() const {
    return w;
}
const Vector &DenseLayer::getBiases() const {
    return b;
}
const Vector &DenseLayer::getCache() const {
    return z;
}
const Vector &DenseLayer::getOutput() const {
    return y;
}
const Vector &DenseLayer::getDelta() const {
    return delta;
}
Vector &DenseLayer::getInput() {
    return x;
}
Matrix &DenseLayer::getWeights() {
    return w;
}
Vector &DenseLayer::getBiases() {
    return b;
}
Vector &DenseLayer::getCache() {
    return z;
}
Vector &DenseLayer::getOutput() {
    return y;
}
Vector &DenseLayer::getDelta() {
    return delta;
}

// Methods
void DenseLayer::preAllocate() {
    x.setSize(input_dim);
    z.setSize(output_dim);
    y.setSize(output_dim);
    delta.setSize(output_dim);
}

void DenseLayer::initialize(BaseInitializationFunction* initializer) {
    initializer->initialize(w, b);
}

Vector DenseLayer::forward(const Vector& x) {
    this->x = x;
    z = w.dotAdd(x, b);
    y = activation->call(z);
    return y;
}

Vector DenseLayer::backward(const Vector& last_grad) {
    delta = last_grad * activation->grad(z);
    return w.transposedDot(delta);
}

void DenseLayer::print() const {
    std::cout << std::format(" - - - - DENSE LAYER {} ({} -> {}): - - - -\n", layer_id, input_dim, output_dim);
    w.print(); 
    b.print();
}

void DenseLayer::save(std::ostream &output) {
    // Layer Summary
    output << std::format("LAYER {} DENSE {} {} {}\n", 
        layer_id, input_dim, output_dim, activation->getName());
    // Weights
    size_t rows = w.getShape().rows;
    size_t cols = w.getShape().cols;
    output << std::format("WEIGHTS {} {}\n", rows, cols);
    output << std::setprecision(std::numeric_limits<float>::max_digits10);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            output << w.getElement(i,j) << (j == cols - 1 ? "" : " ");
        }
        output << "\n";
    }
    // Biases
    size_t size = b.getSize();
    output << std::format("BIASES {}\n", size);
    output << std::setprecision(std::numeric_limits<float>::max_digits10);
    for (size_t i = 0; i < size; i++) {
        output << b[i] << (i == size - 1 ? "" : " ");
    }
    output << "\n";
}

inline void DenseLayer::auxiliaryActivationGenerator(std::string& buffer) {
    // Handle activation (MAY BE MOVED TO ITS OWN GENERATOR CLASS)
    if (buffer == "LINEAR") setActivationFunction(LINEAR);
    else if (buffer == "SIGMOID") setActivationFunction(SIGMOID);
    else if (buffer == "TANH") setActivationFunction(TANH);
    else if (buffer == "RELU") setActivationFunction(RELU);
}

void DenseLayer::load(std::istream &input) {    
    // Buffer to read the stream
    std::string buffer;
    float value;
    
    // Summary: LAYER {ID} {TYPE} {INPUT_DIM} {OUTPUT_DIM} {ACTIVATION}
    input >> buffer >> layer_id >> buffer >> input_dim >> output_dim >> buffer;
    auxiliaryActivationGenerator(buffer);

    // Weights: WEIGHTS {ROWS} {COLS}
    size_t rows, cols;
    input >> buffer >> rows >> cols;
    w.resize(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            input >> value;
            w.setElement(value, i, j);
        }
    }
    // Biases: BIASES {SIZE}
    size_t size;
    input >> buffer >> size;
    b.setSize(size);
    for (size_t i = 0; i < size; i++) {
        input >> value;
        b.setElement(value, i);   
    }

    preAllocate();
}