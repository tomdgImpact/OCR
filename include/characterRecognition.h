#ifndef CHARACTERRECOGNITION_H_
#define CHARACTERRECOGNITION_H_

#include <stdlib.h>

#define NUMINPUTS 784
#define NUMHIDDENNODES 28
#define NUMOUTPUTS 93
#define LR 1.7f
#define NUMTRAININGSETS 93

// Network structure
typedef struct Network
{

    double hiddenLayer[NUMHIDDENNODES];
    double outputLayer[NUMOUTPUTS];

    double hiddenLayerBias[NUMHIDDENNODES];
    double outputLayerBias[NUMOUTPUTS];

    double hiddenWeights[NUMINPUTS][NUMHIDDENNODES];
    double outputWeights[NUMHIDDENNODES ][NUMOUTPUTS];

    double training_inputs[NUMTRAININGSETS][NUMINPUTS];
    double training_outputs[NUMTRAININGSETS][NUMOUTPUTS];

    double *test_inputs;
    int test_lenght;
    int trainingSetOrder[NUMTRAININGSETS];

    double deltaOutput[NUMOUTPUTS];
    double deltaHidden[NUMHIDDENNODES];
} Network;

// propagates the data in the neural network
void feedforward(Network *network, size_t i);

// fills some matrixes of the network with random values
// matrixes are then used for forward feeding and backpropagation
void randomize(Network *network);

// propagates the data back in the neural network
void backpropagation(Network *network, size_t i);

// main training function that
// trains the neural network 'nb_gen' times
void prepare_data_and_train(Network *network, char *str, char *randorload);

void train(size_t nb_gen, Network *network, char *str);

void test(Network *network, char *filename, char *str);

void feedforward_test(Network *network, size_t i);
#endif
