#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../../include/matrix_xor.h"
#include "../../include/xor.h"

void feedforwardx(NetworkX *network, size_t i)
{
    for (size_t j = 0; j < NUMHIDDENNODESX; j++)
    {
        double activation = network->hiddenLayerBias[j];

        for (size_t k = 0; k < NUMINPUTSX; k++)
            activation += network->training_inputs[i][k] *
               network->hiddenWeights[k][j];

        network->hiddenLayer[j] = sigmoidx(activation);
    }

    for (size_t j = 0; j < NUMOUTPUTSX; j++)
    {
        double activation = network->outputLayerBias[j];

        for (size_t k = 0; k < NUMHIDDENNODESX; k++)
            activation += network->hiddenLayer[k] *
            network->outputWeights[k][j];

        network->outputLayer[j] = sigmoidx(activation);
    }

}

void randomizex(NetworkX *network)
{
    for (size_t i = 0; i < NUMINPUTSX; i++)
        for (size_t j = 0; j < NUMHIDDENNODESX; j++)
            network->hiddenWeights[i][j] = randomx();

    for (size_t i = 0; i < NUMHIDDENNODESX; i++)
    {
        network->hiddenLayerBias[i] = randomx();

        for (size_t j = 0; j < NUMOUTPUTSX; j++)
            network->outputWeights[i][j] = randomx();
    }

    for (size_t i = 0; i < NUMOUTPUTSX; i++)
        network->outputLayerBias[i] = randomx();
}

void backpropagationx(NetworkX *network, size_t i)
{
    for (size_t j = 0; j < NUMOUTPUTSX; j++)
    {
        double errOutput = network->training_outputs[i][j] -
            network->outputLayer[j];
        network->deltaOutput[j] = errOutput *
            dsigmoidx(network->outputLayer[j]);
    }

    for (size_t j = 0; j < NUMHIDDENNODESX; j++)
    {
        double errorHidden = 0.0;

        for (size_t k = 0; k < NUMOUTPUTSX; k++)
            errorHidden += network->deltaOutput[k] *
                network->outputWeights[j][k];

        network->deltaHidden[j] = errorHidden *
            dsigmoidx(network->hiddenLayer[j]);
    }

    for (size_t j = 0; j < NUMOUTPUTSX; ++j)
    {
        network->outputLayerBias[j] += network->deltaOutput[j] * LRX;

        for (size_t k = 0; k < NUMHIDDENNODESX; ++k)
            network->outputWeights[k][j] += network->hiddenLayer[k] *
                network->deltaOutput[j] * LRX;
    }

    for (size_t j = 0; j < NUMHIDDENNODESX; j++)
    {
        network->hiddenLayerBias[j] += network->deltaHidden[j] * LRX;

        for (size_t k = 0; k < NUMINPUTSX; k++)
            network->hiddenWeights[k][j] += network->training_inputs[i][k] *
                network->deltaHidden[j] * LRX;
    }
}

void trainx(size_t nb_gen, NetworkX *network)
{
    for (size_t n = 0; n < nb_gen; n++)
    {
        shufflex(network->trainingSetOrder, NUMTRAININGSETSX);

        for (size_t x = 0; x < NUMTRAININGSETSX; x++)
        {
            int i = network->trainingSetOrder[x];

            feedforwardx(network, i);

            double a = network->training_inputs[i][0];
            double b = network->training_inputs[i][1];
            double c = network->outputLayer[0];
            double d = network->training_outputs[i][0];

            printf("[A] : %f [B] : %f  [R] : %f  [ER] : %f\n", a, b, c, d);

            backpropagationx(network, i);
        }
    }

    printf("\n[OUTPUT FORMAT]\n");
    printf("[A] : input A\n");
    printf("[B] : input B\n");
    printf("[R] : network output\n");
    printf("[ER] : expected output\n");
}

void XOR()
{
    srand(time(NULL));

    NetworkX network = {
        .training_inputs = { {0.0,0.0}, {1.0,0.0}, {0.0,1.0}, {1.0,1.0} },
        .training_outputs = { {0.0}, {1.0}, {1.0}, {0.0} },
        .trainingSetOrder = {0, 1, 2, 3}
    };

    // TRAINING
    randomizex(&network);

    trainx(50000, &network);
}