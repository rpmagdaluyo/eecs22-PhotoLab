/****************************************/
/* FileIO.h: header file for I/O module */
/****************************************/

#ifndef FILE_IO_H
#define FILE_IO_H

/*** header files ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Constants.h"
#include "Image.h"

/*** function declarations ***/

/* load image from a file */
IMAGE *LoadImage(const char *fname);

/* save a processed image */
int SaveImage(const char *fname, const IMAGE *image);

#endif

/* EOF FileIO.h */
