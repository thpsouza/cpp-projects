#include <CustomNeuralNetwork/NN.h>
#include <CustomNeuralNetwork/DenseLayer.h>
#include <CustomNeuralNetwork/ActivationFunctions/ActivationFunctions.h>
#include <CustomNeuralNetwork/InitializationFunctions/InitializationFunctions.h>
#include <CustomNeuralNetwork/LossFunctions/LossFunctions.h>
#include <CustomNeuralNetwork/Optimizers/Optimizers.h>
#include <utils.h>
#include <string>

void testLinearAlgebra() {
    Matrix W1 ({ // 4x3
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    });
    Matrix W2 ({ // 3x4
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    });
    Matrix W3 ({ // 5x1
        {13}, {14}, {15}, {16}, {17}
    });
    Vector X ({18, 19, 20}); // 3x1

    W1.dot(X).print(); // 4x1
    W2.transposedDot(X).print(); // 4x1
    W3.dotTransposed(X).print(); // 5x3
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


void testForwardBackward() {
    Vector X ({0,0});
    Vector Y ({0});

    NN model("Test", 2, 1, 1, 1);
    model.setInitializationFunction(RANDOM);
    model.setActivationFunction(SIGMOID);
    model.setLossFunction(MSE);
    model.setOptimizer(SGD, 1e-3);
    model.initialize();
    
    model.forward(X.getRow(0));
    model.getOutput().print();
    
    model.forward(Vector{0,0});
    model.getOutput().print();
    
    model.backward(Y.getRow(0));
    model.backward(Vector{0});
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
    float learning_rate = 1e-1;
    int epochs = 1e6;

    NN model("Xor", input_dim, hidden_layers, hidden_layers_dim, output_dim);
    // model.setInitializationFunction(RANDOM);
    // model.setActivationFunction(SIGMOID);
    // model.setLossFunction(MSE);
    // model.setOptimizer(SGD, learning_rate);
    // model.initialize();
    // model.print(); print("\n");
    // model.fit(x_train, y_train, epochs);
    // model.save("XorModel.txt");
    model = NN();
    model.load("XorModel.txt");
    model.print();
    
    Vector y[4];
    y[0] = model.predict({0,0});
    y[1] = model.predict({0,1});
    y[2] = model.predict({1,0});
    y[3] = model.predict({1,1});
    print("Predict:\n");
    print("F(0,0): ", y[0].getElements()[0], "\n");
    print("F(0,1): ", y[1].getElements()[0], "\n");
    print("F(1,0): ", y[2].getElements()[0], "\n");
    print("F(1,1): ", y[3].getElements()[0], "\n");
}


int main(int argc, char const *argv[]) {
    // testLinearAlgebra();
    // testLayer();
    // testSaveLoad();
    // testForwardBackward();
    xorNetwork();
    return 0;
}