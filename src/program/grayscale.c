/*
** File src/display/grayscale.c for TechForceOCR
** Color removal file that handle grayscale and black and white images
** Made by Tom 07.10.2020
*/
# include "SDL/SDL.h"
# include "../../include/sdl_tools.h"
/*
** Modify image given as parameter into a grayscale image.
** Implementation by Tom 07.10.2020
*/

SDL_Surface *Grayscale (SDL_Surface *image)
{
    int height = image -> h;
    int width = image -> w;
    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            Uint32 pixel = get_pixel (image, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image -> format, &r, &g, &b);
            Uint8 average = 0.3 * r + 0.59 * g + 0.11 * b;
            r = average;
            g = average;
            b = average;
            Uint32 new_pixel = SDL_MapRGB (image -> format, r, g, b);
            put_pixel (image, i, j, new_pixel);
        }
    }
    return image;
}

/*
** Modify image given as parameter into a black and white image.
** *SDL_image -> input surface representing the current image
** *SDL_screen -> pointer to the screen surface
** When set to 255, the pixel will be blank and black if 0.
** lastest change : Prototype and implementation (By Tom 08.10.2020)
*/

SDL_Surface *Black_white(SDL_Surface *image)
{
    int height = image -> h;
    int width = image -> w;
    Uint32 pixel = 0;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 averagelum;
    for (int i = 0; i < width ; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            pixel = get_pixel(image, i, j);
            SDL_GetRGB(pixel, image -> format, &r, &g, &b);
            averagelum = (r + g +b) / 3;
            if (averagelum > 127)
            {
                r = 255;
                g = 255;
                b = 255;
            }
            else
            {
                r = 0;
                g = 0;
                b = 0;
            }
            pixel = SDL_MapRGB(image->format, r, g, b);
            put_pixel(image, i, j, pixel);
        }
    }
    return image;
}
/*
** END OF FILE
*/
