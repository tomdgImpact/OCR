#include <stdio.h>
#include <err.h>
#include <string.h>

#include "../../include/characterRecognition.h"
/*
** FORMAT : x y data
*/

// Saves the matrix data in a file named 'filename'
// using the format FORMAT
void save(double (*data)[][10],size_t rows, size_t cols, char *filename)
{
    FILE *file = fopen(filename, "w");

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            fprintf(file, "%zu %zu %lf\n", i, j, (*data)[i][j]);

    fclose(file);
}

void saveNet(Network *network)
{
    //saving hiddenweights
    FILE *file = fopen("hidden_weights.txt", "w");
    for (size_t i = 0; i < NUMINPUTS; ++i)
        for (size_t j = 0; j < NUMHIDDENNODES; ++j)
            fprintf(file, "%zu %zu %lf\n", i, j, network->hiddenWeights[i][j]);
    fclose(file);

    //saving outputsweights
    FILE *file2 = fopen("outputs_weights.txt", "w");
    for (size_t i = 0; i < NUMHIDDENNODES; ++i)
        for (size_t j = 0; j < NUMOUTPUTS; ++j)
            fprintf(file2, "%zu %zu %lf\n", i, j, network->outputWeights[i][j]);
    fclose(file2);
}

void savearray(double *data, size_t rows, char *filename)
{
    FILE *file = fopen(filename, "w");

    for (size_t i = 0; i < rows; ++i)
        fprintf(file, "%zu %lf\n", i, data[i]);

    fclose(file);
}

void savearrayNet(Network *network)
{
    //hidden bias
    FILE *file = fopen("hidden_bias.txt", "w");

    for (size_t i = 0; i < NUMHIDDENNODES; ++i)
        fprintf(file, "%zu %lf\n", i, network->hiddenLayerBias[i]);

    fclose(file);

    //save output bias
    FILE *file2 = fopen("output_bias.txt", "w");

    for (size_t i = 0; i < NUMOUTPUTS; ++i)
        fprintf(file2, "%zu %lf\n", i, network->outputLayerBias[i]);

    fclose(file2);
}

void loadNet(Network *network)
{
    // FIRST MATRIX
    FILE *file = fopen("hidden_weights.txt", "r");

    if (file == NULL)
        errx(1, "Can't open file hidden_weights.txt ");

    char c[1000];
    size_t x = 0;
    size_t y = 0;
    double datas;

    char *coord = NULL;

    while (fgets(c,sizeof(c),file) != NULL)
    {
        coord = strtok(c, " ");
        x = atoi(coord);
        coord = strtok(NULL, " ");
        y = atoi(coord);
        coord = strtok(NULL, "\n");
        char *endptr;
        datas = strtod(coord, &endptr);
        network->hiddenWeights[x][y] = datas;
    }

    fclose(file);

    // SECOND MATRIX

    FILE *file2 = fopen("outputs_weights.txt", "r");

    if (file2 == NULL)
        errx(1, "Can't open output_weights.txt");

    char c2[1000];
    size_t x2 = 0;
    size_t y2 = 0;
    double datas2;

    char *coord2 = NULL;

    while (fgets(c2,sizeof(c2),file2) != NULL)
    {
        coord2 = strtok(c2, " ");
        x2 = atoi(coord2);
        coord2 = strtok(NULL, " ");
        y2 = atoi(coord2);
        coord2 = strtok(NULL, "\n");
        char *endptr;
        datas2 = strtod(coord2, &endptr);
        network->outputWeights[x2][y2] = datas2;
    }

    fclose(file2);
}

void loaddarray(double *data, char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
        errx(1, "Can't open file in loadarray()");

    char c[1000];
    int x = 0;
    double datas;

    while (fgets(c, sizeof(c), file) != NULL)
    {
        char *coord = strtok(c, " ");
        x = atoi(coord);
        coord = strtok(NULL, "\n");
        char *endptr;
        datas = strtod(coord, &endptr);
        data[x] = datas;
    }

    fclose(file);
}

void put_in_file(char c, char *filename)
{
    FILE *file = fopen(filename, "a");
    fputc(c, file);
    fclose(file);
}