#ifndef MATRIX_XOR_H_
#define MATRIX_XOR_H_

#include <stdlib.h>

#include "xor.h"

// Sigmoid function (activation function)
double sigmoidx(double x);

// Derivative of the sigmoid function
double dsigmoidx(double x);

//filling the training set order matrix in order to shuffle the input

// Shuffling of 'matrix' items randomly
// Needed for the Stochastic Gradient Descent
// Don't forget to generate the random seed
void shufflex(int *matrix, size_t n);

// Returns a double between 0.0 and 0.1
// in order to initialize the weights
double randomx();

#endif
