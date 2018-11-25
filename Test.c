/************************************************************/
/* Test.c: Implements all functions to test for PhotoLab v3 */
/************************************************************/

/*** header files ***/

#include <stdio.h>

#include "Test.h"
#include "Image.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"

/*** function definitions ***/

int AutoTest(const char *fname) {
    int result;
 
    //test BlackNWhite
    IMAGE *image = NULL;
    image = LoadImage(fname);
    if (! image) return 11;
    image = BlackNWhite(image);
    if (! image) return 12;
    result = SaveImage("bw", image);
    if (result) return result;
#ifdef DEBUG
    printf("Black and White tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    //test Edge
    image = LoadImage(fname);
    if (! image) return 13;
    image = Edge(image);
    if (! image) return 14;
    result = SaveImage("edge", image);
    if (result) return result;
#ifdef DEBUG
    printf("Edge Detection tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    //test shuffle
    image = LoadImage(fname);
    if (! image) return 15;
    image = Shuffle(image);
    if (! image) return 16;
    result = SaveImage("shuffle", image);
    if (result) return result;
#ifdef DEBUG
    printf("Shuffle tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    //test Brightness
    image = LoadImage(fname);
    if (! image) return 17;
    image = Brightness(image,BRIGHTNESS);
    if (! image) return 18;
    result = SaveImage("brightness", image);
    if (result) return result;
#ifdef DEBUG
    printf("Brightness tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    //test HMirror
    image = LoadImage(fname);
    if (! image) return 19;
    image = HMirror(image);
    if (! image) return 20;
    result = SaveImage("hmirror", image);
    if (result) return result;
#ifdef DEBUG
    printf("HMirror tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    //test HueRotate
    image = LoadImage(fname);
    if (! image) return 21;
    image = HueRotate(image,ANGLE);
    if (! image) return 22;
    result = SaveImage("hue", image);
    if (result) return result;
#ifdef DEBUG
    printf("HueRotate tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    //test Rotate
    image = LoadImage(fname);
    if (! image) return 23;
    image = Rotate(image,ROTATER);
    if (! image) return 24;
    result = SaveImage("rotate", image);
    if (result) return result;
#ifdef DEBUG
    printf("RotateRight tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 25;
    image = Rotate(image,HFLIP);
    if (! image) return 26;
    result = SaveImage("hflip", image);
    if (result) return result;
#ifdef DEBUG
    printf("HorizontalFlip tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    //test Resize
    image = LoadImage(fname);
    if (! image) return 23;
    image = Resize(image, SMALL_RESIZE_PERCENTAGE);
    if (! image) return 24;
    result = SaveImage("smallresize", image);
    if (result) return result;
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 25;
    image = Resize(image, BIG_RESIZE_PERCENTAGE);
    if (! image) return 26;
    result = SaveImage("bigresize", image);
    if (result) return result;
#ifdef DEBUG
    printf("Resize tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    //test Saturate
    image = LoadImage(fname);
    if (! image) return 27;
    image = Saturate(image, SATURATE_PERCENTAGE);
    if (! image) return 28;
    result = SaveImage("saturate", image);
    if (result) return result;
#ifdef DEBUG
    printf("90 Percent Saturation tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    return 0; /* success! */
}
