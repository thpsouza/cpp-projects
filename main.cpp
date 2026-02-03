#include <CustomNeuralNetwork/NN.h>
#include <CustomNeuralNetwork/ActivationFunctions/ActivationFunctions.h>
#include <CustomNeuralNetwork/InitializationFunctions/InitializationFunctions.h>
#include <CustomNeuralNetwork/LossFunctions/LossFunctions.h>
#include <CustomNeuralNetwork/Optimizers/Optimizers.h>
#include <utils.h>


void singleNeuronNetwork(std::string model_name, Matrix& x_train, Matrix& y_train) {
    int input_dim = 2;
    int output_dim = 1;
    float learning_rate = 1e-2;
    int epochs = 1e6;

    NN neuron(model_name, input_dim, output_dim);
    neuron.setInitializationFunction(RANDOM);
    neuron.setActivationFunction(SIGMOID);
    neuron.setLossFunction(MSE);
    neuron.setOptimizer(SGD, learning_rate);
    neuron.initialize();

    neuron.print();
    print("\n");
    neuron.fit(x_train, y_train, epochs);
    print("\n");
    neuron.print();
    print("\n");

    float y[4];
    y[0] = neuron.predict({0,0});
    y[1] = neuron.predict({0,1});
    y[2] = neuron.predict({1,0});
    y[3] = neuron.predict({1,1});
    print("Predict:\n");
    print("F(0,0): ", y[0], "\n");
    print("F(0,1): ", y[1], "\n");
    print("F(1,0): ", y[2], "\n");
    print("F(1,1): ", y[3], "\n");
}

void andNetwork() {
    Matrix x_train({
        {0, 0},
        {1, 0},
        {0, 1},
        {1, 1}
    });
    Matrix y_train({
        {0}, 
        {0}, 
        {0}, 
        {1} 
    });
    singleNeuronNetwork("AND_MODEL", x_train, y_train);
}

void nandNetwork() {
    Matrix x_train({
        {0, 0},
        {1, 0},
        {0, 1},
        {1, 1}
    });
    Matrix y_train({
        {1}, 
        {1}, 
        {1}, 
        {0} 
    });
    singleNeuronNetwork("NAND_MODEL", x_train, y_train);
}

void orNetwork() {
    Matrix x_train({
        {0, 0},
        {1, 0},
        {0, 1},
        {1, 1}
    });
    Matrix y_train({
        {0}, 
        {1}, 
        {1}, 
        {1} 
    });
    singleNeuronNetwork("OR_MODEL", x_train, y_train);
}

void xorNetwork() {
    Matrix x_train({
        {0, 0},
        {1, 0},
        {0, 1},
        {1, 1}
    });
    Matrix y_train({
        {0}, 
        {1}, 
        {1}, 
        {0} 
    });
    singleNeuronNetwork("XOR_MODEL", x_train, y_train);
    print("Its NOT actually POSSIBLE to fit to a XOR operator cause it has a non-linear behavior.\n");
}

int main(int argc, char const *argv[]) {
    andNetwork();
    // nandNetwork();
    // orNetwork();
    // xorNetwork();
    return 0;
}