#include <math.h>

#include "../../include/matrix_xor.h"

double sigmoidx(double x)
{
    return 1 / (1 + exp(-x));
}

double dsigmoidx(double x)
{
    return x * (1 - x);
}

void shufflex(int *matrix, size_t n)
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

double randomx()
{
    return ((double) rand()) / ((double) RAND_MAX);
}
