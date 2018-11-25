#########################################################
# Makefile: Makefile for Assignment #4 EECS22 Fall 2018 #
#########################################################

# variable definitions 
CC = gcc
DEBUG  = -g -DDEBUG
#MYDEBUG = -g -DDEBUG
#DEBUG = -O2
CFLAGS = -Wall -ansi -std=c99 -c
LFLAGS = -Wall -ansi -std=c99 -lm
AR     = ar rc
RANLIB = ranlib

#IMAGES = bw.ppm edge.ppm shuffle.ppm brightness.ppm hmirror.ppm hue.ppm

IMAGES = bw.ppm \
         edge.ppm \
         shuffle.ppm \
	 brightness.ppm \
         hmirror.ppm \
         hue.ppm \
         rotate.ppm \
         hflip.ppm \
         saturate.ppm \
         smallresize.ppm \
         bigresize.ppm \

# convenience targets
all: PhotoLab PhotoLabTest

clean:
	rm -f *.o *.a *.jpg $(IMAGES)
	rm -f PhotoLab
	rm -f PhotoLabTest

### generate object files ###    
    
Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c -o Image.o

Test.o: Test.c Test.h
	$(CC) $(CFLAGS) Test.c -o Test.o
    
FileIO.o: FileIO.c FileIO.h Image.o Constants.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

Advanced.o: Advanced.c Advanced.h Constants.h
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o

PhotoLab.o: PhotoLab.c Test.h Image.h Constants.h FileIO.h DIPs.h Advanced.h
	$(CC) $(CFLAGS) PhotoLab.c -o PhotoLab.o

PhotoLabTest.o: PhotoLab.c Test.h Image.h Constants.h FileIO.h DIPs.h Advanced.h
	$(CC) $(CFLAGS) $(DEBUG) PhotoLab.c -o PhotoLabTest.o

### generate library files ###    
    
libFilter.a: FileIO.o DIPs.o Advanced.o
	ar rcs libFilter.a DIPs.o Advanced.o

### generate executables ###    
    
PhotoLab: Image.o Test.o FileIO.o PhotoLab.o libFilter.a
	$(CC) $(LFLAGS) Image.o Test.o FileIO.o PhotoLab.o -lFilter -lm -L. -o PhotoLab

PhotoLabTest: Image.o Test.o FileIO.o  PhotoLabTest.o libFilter.a
	$(CC) $(LFLAGS) Image.o Test.o FileIO.o PhotoLabTest.o -lFilter -lm -L. -o PhotoLabTest 



