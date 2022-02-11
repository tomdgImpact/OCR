/*
** File segmentation_tools.c for TechForceOCR
** Made by Victor on 31.10.2020
*/

#include "../../include/segmentation.h"
#include "../../include/matrix_tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* is_null_line() */

int is_null_line(int *matrix, size_t line, size_t width)
{
    for (size_t j = 0; j < width; j++)
        if (matrix[line * width + j] == 1)
            return 0;

    return 1;
}

/* v_binary_histogram() */

int *v_binary_histogram(int *matrix, size_t height, size_t width)
{
    int *binary_histogram = (int *)calloc(height, sizeof(int));

    for (size_t i = 0; i < height; i++)
        if (!is_null_line(matrix, i, width))
            binary_histogram[i] = 1;

    return binary_histogram;
}

/* list_line_coords() */

size_t **list_line_coords(int *matrix, size_t height, size_t width)
{
    size_t **arr_of_arr_n_status = init_array_of_arrays(height, 5);

    int *binary_histogram = NULL;
    binary_histogram = v_binary_histogram(matrix, height, width);

    size_t i_mat = 0;
    size_t j_hist = 0;
    size_t k_tmp = 0;

    /* indexes */
    int x0 = 0;
    int y0 = 1;
    int x1 = 2;
    int y1 = 3;
    int status = 4;

    while (j_hist < height)
    {
        if (binary_histogram[j_hist] == 1)
        {
            /* status */
            arr_of_arr_n_status[i_mat][status] = 1;

            /* x0 and y0 of the text line */
            arr_of_arr_n_status[i_mat][x0] = 0;
            arr_of_arr_n_status[i_mat][y0] = j_hist;

            k_tmp = j_hist;

            while (k_tmp < height && binary_histogram[k_tmp] != 0)
                ++k_tmp;

            /* x1 and y1 of the text line */
            arr_of_arr_n_status[i_mat][x1] = width - 1;
            arr_of_arr_n_status[i_mat][y1] = k_tmp - 1;

            j_hist = k_tmp;

            i_mat++;
        }
        else
            ++j_hist;
    }

    free(binary_histogram);

    return arr_of_arr_n_status;
}

/* is_null_column() */

int is_null_column(int *matrix, size_t width, size_t y1, size_t y0, size_t column)
{
    for (size_t i = y0; i <= y1; i++)
        if (matrix[i * width + column] == 1)
            return 0;

    return 1;
}

/* h_binary_histogram() */

int *h_binary_histogram(size_t width, size_t y0, size_t y1, int *matrix)
{
    int *binary_histogram = (int *) calloc(width, sizeof(int));

    for (size_t i = 0; i < width; i++)
        if (!is_null_column(matrix, width, y1, y0, i))
            binary_histogram[i] = 1;

    return binary_histogram;
}

/* list_char_coords() */

size_t **list_char_coords_for_dist(size_t width, size_t y0, size_t y1, int *matrix)
{
    size_t **arr_of_arr_n_status = init_array_of_arrays(width, 5);

    int *binary_histogram = NULL;
    binary_histogram = h_binary_histogram(width, y0, y1, matrix);

    size_t i_hist = 0;
    size_t j_tmp = 0;
    size_t k_coords = 0;

    // indexes
    size_t i_x0 = 0;
    size_t i_y0 = 1;
    size_t i_x1 = 2;
    size_t i_y1 = 3;
    size_t status = 4;

    while (i_hist < width)
    {
        if (binary_histogram[i_hist] == 1)
        {
            j_tmp = i_hist;

            while (j_tmp < width && binary_histogram[j_tmp] == 1)
                j_tmp++;

            // reminder : k0[ x0, y0, x1, y1, status]

            arr_of_arr_n_status[k_coords][i_x0] = i_hist;
            arr_of_arr_n_status[k_coords][i_x1] = j_tmp - 1;

            arr_of_arr_n_status[k_coords][i_y0] = y0;
            arr_of_arr_n_status[k_coords][i_y1] = y1;

            arr_of_arr_n_status[k_coords][status] = 1;

            i_hist = j_tmp;
            k_coords++;
        }
        else
            i_hist++;
    }

    free(binary_histogram);

    return arr_of_arr_n_status;
}

/*
** Returns an array of array containing the coordinates of each character of a
** line from y0 to y1.
*/

size_t **get_char_coords_for_dist(int *matrix, size_t width, size_t y0, size_t y1, size_t *length)
{
    size_t status_index = 4;
    size_t nb_coords = 4;
    size_t nb_lines = 0;

    size_t **arr_of_arr_n_status = NULL;
    arr_of_arr_n_status = list_char_coords_for_dist(width, y0, y1, matrix);

    while (nb_lines < width && arr_of_arr_n_status[nb_lines][status_index])
        nb_lines++;

    *length = nb_lines; // needed to free the array after the return

    size_t **char_coordinates = init_array_of_arrays(nb_lines, 4);

    for (size_t i = 0; i < nb_lines; i++)
        for (size_t j = 0; j < nb_coords; j++)
            char_coordinates[i][j] = arr_of_arr_n_status[i][j];

    free_array_of_arrays(arr_of_arr_n_status, width);

    return char_coordinates;
}

/*
** Given an array of arrays of the characters of a line, returns the average
** distance between those characters in this line. This function is used to
** know if we are at the end of a word or not.
*/

size_t average_word_dist(size_t **char_coord_for_dist, size_t length)
{
    // length being the actual number of characters on the line
    size_t average_dist = 0;

    // indexes
    size_t x0 = 0;
    size_t x1 = 2;

    // the -1 is mandatory for the substraction to get the exact number
    // of white pixels in between characters
    for (size_t i = 0; i < length - 1; i++)
        average_dist += (char_coord_for_dist[i + 1][x0] - char_coord_for_dist[i][x1] - 1);

    return average_dist / length;
}

int are_chars(size_t **char_coord_for_dist, size_t length_array, size_t i_char_1, size_t i_char_2)
{
    size_t avg_dist = average_word_dist(char_coord_for_dist, length_array);

    // returns 1 if the distance between characters is lower or equal to
    // avg_dist else returns 0

    // indexes
    size_t x0 = 0;
    size_t x1 = 2;

    size_t dist = char_coord_for_dist[i_char_2][x0] - char_coord_for_dist[i_char_1][x1] - 1;

    if (dist <= avg_dist)
        return 1;

    return 0;
}

// You want a function that given an array of characters it returns an array
// containing the coordinates of each word for that specific line

size_t **list_word_coords(size_t **char_coord_for_distance, size_t len_arr_chars_for_dist)
{
    size_t nb_coords_n_status = 5;

    size_t **word_coords_n_status = NULL;
    word_coords_n_status = init_array_of_arrays(len_arr_chars_for_dist, nb_coords_n_status);

    // indexes
    size_t x0 = 0;
    size_t y0 = 1;
    size_t x1 = 2;
    size_t y1 = 3;
    size_t status = 4;

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    while (i < len_arr_chars_for_dist)
    {
        j = i;

        while (j < len_arr_chars_for_dist - 1 &&
               are_chars(char_coord_for_distance, len_arr_chars_for_dist, j, j + 1))
            j++;

        word_coords_n_status[k][x0] = char_coord_for_distance[i][x0];
        word_coords_n_status[k][y0] = char_coord_for_distance[i][y0];
        word_coords_n_status[k][x1] = char_coord_for_distance[j][x1];
        word_coords_n_status[k][y1] = char_coord_for_distance[j][y1];

        word_coords_n_status[k][status] = 1;

        k++;
        i = j + 1;
    }

    return word_coords_n_status;
}

void print_lines_words(int *matrix, size_t **line_coordinates, size_t length, size_t width)
{
    for (size_t i = 0; i < length; i++)
    {
        printf("Line : %5zu\n", i + 1);

        size_t **char_coord_for_dist = NULL;
        size_t len_arr_chars_for_dist = 0;
        char_coord_for_dist = get_char_coords_for_dist(matrix, width, line_coordinates[i][1], line_coordinates[i][3], &len_arr_chars_for_dist);

        size_t **word_coords = NULL;
        size_t len_arr_words = 0;
        word_coords = get_word_coords(char_coord_for_dist, len_arr_chars_for_dist, &len_arr_words);

        print_2D_array(word_coords, len_arr_words, 4);

        free_array_of_arrays(char_coord_for_dist, len_arr_chars_for_dist);
        free_array_of_arrays(word_coords, len_arr_words);

        printf("\n");
    }
}

int *h_binary_histogram_char(size_t x0, size_t y0, size_t x1, size_t y1, int *matrix, size_t width)
{
    int * binary_histogram = NULL;
    binary_histogram = (int *) calloc(x1 - x0 + 1, sizeof(int));

    for (size_t i = x0; i <= x1; i++)
        if (!is_null_column(matrix, width, y1, y0, i))
            binary_histogram[i - x0] = 1;
    return binary_histogram;
}

size_t **list_char_coords(size_t x0, size_t y0, size_t x1, size_t y1, int *matrix, size_t width)
{
    size_t **arr_of_arr_n_status = init_array_of_arrays(x1 - x0 + 1, 5);

    int *binary_histogram = NULL;
    binary_histogram = h_binary_histogram_char(x0, y0, x1, y1, matrix, width);

    size_t i_hist = 0;
    size_t j_tmp = 0;
    size_t k_coords = 0;

    // indexes
    size_t i_x0 = 0;
    size_t i_y0 = 1;
    size_t i_x1 = 2;
    size_t i_y1 = 3;
    size_t status = 4;

    while (i_hist + x0 <= x1)
    {
        if (binary_histogram[i_hist] == 1)
        {
            j_tmp = i_hist;

            while ((j_tmp + x0) <= x1 && binary_histogram[j_tmp] == 1)
                j_tmp++;

            // reminder : k0[ x0, y0, x1, y1, status]

            arr_of_arr_n_status[k_coords][i_x0] = i_hist + x0;
            arr_of_arr_n_status[k_coords][i_x1] = j_tmp - 1 + x0;

            arr_of_arr_n_status[k_coords][i_y0] = y0;
            arr_of_arr_n_status[k_coords][i_y1] = y1;

            arr_of_arr_n_status[k_coords][status] = 1;

            i_hist = j_tmp;
            k_coords++;
        }
        else
            i_hist++;
    }

    free(binary_histogram);

    return arr_of_arr_n_status;
}

size_t *normalize(int *matrix, size_t x0, size_t y0, size_t x1, size_t y1, size_t m_width)
{
    size_t arr_width = 28;

    size_t *array = (size_t *) calloc(28 * 28, sizeof(size_t));

    size_t char_width = x1 - x0 + 1;
    size_t char_height = y1 - y0 + 1;

    for (size_t i = 0; i < char_height; i++)
        for (size_t j = 0; j < char_width; j++)
            array[i * arr_width + j] = matrix[(i + y0) * m_width + (j + x0)];

    return array;
}

size_t nb_chars(int *matrix, size_t height, size_t width)
{
    size_t result = 0;

    size_t **line_coords = NULL;
    size_t len_arr_lines = 0;
    line_coords = get_line_coords(matrix, height, width, &len_arr_lines);

    // index values
    size_t y0 = 1;
    size_t y1 = 3;

    for (size_t i = 0; i < len_arr_lines; i++)
    {
        size_t **chars_dist = NULL;
        size_t len_chars_dist = 0;

        chars_dist = get_char_coords_for_dist(matrix, width, line_coords[i][y0], line_coords[i][y1], &len_chars_dist);
        result += len_chars_dist;

        size_t **word_cords = NULL;
        size_t len_arr_words = 0;
        word_cords = get_word_coords(chars_dist, len_chars_dist, &len_arr_words);

        // This part is for adding space to the array for "empty characters" :
        // a space between words

        result += (len_arr_words - 1);
        free_array_of_arrays(chars_dist, len_chars_dist);
        free_array_of_arrays(word_cords, len_arr_words);
    }

    free_array_of_arrays(line_coords, len_arr_lines);
    // printf("RESULT : %zu\n", result); // HERE
    return result;
}

size_t **segment(int *matrix, size_t height, size_t width, size_t *length)
{
    size_t **line_coords = NULL;
    size_t len_arr_lines = 0;
    line_coords = get_line_coords(matrix, height, width, &len_arr_lines);

    size_t nbchars = nb_chars(matrix, height, width);

    size_t subarray_size = 28 * 28;
    size_t **array = init_array_of_arrays(nbchars, subarray_size);
    *length = nbchars;

    // index values
    size_t x0 = 0;
    size_t y0 = 1;
    size_t x1 = 2;
    size_t y1 = 3;

    size_t arr_index = 0;


    for (size_t i = 0; i < len_arr_lines; i++)
    {
        size_t **chars_dist = NULL;
        size_t len_chars_dist = 0;
        chars_dist = get_char_coords_for_dist(matrix, width, line_coords[i][y0], line_coords[i][y1], &len_chars_dist);

        size_t **word_cords = NULL;
        size_t len_arr_words = 0;
        word_cords = get_word_coords(chars_dist, len_chars_dist, &len_arr_words);

        // printf("len_arr_words = %zu\n", len_arr_words);
        for (size_t j = 0; j < len_arr_words; j++)
        {
            size_t **char_coords = NULL;
            size_t len_chars = 0;
            char_coords = get_char_coords(matrix, word_cords[j][x0], word_cords[j][x1], word_cords[j][y0], word_cords[j][y1], &len_chars, width);

            // printf("len_chars = %zu\n", len_chars);
            for (size_t k = 0; k < len_chars; k++)
            {
                size_t *norm_char = normalize(matrix, char_coords[k][x0], char_coords[k][y0], char_coords[k][x1], char_coords[k][y1], width);

                // copy
                for (size_t m = 0; m < subarray_size; m++)
                    if (arr_index < nbchars)
                        array[arr_index][m] = norm_char[m];

                free(norm_char);
                arr_index++;
            }

            free_array_of_arrays(char_coords, len_chars);

            arr_index++; // skip a cell for whitespace between words
        }

        free_array_of_arrays(word_cords, len_arr_words);

        free_array_of_arrays(chars_dist, len_chars_dist);
    }

    free_array_of_arrays(line_coords, len_arr_lines);

    return array; // to be freed
}
