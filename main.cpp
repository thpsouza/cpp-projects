// #include <LinearAlgebra/LinAlg.h>
#include <CustomNeuralNetwork/NN.h>
#include <utils.h>


int main(int argc, char const *argv[]) {
    Matrix x_train({
        {0, 0},
        {1, 0},
        {0, 1},
        {1, 1}
    });
    // x_train.print();
    // print(std::string(x_train.getShape()), "\n");

    Matrix y_train({
        {0}, 
        {0}, 
        {0}, 
        {1} 
    });
    // y_train.print();
    // print(std::string(y_train.getShape()), "\n");

    NN and_NN(2);
    and_NN.initialize();
    and_NN.setActivationFunction(SIGMOID);
    and_NN.setLossFunction(MSE);
    // and_NN.setOptimizer(ADAM);
    and_NN.fit(x_train, y_train, 20, 1e-3);
    // float y = and_NN.predict({1,1});
    // print(y, "\n");

    return 0;
}