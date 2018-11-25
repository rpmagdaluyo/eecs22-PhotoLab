/**********************************/
/* Test.h: Header file for Test.c */ 
/**********************************/

#ifndef TEST_H
#define TEST_H

/* Test all DIPs */
int AutoTest(const char *image);

/* test parameters used in AutoTest() */

/* parameter used for Hue */
#define ANGLE -1.5

/* parameter used for Saturate*/
#define SATURATE_PERCENTAGE 90

/* parameters used for resize */
#define BIG_RESIZE_PERCENTAGE 170
#define SMALL_RESIZE_PERCENTAGE 60

/* brightness */
#define BRIGHTNESS 200

/* Rotate */
#define ROTATER 3
#define HFLIP 1

#endif /* TEST_H */

/* EOF Test.h */
