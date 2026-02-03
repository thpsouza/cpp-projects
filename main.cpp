#include <CustomNeuralNetwork/NN.h>
#include <CustomNeuralNetwork/DenseLayer.h>
#include <CustomNeuralNetwork/ActivationFunctions/ActivationFunctions.h>
#include <CustomNeuralNetwork/InitializationFunctions/InitializationFunctions.h>
#include <CustomNeuralNetwork/LossFunctions/LossFunctions.h>
#include <CustomNeuralNetwork/Optimizers/Optimizers.h>
#include <utils.h>
#include <fstream>
#include <chrono>
#include <string>


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

    int input_dim = 2;
    int hidden_layers = 0;
    int hidden_layers_dim = 0;
    int output_dim = 1;
    float learning_rate = 1e-2;
    int epochs = 1e6;

    NN and_NN(input_dim, hidden_layers, hidden_layers_dim, output_dim);
    and_NN.setInitializationFunction(RANDOM);
    and_NN.setActivationFunction(SIGMOID);
    and_NN.setLossFunction(MSE);
    and_NN.setOptimizer(SGD, learning_rate);
    and_NN.initialize();

    and_NN.print();
    print("\n");
    and_NN.fit(x_train, y_train, epochs);
    print("\n");
    and_NN.print();
    print("\n");

    float y[4];
    y[0] = and_NN.predict({0,0});
    y[1] = and_NN.predict({0,1});
    y[2] = and_NN.predict({1,0});
    y[3] = and_NN.predict({1,1});
    print("Predict:\n");
    print("F(0,0): ", y[0], "\n");
    print("F(0,1): ", y[1], "\n");
    print("F(1,0): ", y[2], "\n");
    print("F(1,1): ", y[3], "\n");
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

    int input_dim = 2;
    int hidden_layers = 1;
    int hidden_layers_dim = 2;
    int output_dim = 1;
    float learning_rate = 1e-2;
    int epochs = 1e6;

    NN and_NN(input_dim, hidden_layers, hidden_layers_dim, output_dim);
    and_NN.setInitializationFunction(RANDOM);
    and_NN.setActivationFunction(SIGMOID);
    and_NN.setLossFunction(MSE);
    and_NN.setOptimizer(SGD, learning_rate);
    and_NN.initialize();

    and_NN.print();
    print("\n");
    and_NN.fit(x_train, y_train, epochs);
    print("\n");
    and_NN.print();
    print("\n");

    float y[4];
    y[0] = and_NN.predict({0,0});
    y[1] = and_NN.predict({0,1});
    y[2] = and_NN.predict({1,0});
    y[3] = and_NN.predict({1,1});
    print("Predict:\n");
    print("F(0,0): ", y[0], "\n");
    print("F(0,1): ", y[1], "\n");
    print("F(1,0): ", y[2], "\n");
    print("F(1,1): ", y[3], "\n");
}


void testLinAlg() {
    Matrix W = {
        {-1,2,3},
        {4,-5,6},
        {7,8,9},
    };
    W.print();

    Vector X = {
        10,11,12
    };
    X.print();
}


void saveModel() {
    auto now = std::chrono::system_clock::now();
    std::string filename = std::format("model_{:%Y%m%d_%H%M%S}.txt", now);
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        L1.save(outfile);
        L2.save(outfile);
        outfile.close();
        std::cout << "Model saved to: " << filename << std::endl;
    } else {
        std::cerr << "Error: Could not open file for saving!" << std::endl;
    }
}


int main(int argc, char const *argv[]) {
    // xorNetwork();

    DenseLayer L1(2,2,1);
    DenseLayer L2(2,1,2);
    L1.setActivationFunction(SIGMOID);
    L2.setActivationFunction(SIGMOID);
    L1.setWeights(Matrix{
        {6.467752, 6.467752},
        {4.614151, 4.613075},
    });
    L1.setBiases(Vector{-2.837445, -7.347040});
    L2.setWeights(Matrix{
        {9.391535, -10.341160},
    });
    L2.setBiases(Vector{-4.496364});
    
    // Vector X = {1,1};
    // L1.forward(X);
    // L2.forward(L1.getOutput());
    // L2.getOutput().print();

    // std::ofstream outfile;
    // outfile.open("model.txt");//, std::ios_base::app); // Open in append mode
    // L1.save(outfile);
    // L2.save(outfile);
    // outfile.close();
    saveModel();

    return 0;
}