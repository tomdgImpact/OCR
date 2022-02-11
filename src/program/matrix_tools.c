/*
** File matrix_tools.c for TechForceOCR
** Made by Victor on 31.10.2020
*/

#include "../../include/matrix_tools.h"

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

/* init_matrix() */

int *init_matrix(size_t height, size_t width)
{
    int *binary_matrix = NULL;

    binary_matrix = (int *) calloc(height * width, sizeof(int));

    if (binary_matrix == NULL)
        errx(1, "init_matrix : could not initialize the matrix");

    return binary_matrix;
}

/* print_matrix() */

void print_matrix(int *matrix, size_t height, size_t width)
{
    if (matrix != NULL)
    {
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
                printf("%i ", matrix[i * width + j]);

            printf("\n");
        }

        return;
    }

    errx(1, "print_matrix : could not print the matrix");
}

/* save_matrix() */

void save_matrix(int *matrix, size_t height, size_t width, char *path)
{
    FILE *file;
    char *mode = "w";

    if (matrix != NULL)
    {
        file = fopen(path, mode);
        char str_of_int[2];

        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                sprintf(str_of_int, "%d", matrix[i * width + j]);
                fputs(str_of_int, file);
            }

            fputs("\n", file);
        }

        fclose(file);

        return;
    }

    errx(1, "save_matrix : could not print the matrix");
}

/* free_matrix() */

void free_matrix(int *matrix)
{
    if (matrix != NULL)
        free(matrix);
    else
        errx(1, "free_matrix : could not free the matrix");
}

/* init_array_of_arrays() */

size_t **init_array_of_arrays(size_t length, size_t subarray_length)
{
    size_t **array_of_arrays = NULL;

    array_of_arrays = (size_t **) calloc(length, sizeof(size_t *));

    for (size_t i = 0; i < length; i++)
        array_of_arrays[i] = (size_t *) calloc(subarray_length, sizeof(size_t));

    if (array_of_arrays == NULL)
        errx(1, "init_array_of_arrays : could not initialize the array");

    return array_of_arrays;
}

/* free_array_of_arrays() */

void free_array_of_arrays(size_t **array_of_arrays, size_t length)
{
    for (size_t i = 0; i < length; i++)
        free(array_of_arrays[i]);
    free(array_of_arrays);
}

/* print_2D_array() */

void print_2D_array(size_t **array_of_arrays, size_t length, size_t subarray_length)
{
    for (size_t i = 0; i < length; i++)
    {
        printf("%5zu : ", (i + 1));

        for (size_t j = 0; j < subarray_length; j++)
            printf("[%5zu]   ", array_of_arrays[i][j]);
        printf("\n");
    }
}

/* save_line_coords() */

void save_line_coords(size_t **array_of_arrays, size_t length, size_t subarray_length, char *path)
{
    FILE *file;
    char *mode = "w";

    if (array_of_arrays != NULL)
    {
        file = fopen(path, mode);
        char str_of_int[12];

        for (size_t i = 0; i < length; i++)
        {
            for (size_t j = 0; j < subarray_length; j++)
            {
                // if (j == subarray_length / 2) // use modulo 28 to see the characters
                //    fputs("\n", file);
                if (j % 28 == 0)
                    fputs("\n", file);
                sprintf(str_of_int, "%zu", array_of_arrays[i][j]);
                fputs(str_of_int, file);
            }

            fputs("\n", file);
        }

        fclose(file);
        return;
    }

    errx(1, "save_line_coords : could not save the line coordinates");
}

/* print_matrixbis() */

void print_matrixbis(size_t *matrix, size_t height, size_t width)
{
    if (matrix != NULL)
    {
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
                printf("%zu ", matrix[i * width + j]);

            printf("\n");
        }

        return;
    }

    errx(1, "print_matrix : could not print the matrix");
}
