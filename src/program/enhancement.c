#include "SDL/SDL.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/pixels.h"
#include "../../include/enhancement.h"

SDL_Surface *Enhanc (SDL_Surface *image)
{
    int hist[256] = { 0 };
    int rows = image -> w;
    int cols = image -> h;
    int Mat[rows * cols][3];
    memset( Mat, 0, (rows*cols)*3*sizeof(int) );
    Uint8 r, g, b;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            Uint32 pixel = get_pixel(image, i, j);
            SDL_GetRGB(pixel, image -> format, &r, &g, &b);
            Uint8 luminosity = 0.21 * r + 0.72 * g + 0.07 * b;
            hist[(int)luminosity]++;
            Mat[i * cols + j][0] = i;
            Mat[i * cols + j][1] = j;
            Mat[i * cols + j][2] = luminosity;
        }
    }

    float curr = 0;
    int size = rows * cols;

    for (int i = 0; i < 256; ++i)
    {
        curr += hist[i];
        hist[i] = round(curr * 255 / size);
    }

    for (int i = 0; i < 256; ++i)
    {
        for (int j = 0; j < rows; ++j)
        {
            for (int k = 0; k < cols; ++k)
            {
                if (Mat[j * cols + k][2] == i)
                    Mat[j * cols + k][2] = hist[i];
            }
        }
    }



    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            r = Mat[i * cols + j][2];
            g = Mat[i * cols + j][2];
            b = Mat[i * cols + j][2];
            Uint32 new_pixel = SDL_MapRGB (image -> format, r, g, b);
            put_pixel (image, i, j, new_pixel);
        }
    }


    return image;
}
