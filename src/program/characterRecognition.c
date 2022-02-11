#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/matrix.h"
#include "../../include/characterRecognition.h"
#include "../../include/save.h"

void feedforward(Network *network, size_t i)
{
    for (size_t j = 0; j < NUMHIDDENNODES; j++)
    {
        double activation = network->hiddenLayerBias[j];

        for (size_t k = 0; k < NUMINPUTS; k++)
            activation += network->training_inputs[i][k] *
               network->hiddenWeights[k][j];

        network->hiddenLayer[j] = sigmoid(activation);
    }

    for (size_t j = 0; j < NUMOUTPUTS; j++)
    {
        double activation = network->outputLayerBias[j];

        for (size_t k = 0; k < NUMHIDDENNODES; k++)
            activation += network->hiddenLayer[k] *
            network->outputWeights[k][j];

        network->outputLayer[j] = sigmoid(activation);
    }
}

void randomize(Network *network)
{
    for (size_t i = 0; i < NUMINPUTS; i++)
        for (size_t j = 0; j < NUMHIDDENNODES; j++)
            network->hiddenWeights[i][j] = random();

    for (size_t i = 0; i < NUMHIDDENNODES; i++)
    {
        network->hiddenLayerBias[i] = random();

        for (size_t j = 0; j < NUMOUTPUTS; j++)
            network->outputWeights[i][j] = random();
    }

    for (size_t i = 0; i < NUMOUTPUTS; i++)
        network->outputLayerBias[i] = random();
}

void backpropagation(Network *network, size_t i)
{
    for (size_t j = 0; j < NUMOUTPUTS; j++)
    {
        double errOutput = network->training_outputs[i][j] -
            network->outputLayer[j];
        network->deltaOutput[j] = errOutput *
            dsigmoid(network->outputLayer[j]);
    }

    for (size_t j = 0; j < NUMHIDDENNODES; j++)
    {
        double errorHidden = 0.0;

        for (size_t k = 0; k < NUMOUTPUTS; k++)
            errorHidden += network->deltaOutput[k] *
                network->outputWeights[j][k];

        network->deltaHidden[j] = errorHidden *
            dsigmoid(network->hiddenLayer[j]);
    }

    for (size_t j = 0; j < NUMOUTPUTS; ++j)
    {
        network->outputLayerBias[j] += network->deltaOutput[j] * LR;

        for (size_t k = 0; k < NUMHIDDENNODES; ++k)
            network->outputWeights[k][j] += network->hiddenLayer[k] *
                network->deltaOutput[j] * LR;
    }

    for (size_t j = 0; j < NUMHIDDENNODES; j++)
    {
        network->hiddenLayerBias[j] += network->deltaHidden[j] * LR;

        for (size_t k = 0; k < NUMINPUTS; k++)
            network->hiddenWeights[k][j] += network->training_inputs[i][k] *
                network->deltaHidden[j] * LR;
    }
}

void prepare_data_and_train(Network *network, char *str, char *randorload)
{
    char fonts[][40] = {
        "dataset/set/arial12.bmp",
        "dataset/set/calibri12.bmp",
        "dataset/set/liberationsans12.bmp",
        "dataset/set/rockwell12.bmp",
        "dataset/set/verdana12.bmp",
        "dataset/set/chars.bmp"
        //"../../images/tech2.bmp"
        };

    // initialisation of the matrixes
    // fill_inputs(&network, "dataset/set/chars.bmp");

    fill_expected(network);

    array_to_shuffle(network);

    if (strcmp(randorload, "rand") == 0)
        randomize(network);

    else
    {
        loadNet(network);
        loaddarray(network->hiddenLayerBias, "hidden_bias.txt");
        loaddarray(network->outputLayerBias, "output_bias.txt");
    }

    for (size_t i = 0; i < 10000; i++)
    {
        // filling with one then the other
        size_t random = rand() % 6;
        fill_inputs(network, fonts[random]);

        printf("%10ld >>> (%40s) >>>", i, fonts[random]);
        train(1, network, str);
    }
}

void train(size_t nb_gen, Network *network, char *str)
{
    double goodanswer = 0.0;
    double total = 0.0;

    for (size_t n = 0; n < nb_gen; n++)
    {
        shuffle(network->trainingSetOrder, NUMTRAININGSETS);

        for (size_t x = 0; x < NUMTRAININGSETS; x++)
        {
            int i = network->trainingSetOrder[x];

            feedforward(network, i);

            char c_input = str[i]; // character

            // index of the letter go by the neural network
            size_t max = maxout(network);

            char c_got = str[max]; //retrieve the character

            printf("[INPUT] : %c [GOT] : %c  [STATUS] : %i\n", c_input, c_got, c_input == c_got);

            if (c_input == c_got)
                goodanswer++;

            total++;

            backpropagation(network, i);
        }

        printf("| CURRENT PRECISION : %10lf\n", goodanswer / total * 100);
    }

    saveNet(network);
    savearrayNet(network);
}

void test(Network *network, char *filename, char *str)
{
    fill_inputs_test(network, filename);

    loaddarray(network->hiddenLayerBias, "hidden_bias.txt");
    loaddarray(network->outputLayerBias, "output_bias.txt");
    loadNet(network);

    size_t nbspace = 0;
    char c;
    FILE *file = fopen("text_sample.txt", "w");
    for (int i = 0; i < network->test_lenght; ++i)
    {
        feedforward_test(network, i);

        size_t max = maxout(network);
         c = str[max];

        if (c == ' ')
            ++nbspace;

        if (nbspace == 15)
        {
            c = '\n';
             fputc(c, file);
        }
        else
             fputc(c, file);
    }
    c = '\n';
    fputc(c, file);
    fclose(file);
    free(network->test_inputs);
}

void feedforward_test(Network *network, size_t i)
{
    for (size_t j = 0; j < NUMHIDDENNODES; j++)
    {
        double activation = network->hiddenLayerBias[j];

        for (size_t k = 0; k < NUMINPUTS; k++)
            activation += network->test_inputs[i * NUMINPUTS + k] *
               network->hiddenWeights[k][j];

        network->hiddenLayer[j] = sigmoid(activation);
    }

    for (size_t j = 0; j < NUMOUTPUTS; j++)
    {
        double activation = network->outputLayerBias[j];

        for (size_t k = 0; k < NUMHIDDENNODES; k++)
            activation += network->hiddenLayer[k] *
            network->outputWeights[k][j];

        network->outputLayer[j] = sigmoid(activation);
    }
}