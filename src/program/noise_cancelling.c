#include "SDL/SDL.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/sdl_tools.h"
#include "../../include/noise_cancelling.h"

SDL_Surface *Noise (SDL_Surface *image)
{
    int arr[9] = { 0 };
    int rows = image -> w;
    int cols = image -> h;
    int Mat[rows * cols];
    memset( Mat, 0, (rows*cols)*sizeof(int) );
    Uint8 r, g, b;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            Uint32 pixel = get_pixel(image, i, j);
            SDL_GetRGB(pixel, image -> format, &r, &g, &b);
            Uint8 luminosity = 0.21 * r + 0.72 * g + 0.07 * b;
            Mat[i * cols + j]= luminosity;
        }
    }
    for (int i = 1; i < rows - 1; ++i)
    {
        for (int j = 1; j < cols - 1; j++)
        {
            arr[0] = Mat[i * cols + j];
            arr[1] = Mat[(i-1 )* cols + j];
            arr[2] = Mat[(i+1) * cols + j];
            arr[3] = Mat[i * cols + (j-1)];
            arr[4] = Mat[i * cols + (j+1)];
            arr[5] = Mat[(i - 1) * cols + (j+1)];
            arr[6] = Mat[(i+1) * cols + (j-1)];
            arr[7] = Mat[(i+1) * cols + (j+1)];
            arr[8] = Mat[(i-1) * cols + (j-1)];

            int length = sizeof(arr)/sizeof(int);
            int temp = 0;
            for (int k = 0; k < length; k++)
            {
                for(int l = k; l < length; l++)
                {
                    if (arr[k] > arr[l])
                    {
                        temp = arr[l];
                        arr[l] = arr[k];
                        arr[k] = temp;
                    }
                }
            }
        }
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            r = Mat[i * cols + j];
            g = Mat[i * cols + j];
            b = Mat[i * cols + j];
            Uint32 new_pixel = SDL_MapRGB (image -> format, r, g, b);
            put_pixel (image, i, j, new_pixel);
        }
    }
    return image;
}
