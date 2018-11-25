/******************************************/
/* DIPs.h: Header file for DIP Operations */
/******************************************/
#ifndef DIPS_H
#define DIPS_H

/*** header files ****/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "Constants.h"
#include "Image.h"

/*** function declarations ***/

/* edge detection */
IMAGE *Edge(IMAGE *image);

/* change color image to black & white */
IMAGE *BlackNWhite(IMAGE *image);

/* shuffle the image */
IMAGE *Shuffle(IMAGE *image);

#endif /* DIPS_H */

/* EOF DIPs. h */
