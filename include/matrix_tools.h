/*
** File matrix_tools.h for TechForceOCR
** Made by Victor on 31.10.2020
*/

#ifndef MATRIX_TOOLS_H_
#define MATRIX_TOOLS_H_

/*
** SUMMARY
**
** This file contains the tools for matrix manipulation.
**
** init_matrix()            - initializes a empty matrix (height x width)   [OK]
** print_matrix()           - prints the matrix on the terminal             [OK]
** save_matrix()            - pretty-prints the matrix in a file            [OK]
** free_matrix()            - frees the previously allocated memory         [OK]
** init_array_of_arrays()   - initializes an array of arrays                [OK]
** free_array_of_arrays()   - frees an array of arrays                      [OK]
** print_2D_array()         - prints a 2D array on the terminal             [OK]
** save_line_coords()       - saves the coordinates of the lines in a file  [OK]
** print_matrixbis()        - another way of printing on the terminal       [OK]
*/

#include <stdlib.h>

/*
** @brief initializes an empty matrix filled with zeros of size width and
** height, this matrix will be used as the binarized matrix. It has to be filled
** with ones using the fill_matrix() function.
**
** @param height : height of the image
** @param width : width of the image
**
** @return int *
*/

int *init_matrix(size_t height, size_t width);

/*
** @brief pretty-prints the matrix on the terminal. Pay attention, if the matrix
** is too large you will have to unzoom to see it as it really is. Also not that
** you should use this function only if you need to know whats is happening. An
** alternative to this function is the save_matrix() that saves the matrix
** reprensentation in a text file.
**
** @param matrix : the matrix got from binarize() or init_matrix()
** @param height : height of the image / of the matrix
** @param width : width of the image / of the matrix
**
** @return void
*/

void print_matrix(int *matrix, size_t height, size_t width);

/*
** @brief pretty-prints the matrix in a file and then saves it as 'filename'. If
** the file doesn't exists then it is created. If it exists then it is
** overwritten.
**
** @param matrix : the matrix from init_matrix() or binarize()
** @param height : height of the matrix / or the image
** @param width : width of the matrix / or the image
** @param path : path of the saved file
**
** @return void
*/

void save_matrix(int *matrix, size_t height, size_t width, char *path);

/*
** @brief frees the matrix given in parameter if it has been initialized. This
** function is mandatory and you probably want to use it at the end of the
** execution to avoid memory leaks.
**
** @param matrix : the matrix from init_matrix() or binarize()
**
** @return void
*/

void free_matrix(int *matrix);

/*
** @brief initializes an array of arrays of length 'length' where each subarray
** is of length 'subarray_length'. This function is used in the context of
** segmentation particularly when you need to store the coordinates of different
** elements of the binary matrix.
**
** @param length : the length of array (ex. height of the image for lines)
** @param subarray_length : length of each array in the array
**
** @return size_t **
*/

size_t **init_array_of_arrays(size_t length, size_t subarray_length);

/*
** @brief frees an array of arrays dynamically allocated from the memory. You
** will probably want to use this function at the end of the execution.
**
** @param array_of_arrays : the array_of_arrays to be freed
** @param length : the length of array
**
** @return void
*/

void free_array_of_arrays(size_t **array_of_arrays, size_t length);

/*
** @brief prints a two-dimensional array on the terminal. The style is
** predefined by myself (lol).
**
** @param array_of_arrays : the array_of_arrays to be print on the terminal
** @param length : the length of the array
** @param sublength : the length of the subarrays
**
** @return void
*/

void print_2D_array(size_t **array_of_arrays, size_t length,
                        size_t subarray_length);

/*
** @brief saves the coordinates of the lines in a file given as parameter. If
** the file doesn't exist then it is created.
**
** @param array_of_arrays : the array_of_arrays to be saved
** @param length : the length of the array
** @param sublength : the length of the subarrays
** @param path : the path of the file in which the coordinates will be stored
**
** @return void
*/

void save_line_coords(size_t **array_of_arrays, size_t length,
                        size_t subarray_length, char *path);

/*
** @brief another way of displaying the matrix in the terminal mostly used for
** testing
**
** @param matrix : the two-dimensionnal matrix
** @param height : the height of the matrix
** @param width : the width of the matrix
**
** @return void
*/

void print_matrixbis(size_t *matrix, size_t height, size_t width);

#endif
