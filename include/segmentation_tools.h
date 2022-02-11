/*
** File segmentation_tools.h for TechForceOCR
** Made by Victor on 31.10.2020
*/

#ifndef SEGMENTATION_TOOLS_H_
#define SEGMENTATION_TOOLS_H_

/*
** SUMMARY
**
** This file contains the "background" functions for the segmentation part of
** the project.
**
** is_null_line()       - returns 1 is line is full of zeros else 0         [OK]
** v_binary_histogram() - returns a binary histogram of the matrix          [OK]
** list_line_coords()   - retuns an array of arrays of coords and the status[OK]
*/

#include <stdlib.h>

/*
** @brief returns 1 if the line of the binary matrix is full of zeros otherwise
** the function returns 0. This function is used in the v_binary_histogram()
** function that returns a vertical binary histogram (array) of the matrix.
**
** @param matrix : the binary matrix got from the image
** @param line : the line of the binary matrix that we want to analyse
** @param width : the width of the binary matrix (also the width of the image)
**
** @return int *
*/

int is_null_line(int *matrix, size_t line, size_t width);

/*
** @brief returns a one-dimensional array containing 0 or 1 at the spot where
** the corresponding line is 'null' (full of zeros) or not. This function uses
** the is_null_line() function and is used by the list_line_coords() function.
**
** @param matrix : the binary matrix got from the image
** @param height : the height of the binary matrix (also the height of the image)
** @param width : the width of the binary matrix (also the width of the image)
**
** @return int *
*/

int *v_binary_histogram(int *matrix, size_t height, size_t width);

/*
** @brief returns an array of arrays. The subarrays are of dimension 5 and
** contain the coordinates & status (x0, y0, x1, y1, status) for each line of
** the matrix given as parameter.
**
** @param matrix : the binary matrix got from the image
** @param height : the height of the binary matrix (the height of the image)
** @param width : the width of the binary matrix (also the width of the image)
**
** @return size_t **
*/

size_t **list_line_coords(int *matrix, size_t height, size_t width);

int *h_binary_histogram(size_t width, size_t y0, size_t y1, int *matrix);

size_t **list_char_coords_for_dist(size_t width, size_t y0, size_t y1,
                                        int *matrix);

size_t **get_char_coords_for_dist(int *matrix, size_t width, size_t y0,
                                    size_t y1, size_t *length);

size_t average_word_dist(size_t **char_coord_for_dist, size_t length);

int are_chars(size_t **char_coord_for_dist, size_t length_array,
                size_t i_char_1, size_t i_char_2);

size_t **list_word_coords(size_t **char_coord_for_distance,
                            size_t len_arr_chars_for_dist);

void print_lines_words(int *matrix, size_t **line_coordinates, size_t length,
                            size_t width);

int *h_binary_histogram_char(size_t x0, size_t y0, size_t x1, size_t y1,
                                int *matrix, size_t width);

size_t **list_char_coords(size_t x0, size_t y0, size_t x1, size_t y1,
                            int *matrix, size_t width);

// Returns the 28 by 28 arrays of the coordinates of the chars given in @param
size_t *normalize(int *matrix, size_t x0, size_t y0, size_t x1, size_t y1,
                    size_t m_width);

// Returns the numbers of characters in an image
size_t nb_chars(int *matrix, size_t height, size_t width);

// Main segmentation function that regroups all the previous functions
size_t **segment(int *matrix, size_t height, size_t width, size_t *length);

#endif
