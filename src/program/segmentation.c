/*
** File segmentation.c for TechForceOCR
** Made by Victor on 31.10.2020
*/

#include "../../include/segmentation.h"
#include "../../include/segmentation_tools.h"
#include "../../include/matrix_tools.h"

#include <stdio.h> // TO REMOVE


/* get_line_coords() */

size_t **get_line_coords(int *matrix, size_t height, size_t width, size_t *length)
{
    size_t nb_coords = 4;
    int status_index = 4;
    size_t nb_lines = 0;

    size_t **arr_of_arr_n_status = NULL;
    arr_of_arr_n_status = list_line_coords(matrix, height, width);

    while (nb_lines < height && arr_of_arr_n_status[nb_lines][status_index])
        ++nb_lines;

    *length = nb_lines; // needed to free the array after the return

    size_t **line_coordinates = init_array_of_arrays(nb_lines, 4);

    for (size_t i = 0; i < nb_lines; i++)
        for (size_t j = 0; j < nb_coords; j++)
            line_coordinates[i][j] = arr_of_arr_n_status[i][j];

    free_array_of_arrays(arr_of_arr_n_status, height);

    return line_coordinates;
}

/* get_word_coords() */

size_t **get_word_coords(size_t **char_arr_for_dist, size_t arr_len, size_t *new_length)
{
    size_t **array_n_status = NULL;
    array_n_status = list_word_coords(char_arr_for_dist, arr_len);

    size_t nb_lines = 0;
    size_t nb_coords = 4;
    size_t status_index = 4;

    while (nb_lines < arr_len && array_n_status[nb_lines][status_index])
        nb_lines++;

    *new_length = nb_lines;

    size_t **word_coords = init_array_of_arrays(nb_lines, 4);

    for (size_t i = 0; i < nb_lines; i++)
        for (size_t j = 0; j < nb_coords; j++)
            word_coords[i][j] = array_n_status[i][j];

    free_array_of_arrays(array_n_status, arr_len);

    return word_coords;
}

/* get_char_coords() */

size_t **get_char_coords(int *matrix, size_t x0, size_t x1, size_t y0, size_t y1, size_t *length, size_t width)
{
    size_t **char_coords_n_status = NULL;
    char_coords_n_status = list_char_coords(x0, y0, x1, y1, matrix, width);

    size_t nb_lines = 0;
    size_t nb_coords = 4;
    size_t status_index = 4;

    while (nb_lines < x1 - x0 + 1 && char_coords_n_status[nb_lines][status_index] == 1)
        nb_lines++;

    *length = nb_lines;

    size_t **char_coords = NULL;
    char_coords = init_array_of_arrays(nb_lines, 4);

    for (size_t i = 0; i < nb_lines; i++)
        for (size_t j = 0; j < nb_coords; j++)
            char_coords[i][j] = char_coords_n_status[i][j];

    free_array_of_arrays(char_coords_n_status, x1 - x0 + 1);

    return char_coords;
}