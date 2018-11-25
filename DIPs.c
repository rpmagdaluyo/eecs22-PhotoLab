/*******************************************/
/* DIPs.c: DIP Operations from PhotoLab v1 */
/*******************************************/

/*** header files ***/

#include "DIPs.h"

/*** function definitions ***/

/* converts values of RGB arrays to produce grayscale image */
IMAGE *BlackNWhite(IMAGE *image){    
    assert(image);

    //variable declarations
    int temp   = 0;
    int Width  = ImageWidth(image);
    int Height = ImageHeight(image);

    for(int y=0; y<Height; y++){
        for(int x=0; x<Width; x++){ 
            temp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y))/3;
            SetPixelR(image, x, y, (unsigned char)temp);  
            SetPixelG(image, x, y, (unsigned char)temp);
            SetPixelB(image, x, y, (unsigned char)temp);           
        }
    }

    printf("Image was successfully converted to black and white.\n");

    return image;
} /* end of BlackNWhite */

/* Add edge to the image*/
IMAGE *Edge(IMAGE *image){    
    assert(image);
    
    //variable declarations
    int             x, y, m, n, a, b;
    int             Height = ImageHeight(image);
    int             Width  = ImageWidth(image);

    IMAGE *tempImage = CreateImage(Width, Height);

    //copy values into temp arrays
    for (y = 0; y < Height; y++){
        for (x = 0; x < Width; x++) {
            SetPixelR(tempImage, x, y, GetPixelR(image, x, y));
            SetPixelG(tempImage, x, y, GetPixelG(image, x, y));
            SetPixelB(tempImage, x, y, GetPixelB(image, x, y));
        }
    }

    int sumR = 0;   /* sum of the intensity differences with neighbors */
    int sumG = 0;
    int sumB = 0;

    for (y = 1; y < Height - 1; y++){
        for (x = 1; x < Width - 1; x++){
            for (n = -1; n <= 1; n++){
                for (m = -1; m <= 1; m++) {
                    a = (x + m >= Width) ? Width - 1 : (x + m < 0) ? 0 : x + m;
                    b = (y + n >= Height) ? Height - 1 : (y + n < 0) ? 0 : y + n;
                    sumR += (GetPixelR(tempImage, x, y) - GetPixelR(tempImage, a, b));
                    sumG += (GetPixelG(tempImage, x, y) - GetPixelG(tempImage, a, b));
                    sumB += (GetPixelB(tempImage, x, y) - GetPixelB(tempImage, a, b));
                }
            }  

            SetPixelR(image, x, y, (sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < 0) ? 0: sumR); 
            SetPixelG(image, x, y, (sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < 0) ? 0: sumG); 
            SetPixelB(image, x, y, (sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < 0) ? 0: sumB); 
            sumR = sumG = sumB = 0;
        }
    }

    /* set all four borders to 0 */
    for (y = 0; y < Height; y++) {
        SetPixelR(image, 0, y, 0);
        SetPixelG(image, 0, y, 0);
        SetPixelB(image, 0, y, 0);
        SetPixelR(image, Width-1, y, 0);
        SetPixelG(image, Width-1, y, 0);
        SetPixelB(image, Width-1, y, 0);
    }
    for (x = 0; x < Width; x++) {
        SetPixelR(image, x, 0, 0);
        SetPixelG(image, x, 0, 0);
        SetPixelB(image, x, 0, 0);
        SetPixelR(image, x, Height-1, 0); 
        SetPixelG(image, x, Height-1, 0); 
        SetPixelB(image, x, Height-1, 0); 
    }

    printf("Image was successfully converted to show edges.\n");

    DeleteImage(tempImage);

    return image;
} /* end of Edge */

/* Shuffle the image */
IMAGE *Shuffle(IMAGE *image){
    assert(image);

    //variable declarations
    int Width = ImageWidth(image);
    int Height = ImageHeight(image);    
    int block_cnt = SHUFF_HEIGHT_DIV * SHUFF_WIDTH_DIV;
    int block_width = Width/SHUFF_WIDTH_DIV;
    int block_height = Height/SHUFF_HEIGHT_DIV;
    int *block = malloc(sizeof(int) * SHUFF_WIDTH_DIV * SHUFF_HEIGHT_DIV);
    int i, j;


    srand(time(NULL));
    /* Initialize block markers to not done (-1) */
    for (i = 0; i < SHUFF_WIDTH_DIV; i++) {
        for (j = 0; j< SHUFF_HEIGHT_DIV; j++) {
            *(block + i + j*SHUFF_WIDTH_DIV) = -1;
        }
    }

    while (block_cnt > 0) {
        /* Generate a random pair of blocks */
        int dest_height = rand() % SHUFF_HEIGHT_DIV;
        int dest_width = rand() % SHUFF_WIDTH_DIV;
        int src_height = rand() % SHUFF_HEIGHT_DIV;
        int src_width = rand() % SHUFF_WIDTH_DIV;

        /* Check if these blocks are already swaped, if not swap blocks */
        if ((*(block + dest_width + dest_height*SHUFF_WIDTH_DIV) == -1) && (*(block + src_width + src_height*SHUFF_WIDTH_DIV) == -1))
        {
            /* Swap blocks */
            for (i = 0; i < block_height; i++) {
                /* Init src and dest height offset */
                int h_dest = ((dest_height * block_height) + i) % Height;
                int h_src  = ((src_height * block_height) + i) % Height;
                for (j = 0; j < block_width; j++) {
                    int temp;
                    /* Init src and dest width offset */
                    int w_src  = ((src_width * block_width) + j) % Width;
                    int w_dest = ((dest_width * block_width) + j) % Width;

                    temp = GetPixelR(image, w_dest, h_dest);
                    SetPixelR(image, w_dest, h_dest, GetPixelR(image, w_src, h_src));
                    SetPixelR(image, w_src, h_src, temp);

                    temp = GetPixelG(image, w_dest, h_dest);
                    SetPixelG(image, w_dest, h_dest, GetPixelG(image, w_src, h_src));
                    SetPixelG(image, w_src, h_src, temp);

                    temp = GetPixelB(image, w_dest, h_dest);
                    SetPixelB(image, w_dest, h_dest, GetPixelB(image, w_src, h_src));
                    SetPixelB(image, w_src, h_src, temp);
                }
            }
            /* Set marker as done */
            *(block + dest_width + dest_height*SHUFF_WIDTH_DIV) = 1;
            *(block + src_width + src_height*SHUFF_WIDTH_DIV) = 1;
            /* Decrease block count */
            block_cnt -= 2; /* Two blocks are swapped */
        }

    }

    printf("The image has been successfully shuffled!\n");

    free(block);

    return image;
} /* end of shuffle */

/* EOF */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
