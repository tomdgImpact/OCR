#include <math.h>

#include "../../include/matrix.h"
#include "../../include/characterRecognition.h"
#include "../../include/matrix_tools.h"
#include "../../include/sdl_tools.h"
#include "../../include/binarization.h"
#include "../../include/segmentation.h"
#include "../../include/segmentation_tools.h"
#include "../../include/finalrotate.h"
#include "../../include/grayscale.h"
#include "../../include/enhancement.h"
#include "../../include/noise_cancelling.h"

size_t maxout(Network *network)
{
    size_t index = 0;
    double max = 0.0;

    for (size_t i = 0; i < NUMOUTPUTS; i++)
    {
        if (network->outputLayer[i] > max)
        {
            index = i;
            max = network->outputLayer[i];
        }
    }

    return index;
}

void fill_expected(Network *network)
{
    for (size_t i = 0; i < NUMTRAININGSETS; ++i)
    {
        for (size_t j = 0; j < NUMOUTPUTS; ++j)
            network->training_outputs[i][j] = 0.0;

        network->training_outputs[i][i] = 1.0; // STOPPED HERE !!!!
    }
}

void fill_inputs(Network *network, char *filename)
{
    init_sdl();

    SDL_Surface *image = NULL;
    int *binary_matrix = NULL;

    image = load_image(filename);

    size_t height = image->h;
    size_t width = image->w;

    image = Grayscale(image);
    image = Enhanc(image);
    image = Noise(image);
    image = Black_white(image);
    // creates the matrix of 0s and 1s
    binary_matrix = binarize(image);

    size_t **array = NULL;
    size_t length = 0;

    array = segment(binary_matrix, height, width, &length);

    // save_line_coords(array, length, 28*28, "REAL_SEGMENTATION.txt");

    for (size_t i = 0; i < NUMTRAININGSETS; ++i)
    {
        for (size_t j = 0; j < NUMINPUTS; ++j)
        {
            network->training_inputs[i][j] = (double) array[i][j]; // added explicit cast
        }
    }

    SDL_FreeSurface(image);

    free_matrix(binary_matrix);

    free_array_of_arrays(array, length);
}

double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double dsigmoid(double x)
{
    return x * (1 - x);
}

void array_to_shuffle(Network *network)
{
    for (size_t i = 0; i < 94; i++)
        network->trainingSetOrder[i] = i;
}

void shuffle(int *matrix, size_t n)
{
    if (n > 1)
    {
        size_t i;

        for (i = 0; i < n - 1; i++)
        {
            // value between 0.0 and 1.0
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);

            int t = matrix[j];
            matrix[j] = matrix[i];
            matrix[i] = t;
        }
    }
}

double random()
{
    return ((double) rand()) / ((double) RAND_MAX);
}

double leakyrelu(double input)
{
    return input > 0 ? input : (0.01 * input);
}

double dleakyrelu(double input)
{
    return input > 0 ? 1 : 0.01;
}


void fill_inputs_test(Network *network, char *filename)
{
    init_sdl();

    SDL_Surface *image = NULL;
    int *binary_matrix = NULL;

    image = load_image(filename);

    size_t height = image->h;
    size_t width = image->w;

    image = image_deskew(image);
    image = Grayscale(image);
    image = Enhanc(image);
    image = Noise(image);
    image = Black_white(image);
    // creates the matrix of 0s and 1s
    binary_matrix = binarize(image);

    size_t **array = NULL;
    size_t length = 0;

    array = segment(binary_matrix, height, width, &length);

    network->test_inputs = malloc(length * NUMINPUTS * sizeof(double));
    // save_line_coords(array, length, 28*28, "FILE.txt");
    network->test_lenght = length;
    for (size_t i = 0; i < length; ++i)
    {
        for (size_t j = 0; j < NUMINPUTS; ++j)
        {
            network->test_inputs[i * NUMINPUTS + j] = (double) array[i][j]; // added explicit cast
        }
    }

    // TO REMOVE
    save_line_coords(array, length, 28*28, "TRAINING_SEGMENTATIONS.txt");

    SDL_FreeSurface(image);

    free_matrix(binary_matrix);

    free_array_of_arrays(array, length);
}