#include <CustomNeuralNetwork/NN.h>
#include <CustomNeuralNetwork/DenseLayer.h>
#include <CustomNeuralNetwork/ActivationFunctions/ActivationFunctions.h>
#include <CustomNeuralNetwork/InitializationFunctions/InitializationFunctions.h>
#include <CustomNeuralNetwork/LossFunctions/LossFunctions.h>
#include <CustomNeuralNetwork/Optimizers/Optimizers.h>
#include <utils.h>
#include <string>


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

    NN model(input_dim, hidden_layers, hidden_layers_dim, output_dim);
    model.setInitializationFunction(RANDOM);
    model.setActivationFunction(SIGMOID);
    model.setLossFunction(MSE);
    model.setOptimizer(SGD, learning_rate);
    model.initialize();

    model.print();
    print("\n");
    // model.fit(x_train, y_train, epochs);
    print("\n");
    model.print();
    print("\n");

    Vector y[4];
    y[0] = model.predict({0,0});
    y[1] = model.predict({0,1});
    y[2] = model.predict({1,0});
    y[3] = model.predict({1,1});
    // print("Predict:\n");
    // print("F(0,0): ", y[0], "\n");
    // print("F(0,1): ", y[1], "\n");
    // print("F(1,0): ", y[2], "\n");
    // print("F(1,1): ", y[3], "\n");
}


void testLayer() {
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

    Vector X = {1,1};
    L2.forward(L1.forward(X));
    L2.getOutput().print();
}


void testSaveLoad() {
    int input_dim = 5;
    int hidden_layers = 2;
    int hidden_layers_dim = 2;
    int output_dim = 1;
    NN model("SaveLoadTest", input_dim, hidden_layers, hidden_layers_dim, output_dim);
    model.setInitializationFunction(RANDOM);
    model.setActivationFunction(SIGMOID);
    model.setLossFunction(MSE);
    model.setOptimizer(SGD);
    model.initialize();
    model.save("SaveLoadTest.txt");
    model = NN();
    model.load("SaveLoadTest.txt");
    model.print();
}


int main(int argc, char const *argv[]) {
    // xorNetwork();
    // testLayer();
    testSaveLoad();

    // int input_dim = 2;
    // int hidden_layers = 1;
    // int hidden_layers_dim = 2;
    // int output_dim = 1;
    // float learning_rate = 1e-2;
    // int epochs = 1e6;

    // NN model("Test1", input_dim, hidden_layers, hidden_layers_dim, output_dim);
    // model.setInitializationFunction(RANDOM);
    // model.setActivationFunction(SIGMOID);
    // model.setLossFunction(MSE);
    // model.setOptimizer(SGD, learning_rate);
    // model.initialize();
    // model.print();
    // // model.fit(x_train, y_train, epochs);
    // Vector X = {1,1};
    // model.forward(X);
    // model.getOutput().print();

    return 0;
}