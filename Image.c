/*********************************************************************/
/* Image.c: Implements various operations for modifying Image struct */
/*********************************************************************/

/*** header files ***/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Image.h"

/*** function definitions ***/

/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y){

/*
    //get effective address
    unsigned char *tempR;
    tempR = (image -> R);

    assert(tempR == (image -> R));
    tempR += (x + y*(image -> W));
*/
    return *((image -> R) + (x + y*(image -> W)));
}

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y){
/*
    //get effective address
    unsigned char *tempG;
    tempG = (image -> G);

    assert(tempG == (image -> G));
    tempG += (x + y*(image -> W));
*/
    return *((image -> G)  + (x + y*(image -> W)));
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y){
/*
    //get effective address
    unsigned char *tempB;
    tempB = (image -> B);

    assert(tempB == (image -> B));
    tempB += (x + y*(image -> W));
*/
    return *((image -> B)  + (x + y*(image -> W)));
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r){
/*	
    //get effective address
    unsigned char *tempR;
    tempR = (image -> R);

    assert(tempR == (image -> R));
    tempR += (x + y*(image -> W));
*/
    *((image -> R) + (x + y*(image -> W))) = r;
}

/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g){
/*	
    //get effective address
    unsigned char *tempG;
    tempG = (image -> G);

    assert(tempG == (image -> G));
    tempG += (x + y*(image -> W));
*/
    *((image -> G) + (x + y*(image -> W))) = g;
}

/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b){
/*	
    //get effective address
    unsigned char *tempB;
    tempB = (image -> B);

    assert(tempB == (image -> B));
    tempB += (x + y*(image -> W));
*/
    *((image -> B) + (x + y*(image -> W))) = b;
}

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
    IMAGE *i;
    i = (IMAGE *) malloc(sizeof(IMAGE));
    if(i == NULL){
        perror("Allocation failed.");
        exit(10);
    }
    i -> W = Width;
    i -> H = Height;
    i -> R =  (unsigned char *) malloc(sizeof(unsigned char) * Width * Height);
    i -> G =  (unsigned char *) malloc(sizeof(unsigned char) * Width * Height);
    i -> B =  (unsigned char *) malloc(sizeof(unsigned char) * Width * Height);
    return i;
}

/* Free the memory for the R/G/B values and IMAGE structure */
void DeleteImage(IMAGE *image){ 
   assert(image);
   free(image -> R);
   free(image -> G);
   free(image -> B);
   free(image);
}

/* Return the image's width in pixels */
unsigned int ImageWidth(const IMAGE *image){
    return image -> W;
}

/* Return the image's height in pixels */
unsigned int ImageHeight(const IMAGE *image){
    return image -> H;
}
