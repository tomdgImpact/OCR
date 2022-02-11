/*
** File binarization.h for TechForceOCR
** Made by Victor on 31.10.2020
*/

#ifndef BINARIZATION_H_
#define BINARIZATION_H_

/*
** SUMMARY
**
** This file contains functions that are needed for the entire process of
** segmentation as the functions defined here process a black an white image
** into a matrix containing only zeros and ones.
**
** binarize()           - returns the binarized matrix from the image       [OK]
*/

#include "SDL/SDL_image.h"

/*
** @brief takes an image as paramater, initializes an empty matrix (matrix
** filled with zeros) and fills according to pixels on the image. A white pixel
** is represented by a 0 and a black pixel is represented by a 1. Note that the
** matrix is not a 2-dimentional matrix, the row order is used instead to
** improve the initialization for large images. Note that the returned matrix
** will have to be freed at the end of the execution.
**
** @param image : the SDL_Surface got from the load_image() function
**
** @return int *
*/

int *binarize(SDL_Surface *image);

#endif