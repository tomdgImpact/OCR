#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdlib.h>

#include "characterRecognition.h"

// Sigmoid function (activation function)
double sigmoid(double x);

// Derivative of the sigmoid function
double dsigmoid(double x);

//filling the training set order matrix in order to shuffle the input
void array_to_shuffle(Network *network);


void fill_inputs(Network *network, char *filename);

void fill_inputs_test(Network *network, char *filename);

void fill_expected(Network *network);

size_t maxout(Network *network);
// Shuffling of 'matrix' items randomly
// Needed for the Stochastic Gradient Descent
// Don't forget to generate the random seed
void shuffle(int *matrix, size_t n);

// Returns a double between 0.0 and 0.1
// in order to initialize the weights
double random();

// another activation function
double leakyrelu(double input);

// derivative of another activation function
double dleakyrelu(double input);

#endif
