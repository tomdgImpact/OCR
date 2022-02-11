#include "SDL/SDL.h"

#ifndef DISPLAY_H_
#define DISPLAY_H_
void init_sdl();

SDL_Surface* load_image(char *path);

SDL_Surface* display_image(SDL_Surface *img);

void wait_for_keypressed();

void pause_exec();

void update_surface(SDL_Surface* screen, SDL_Surface* image);

#endif
