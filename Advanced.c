/*******************************************************/
/* Advanced.c: Advanced DIP operations for PhotoLab_v2 */ 
/*******************************************************/

/*** header files ***/
#include "Advanced.h"

/*** function definitions ***/

/* Adjust the brightness of an image */
IMAGE *Brightness(IMAGE *image, int brightness){	
    assert(image);
    
    int Width  = ImageWidth(image);
    int Height = ImageHeight(image);

    for (int i=0; i<Width; i++){
	for (int j=0; j<Height; j++){
            if (GetPixelR(image, i, j) + brightness > 255){
                SetPixelR(image, i, j, 255);
		}else if(GetPixelR(image, i, j) + brightness < 0){
		    SetPixelR(image, i, j, 0);
		}else{
                    SetPixelR(image, i, j, GetPixelR(image, i, j) + brightness);
		}

		if (GetPixelG(image, i, j) + brightness > 255){
                    SetPixelG(image, i, j, 255);
		}else if(GetPixelG(image, i, j) + brightness < 0){
		    SetPixelG(image, i, j, 0);
		}else{
		    SetPixelG(image, i, j, GetPixelG(image, i, j) + brightness);
		}

		if (GetPixelB(image, i, j) + brightness > 255){
		    SetPixelB(image, i, j, 255);
		}else if(GetPixelB(image, i, j) + brightness < 0){
		    SetPixelB(image, i, j, 0);
		}else{
		    SetPixelB(image, i, j, GetPixelB(image, i, j) + brightness);
		}
	}
    }
    
    printf("Image's brightness successfully adjusted by %d.\n", brightness);

    return image;
} /* end of Brightness */

/* Mirror an image horizontally */
IMAGE *HMirror(IMAGE *image){
    assert(image); 

    //variable definitions
    int Width  = ImageWidth(image);
    int Height = ImageHeight(image);
    int x, y;

    for (y = 0; y < Height; y++) {
        for (x = 0; x < Width / 2; x++) {
            SetPixelR(image, Width-1-x, y, GetPixelR(image, x, y));
            SetPixelG(image, Width-1-x, y, GetPixelG(image, x, y));
            SetPixelB(image, Width-1-x, y, GetPixelB(image, x, y));
        }
    }

    printf("Image was mirrored successfully\n");

    return image;
} /* end of HMirror */

void matrix_3_3multiplyVector_3(float vector[3], const float matrix[3][3])
{
	/* Memory for result */
	float result[3] = {0, 0, 0};

	/* Perform multiplication */
	result[0] = matrix[0][0]*vector[0] + matrix[0][1]*vector[1] + matrix[0][2]*vector[2];
	result[1] = matrix[1][0]*vector[0] + matrix[1][1]*vector[1] + matrix[1][2]*vector[2];
	result[2] = matrix[2][0]*vector[0] + matrix[2][1]*vector[1] + matrix[2][2]*vector[2];

	/* Copy result into other stack's memory */
	vector[0] = result[0];
	vector[1] = result[1];
	vector[2] = result[2];
}

/* Rotate image hue based on input angle */
IMAGE *HueRotate(IMAGE *image, float angle)
{
        assert(image);

	/* Matrix to transform normalized
	// RGB color vector from the RGB
	// color space to the YIQ color space */
	static const float RGBtoYIQMatrix[3][3] = {{0.299,  0.587,  0.114},
                                                   {0.596, -0.274, -0.321},							        {0.211, -0.523,  0.311}};

	/* Matrix to transform normalized
	// YIQ color vector from the YIQ
	// color space to the RGB color space */
	static const float YIQtoRGBMatrix[3][3] = {{1.000,  0.956,  0.621},
						   {1.000, -0.272, -0.647},								{1.000, -1.107,  1.705}};

	const float cs = cos(angle), ss = sin(angle);

	/* Matrix to perform a hue
	// rotation on a normalized
	// YIQ color vector*/
	const float XYPlaneVectorRotateMatrix[3][3] = {{1.000, 0.000, 0.000},								    {0.000,    cs,   -ss},
						       {0.000,    ss,    cs}};

	/* Image variables */
	float temp[3];
        int Width  = ImageWidth(image);
        int Height = ImageHeight(image);

	for(unsigned int i = 0; i < Width; i++)
	{
	    for(unsigned int j = 0; j < Height; j++)
	    {
		/* Create a normalized RGB color
		// vector from the current pixel
		// in the image */
		temp[0] = (float)GetPixelR(image, i, j)/255;
		temp[1] = (float)GetPixelG(image, i, j)/255;
		temp[2] = (float)GetPixelB(image, i, j)/255;

		/* Transform the RGB vector
		// to a YIQ vector */
		matrix_3_3multiplyVector_3(temp, RGBtoYIQMatrix);

		/* Perform the DIP */
		matrix_3_3multiplyVector_3(temp, XYPlaneVectorRotateMatrix);

		/* Transform back to RGB */
		matrix_3_3multiplyVector_3(temp, YIQtoRGBMatrix);

		/* Denormalize and store back into the image */
		temp[0] = temp[0] * 255;
		temp[0] = temp[0] < 0 ? 0 : temp[0];
		temp[0] = temp[0] > 255 ? 255 : temp[0];
		temp[1] = temp[1] * 255;
		temp[1] = temp[1] < 0 ? 0 : temp[1];
		temp[1] = temp[1] > 255 ? 255 : temp[1];
		temp[2] = temp[2] * 255;
		temp[2] = temp[2] < 0 ? 0 : temp[2];
		temp[2] = temp[2] > 255 ? 255 : temp[2];

                SetPixelR(image, i, j, (unsigned char)temp[0]); 
                SetPixelG(image, i, j, (unsigned char)temp[1]); 
                SetPixelB(image, i, j, (unsigned char)temp[2]); 
	    }
    }

    printf("The image's hue has been successfully rotated by %.2f rad.\n", angle);

    return image;
} /* end of HueRotate */

/* Rotate the image based on input */
IMAGE *Rotate(IMAGE *image, int option){
    assert(image);

    //variable declarations
    IMAGE *newImage = NULL;
    int Width, Height;
    
    switch(option){
        //horizontal flip
        case 1:
            newImage = CreateImage(ImageWidth(image), ImageHeight(image));
            Width  = ImageWidth(newImage);
            Height = ImageHeight(newImage);

            for(int y=0; y<Height; y++)
                for(int x=0; x<Width; x++){
                    SetPixelR(newImage, Width-1-x, y, GetPixelR(image, x, y));
                    SetPixelG(newImage, Width-1-x, y, GetPixelG(image, x, y));
                    SetPixelB(newImage, Width-1-x, y, GetPixelB(image, x, y));
                } 

            break;

        //vertical flip
        case 2:
            newImage = CreateImage(ImageWidth(image), ImageHeight(image));
            Width  = ImageWidth(newImage);
            Height = ImageHeight(newImage);

            for(int y=0; y<Height; y++)
                for(int x=0; x<Width; x++){
                    SetPixelR(newImage, x, Height-1-y, GetPixelR(image, x, y));
                    SetPixelG(newImage, x, Height-1-y, GetPixelG(image, x, y));
                    SetPixelB(newImage, x, Height-1-y, GetPixelB(image, x, y));
                } 

            break;
        
        //rotate right
        case 3:
            newImage = CreateImage(ImageHeight(image), ImageWidth(image));
            Width  = ImageWidth(newImage);
            Height = ImageHeight(newImage);

            for(int y=0; y<Height; y++)
                for(int x=0; x<Width; x++){
                    SetPixelR(newImage, x, y, GetPixelR(image, y, x));
                    SetPixelG(newImage, x, y, GetPixelG(image, y, x));
                    SetPixelB(newImage, x, y, GetPixelB(image, y, x));
                } 

            break;
        
        //rotate left
        case 4:
            newImage = CreateImage(ImageHeight(image), ImageWidth(image));
            Width  = ImageWidth(newImage);
            Height = ImageHeight(newImage);

            for(int y=0; y<Height; y++)
                for(int x=0; x<Width; x++){
                    SetPixelR(newImage, Width-1-x, y, GetPixelR(image, y, x));
                    SetPixelG(newImage, Width-1-x, y, GetPixelG(image, y, x));
                    SetPixelB(newImage, Width-1-x, y, GetPixelB(image, y, x));
                } 

            break;
        
        //no flip
        default:
            newImage = image;
    }

    printf("Image was successfully rotated.\n");

    DeleteImage(image);

    return newImage;
} /* end of Rotate */

/* Resize the image by a certain percentage */
IMAGE *Resize(IMAGE *image, int percentage){
    assert(image);

    //variable declarations
    int Width = ImageWidth(image);
    int Height = ImageHeight(image);
    int newWidth  = ImageWidth(image)*(percentage/100.00);
    int newHeight = ImageHeight(image)*(percentage/100.00);
//    int range = (int) ((100.0/percentage) * (100.0/percentage));
    int range;
    int intensityR, intensityG, intensityB;
    int countR, countG, countB;
    int averageR, averageG, averageB;                       //saved as int since will be floored later anyway
    IMAGE *newImage = CreateImage(newWidth, newHeight);

    if(percentage < 100)  //shrinking
    {
        range = (int)(100.0/percentage);

        for(int y=0; y<newHeight; y++){
            for(int x=0; x<newWidth; x++){
                //reset intensity values
                intensityR = 0;
                intensityG = 0;
                intensityB = 0;

                //reset averages
                averageR = 0;
                averageG = 0;
                averageB = 0;

                //reset counters
                countR = 0;
                countG = 0;
                countB = 0;
 
                 for(int j=0; j<range; j++){
                     for(int i=0; i<range; i++){

                         //increment total intensity of each channel
                         intensityR += GetPixelR(image, ((x*100)/percentage)+i, ((y*100)/percentage)+j);
                         intensityG += GetPixelG(image, ((x*100)/percentage)+i, ((y*100)/percentage)+j);
                         intensityB += GetPixelB(image, ((x*100)/percentage)+i, ((y*100)/percentage)+j);
    
                         //increment counters
                         countR++;
                         countG++;
                         countB++;
                     }     
                 }
       
                 //set pixels in new image
                 averageR = intensityR/countR;         
                 SetPixelR(newImage, x, y, (unsigned char)averageR);
                 
                 averageG = intensityG/countG;          
                 SetPixelG(newImage, x, y, (unsigned char)averageG);

                 averageB = intensityB/countB;          
                 SetPixelB(newImage, x, y, (unsigned char)averageB);          
            }
        }     
    }
    else if(percentage > 100)  //enlarging
    {
        range = (int)((percentage+99)/100);

        for(int y=0; y<Height; y++){
            for(int x=0; x<Width; x++){ 
                 for(int j=0; j<range; j++){
                     for(int i=0; i<range; i++){
                         SetPixelR(newImage, ((x*percentage)/100)+i, ((y*percentage)/100)+j, (unsigned char)GetPixelR(image,x,y));
                         SetPixelG(newImage, ((x*percentage)/100)+i, ((y*percentage)/100)+j, (unsigned char)GetPixelG(image,x,y));
                         SetPixelB(newImage, ((x*percentage)/100)+i, ((y*percentage)/100)+j, (unsigned char)GetPixelB(image,x,y));
                     }     
                 }
            }
        }     
    }
    else{
        return image;
    }


    printf("Image was successfully resized by %d%%.\n", percentage);

    DeleteImage(image);

    return newImage;
} /* end of Resize */

IMAGE *Saturate(IMAGE *image, float percent){
    assert(image);

    //variable declarations  
    int Width = ImageWidth(image);
    int Height = ImageHeight(image);
    int tempR, tempG, tempB;

    for(int y=0; y<Height; y++){
        for(int x=0; x<Width; x++){ 
            //get grayscale color
            tempR = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y))/3;
            tempG = tempR;
            tempB = tempB;

            //find difference from original
            tempR = GetPixelR(image, x, y) - tempR;
            tempG = GetPixelG(image, x, y) - tempG;
            tempB = GetPixelB(image, x, y) - tempB;

            //modify saturation
            tempR = GetPixelR(image, x, y) + (int)(tempR * percent/100.0);
            tempG = GetPixelG(image, x, y) + (int)(tempG * percent/100.0);
            tempB = GetPixelB(image, x, y) + (int)(tempB * percent/100.0);

            //check for any negative values
            if(tempR < 0)
                tempR = 0;
            if(tempG < 0)
                tempG = 0;
            if(tempB < 0)
                tempB = 0;

            //check for any values > 255
            if(tempR > 255)
                tempR = 255;
            if(tempG > 255)
                tempG = 255;
            if(tempB > 255)
                tempB = 255;

            //modify values
            SetPixelR(image, x, y, (unsigned char)tempR);
            SetPixelG(image, x, y, (unsigned char)tempG);
            SetPixelB(image, x, y, (unsigned char)tempB);
        }
    }

    printf("Image saturation successfully modified to %.2f%%\n", percent);

    return image;
} /* end of Saturate */
/* EOF */
/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
