#ifndef FINALROTATE_H_
#define FINALROTATE_H_
#include "SDL/SDL.h"

double convert_to_rad(double angle_in_deg);

SDL_Surface *Rotate(SDL_Surface *image, double angle);

int is_white_pixel(SDL_Surface *image, int h, int w);

int compute_raycast_sum(SDL_Surface *image, int h, double angle);

double compute_variance(SDL_Surface *image, double angle);

double find_skew_angle(SDL_Surface *image,double lower_bound, double upper_bound, double precision);

SDL_Surface *image_deskew(SDL_Surface *image);
#endif