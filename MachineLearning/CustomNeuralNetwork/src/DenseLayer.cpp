#include <CustomNeuralNetwork/DenseLayer.h>
#include <CustomNeuralNetwork/ActivationFunctions/ActivationFunctions.h>
#include <CustomNeuralNetwork/InitializationFunctions/InitializationFunctions.h>
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

const std::unique_ptr<BaseActivationFunction>& DenseLayer::getActivationFunction() const {
    return activation;
}
int DenseLayer::getInputDim() const { 
    return input_dim; 
}
int DenseLayer::getOutputDim() const { 
    return output_dim; 
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
void DenseLayer::initialize(BaseInitializationFunction* initializer) {
    initializer->initialize(w, b);
}

Vector DenseLayer::forward(const Vector& x) {
    last_input = x;
    z_cache = w.dotAdd(x, b);
    y = activation->call(z_cache);
    return y;
}

void DenseLayer::backward(float y_target) {
    
}

void DenseLayer::print() const {
    // std::cout << std::format("DENSELAYER{}:", layer_id) << "\n"; 
    // w.print();
    // b.print();
    std::cout << std::format(" - - - - DENSE LAYER {} ({} -> {}): - - - -\n", layer_id, input_dim, output_dim);
    w.print(); 
    b.print();
}

void DenseLayer::save(std::ostream &output) {
    // Layer Summary
    output << std::format("LAYER {} DENSE {} {} {}\n", 
        layer_id, output_dim, input_dim, activation->getName());
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
}