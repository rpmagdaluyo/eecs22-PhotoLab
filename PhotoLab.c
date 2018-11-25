/*********************************************************************/
/* PhotoLab.c: assignment 2 for EECS 22, Fall 2018                   */
/*                                                                   */
/* modifications: Mihnea Chirila                                     */
/* 09/27/17 RD	adjusted for lecture usage                           */
/* 10/1/18 MC	 adjusted for F18                          	     */
/*********************************************************************/
/* Enter your name, last name and UCInet ID below:
 *
 * *****************************
 * First Name : Richard 
 * Last Name  : Magdaluyo
 * UCInet ID  : 45993793
 *
 */


/*** header files ***/

#include "Constants.h"
#include "Test.h"
#include "Image.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"

int choice = 0;                   // used for menu choices
int brightness = 0;               // used for Brightness function
int rotateOption = 0;             // used for Rotate function
int resizePercent = 100;          // used for Resize function
float saturatePercent = 0;        // used for Saturate function
float angle = 0;                  // used for HueRotate function
char fileName[SLEN];              // file name 

/*** function declarations ***/

/* Print menu */
void PrintMenu();

/*** main program ***/

int main(void)
{
    //variable declarations
    IMAGE *myImage = NULL;
 
    #ifdef DEBUG
        strcpy(fileName, "HSSOE");
        AutoTest(fileName);
        return 0;
    #endif
  
    do{ 
    prog:
        PrintMenu();

        scanf("%d", &choice);
    
        if(choice == 1)
        {
            printf("Please enter a file name.\n");
            scanf("%s", fileName);
            myImage = LoadImage(fileName);
        }
        else if(choice > 1 && choice < 13) //check if valid image loaded before performing DIPs
        {
            if(myImage == NULL){
                printf("Sorry the image you are trying to access is unitializied. Please load a valid image.\n");
                goto prog;
            }
            else
            {
		if(choice == 2)
		{
		    printf("Please enter a file name.\n");
		    scanf("%s", fileName);
		    SaveImage(fileName, myImage);
		
		}
                else if(choice == 3)
                {
                    BlackNWhite(myImage);
                }
                else if(choice == 4)
                {
                    Edge(myImage);
                }
                else if(choice == 5)
                {
                    Shuffle(myImage);
                }
                else if(choice == 6)
                {
                    //Get a valid value for brightness adjustment before proceeding
                    do
                    {
                         printf("Please a number between -255 and 255.\n");
                         scanf("%d", &brightness);
                         
                         if(brightness >= -255 && brightness <= 255)
                            break;
                         else{
                            printf("Sorry that was an invalid input.\n");
                            continue;
                         }
                    }while(-255 > brightness || 255 < brightness);  

                    Brightness(myImage, brightness);
                }
                else if(choice == 7)
                {
                    HMirror(myImage);
                }
                else if(choice == 8)
                {
                    printf("Please a number with which you wish to rotate the hue of the image.\n");
                    scanf("%f", &angle);

                    HueRotate(myImage, angle);
                }
                else if(choice == 9)
                {
                    //Get a valid selection before operating on image
                    do{
                        printf("Please select an option\n");
                        printf("------------------------------\n");
                        printf("1: Horizontal flip\n");
                        printf("2: Vertical flip\n");
                        printf("3: Rotate right\n");
                        printf("4: Rotate left\n");

                        scanf("%d", &rotateOption);

                        if(rotateOption > 0 && rotateOption <= 4)
                            break;
                        else{
                            printf("Sorry that was an invalid input.\n");
                            continue;
                        } 

                    }while(0 >= rotateOption || 4 < rotateOption);

                    myImage = Rotate(myImage, rotateOption);
                }
                else if(choice == 10)
                {
                    //Get a valid resize percentage
                    do{
                       printf("Please input the resizing percentage (integer between 1 - 500).\n");
                       scanf("%d", &resizePercent);
                         
                       if(resizePercent >= 1 && resizePercent <= 500)
                          break;
                       else{
                          printf("Sorry that was an invalid input.\n");
                          continue;
                       }
                    }while(1 > resizePercent || 500 < resizePercent); 

                    myImage = Resize(myImage, resizePercent);
                }
                else if(choice == 11)
                {
                    //Get a valid value for saturation adjustment before proceeding
                    do
                    {
                         printf("Please a number between 0 and 100.\n");
                         scanf("%f", &saturatePercent);
                         
                         if(saturatePercent >= 0 && saturatePercent <= 100)
                            break;
                         else{
                            printf("Sorry that was an invalid input.\n");
                            continue;
                         }
                    }while(0 > saturatePercent || 100 < saturatePercent);  

                    Saturate(myImage, saturatePercent);
                }
                else if(choice == 12)
                {
                    int t = AutoTest(fileName);
                    if(t!=0)
                        printf("AutoTest failed, error code %d\n", t);
                }
            }
        }
        else if(choice == EXIT)
        {   
            if(myImage != NULL)
                DeleteImage(myImage);
            exit(0);
        }
        else
        { 
           printf("Sorry that was an invalid input.\n");
        }
    }while(choice != EXIT);

    return 0;
} /* end of main */


/*** function definitions ***/

/* prints user menu */
void PrintMenu(){ 
    printf("Please make a choice.\n");
    for(int i=0; i<20; i++)
        printf("-");
    printf("\n1: Load a PPM image\n");
    printf("2: Save a PPM image\n");
    printf("3: Change image to Black and White\n");
    printf("4: Sketch the edge of an image\n");
    printf("5: Shuffle an image\n");
    printf("6: Adjust the brightness of an image\n");
    printf("7: Mirror an image horizontally\n");
    printf("8: Adjust the hue of an image\n");
    printf("9: Rotate or flip the image\n");
    printf("10: Resize the image\n");
    printf("11: Saturate the image\n");
    printf("12: Test all functions\n");
    printf("13: Exit\n");
} /* end of PrintMenu */

/* EOF PhotoLab.c */
