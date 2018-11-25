/*********************************************/
/*  Advanced.h: Header file for advanced DIP */
/*              functions in PhotoLab_v2     */
/*********************************************/

#ifndef ADVANCED_H
#define ADVANCED_H

/*** header files ***/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "Constants.h"
#include "Image.h"

/*** function definitions ***/

/* Set brightntess of an image */
IMAGE *Brightness(IMAGE *image, int brightness);

/* Horizontally Mirror an image */
IMAGE *HMirror(IMAGE *image);

/* Adjust the hue of an image */
IMAGE *HueRotate(IMAGE *image, float angle);

/* Rotate the image based on input */
IMAGE *Rotate(IMAGE *image, int option);

/* Resize the image by a certain percentage */
IMAGE *Resize(IMAGE *image, int percentage);

/* Adjust the color saturation of an image */
IMAGE *Saturate(IMAGE *image, float percent);

#endif /* ADVANCED_H */

/* EOF Advanced.h */
