#ifndef XOR_H_
#define XOR_H_

#define NUMINPUTSX 2
#define NUMHIDDENNODESX 2
#define NUMOUTPUTSX 1
#define LRX 1.7f
#define NUMTRAININGSETSX 4

// Network structure
typedef struct NetworkX
{

    double hiddenLayer[NUMHIDDENNODESX];
    double outputLayer[NUMOUTPUTSX];

    double hiddenLayerBias[NUMHIDDENNODESX];
    double outputLayerBias[NUMOUTPUTSX];

    double hiddenWeights[NUMINPUTSX][NUMHIDDENNODESX];
    double outputWeights[NUMHIDDENNODESX ][NUMOUTPUTSX];

    double training_inputs[NUMTRAININGSETSX][NUMINPUTSX];
    double training_outputs[NUMTRAININGSETSX][NUMOUTPUTSX];

    int trainingSetOrder[NUMTRAININGSETSX];

    double deltaOutput[NUMOUTPUTSX];
    double deltaHidden[NUMHIDDENNODESX];
} NetworkX;

void XOR();
#endif