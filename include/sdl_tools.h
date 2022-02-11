/*
** File source/sdl_tools.h for TechForceOCR
**
** Made by Victor on 16.10.2020
** Last update : 16.10.2020 by Victor
*/

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include "SDL/SDL.h"
/*
** Function init_sdl() to initialize the default subsystems and the video
** subsystem. Has to be called before any other library usage.
**
** Latest change : implementation (by Victor 15.10.2020)
*/

void init_sdl();

/*
** Function quit_sdl() shuts down all subsystems initialized. Has to be called
** at the end of the execution.
**
** Latest change : implementation (by Victor 15.10.2020)
*/

void quit_sdl();

/*
** Function pause_exec() waits for <ESC> key to be pressed. Use this function
** to prevent a window from closing right after being summoned.
**
** Latest change : implementation (by Victor 16.10.2020)
*/

void pause_exec();

void wait_for_keypressed();

/*
** @brief loads the image from the path into memory for further processing. This
** requires the SDL video part to be initialized using init_sdl() function.
**
** @param path : the path to the image
**
** @return SDL_Surface *
*/

SDL_Surface *load_image(char *path);

SDL_Surface* display_image(SDL_Surface *img);
/*
** @brief gets the RGB values of a pixel in a BMP image given as parameter.
** Pixel is a position (x,y) such that x is the column and y is the line. This
** function requires the initialization of the SDL using init_sdl().
**
** @param image : the SDL_Surface got from load_image()
** @param column : the x position of the pixel
** @param line : the y position of the pixel
**
** @return Uint32
*/

Uint32 get_pixel(SDL_Surface *image, int x, int y);

void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void update_surface(SDL_Surface* screen, SDL_Surface* image);
#endif
