/*
** Header for function that handle pixels manipulation.
** created by Tom 10.10.2020
*/
# include "SDL/SDL.h"
# ifndef PIXELS_H_
# define PIXELS_H_

Uint32 get_pixel(SDL_Surface *surface, int x, int y);

void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

# endif
