/*
** File segmentation.h for TechForceOCR
** Made by Victor on 31.10.2020
*/

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

/*
** SUMMARY
**
** This file contains the "foreground" functions for the segmentation part of
** the project.
**
** get_line_coords()    - returns an array of arrays of coords of lines     [OK]
** get_word_coords()    - returns an array of arrays of coords of words     [OK]
** get_cahr_coords()    - returns an array of arrays of coords of chars     [OK]
*/

#include <stdlib.h>

/*
** @brief returns an array of arrays containing only the coordinates of the
** lines of text in a file. Altough this function frees the matrixes or arrays
** initialized, you need to free the array of arrays it returns using the
** function free_array_of_arrays().
**
** @param matrix : the binary matrix got from the image
** @param height : the height of the binary matrix (the height of the image)
** @param width : the width of the binary matrix (also the width of the image)
**
** @return size_t **
*/

size_t **get_line_coords(int *matrix, size_t height, size_t width, 
                            size_t *length);

/*
** @brief returns an array of arrays containing only the coordinates of the
** words in a line. Altough this function free the arrays that are given as
** parameters, it remains important to free the arrays that it returns using the
** function free_array_of_arrays().
**
** @param char_arr_for_dist : matrix of characters segmentation
** @param arr_len : lenght of the char_arr_for_dist matrix
** @param new_length : the length is computed inside the function, should be 0
**
** @return : size_t **
*/

size_t **get_word_coords(size_t **char_arr_for_dist, size_t arr_len, 
                            size_t *new_length);

/*
** @brief returns an array of arrays containing only the coordinates of the
** characters in a word. Altough this function free the array that is given as
** parameter, it remains important to free the array that it returns using the
** function free_array_of_arrays().
**
** @param matrix : the binarized matrix got from the image
** @param x0 : the coordinate x0 of the word
** @param x1 : the coordinate x1 of the word
** @param y0 : the coordinate y0 of the word
** @param y1 : the coordinate y1 of the word
** @param lenght : the new length that is computed, should be 0
** @param width : the width of the binarized matrix
**
** @return : size_t **
*/

size_t **get_char_coords(int *matrix, size_t x0, size_t x1, size_t y0, 
                            size_t y1, size_t *length, size_t width);

#endif