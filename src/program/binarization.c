/*
** File binarization.c for TechForceOCR
** Made by Victor on 31.10.2020
*/

#include "../../include/binarization.h"
#include "../../include/sdl_tools.h"
#include "../../include/matrix_tools.h"
#include "SDL/SDL_image.h"

#include <stdlib.h>
#include <err.h>

/* binarize() */

int *binarize(SDL_Surface *image)
{
    size_t height = image->h;
    size_t width = image->w;

    int *binary_matrix = NULL;
    binary_matrix = init_matrix(height, width);

    Uint8 r, g, b;

    if (binary_matrix != NULL)
    {
        for (size_t i = 0; i < height; ++i)
        {
            for (size_t j = 0; j < width; ++j)
            {
                Uint32 pixel = get_pixel(image, j, i);

                SDL_GetRGB(pixel, image->format, &r, &g, &b);

                if (r + g + b == 0)
                    binary_matrix[i * width + j] = 1;
            }
        }

        return binary_matrix;
    }

    errx(1, "binarize : could not fill the matrix");
}