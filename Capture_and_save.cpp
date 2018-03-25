/*
----------Objective of this program---------------
1. Capture image through webcam and save as well
2. Display the captured image and save as well
3. Change the captured into GRAYSCALE and save as well
4. Display the HSV of the image and save as well
5. Display the image of different sizes all over the screen and save as well
*/

#include<iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/video/tracking.hpp>
using namespace std;
using namespace cv;
int main(){
    Mat img;  //creating a Mat object to store the frame later
    Mat LoadedImage,Step1;  //for loading saved image
    VideoCapture cap; //Declaring a variable for videocapture..it will capture frame from webcam
    cap.open(0); //associating cap with webcam to use a camera 0
    cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
    while(waitKey(300)!= 27){ //Take images from webcam
        cap>>img;
        imshow("From webcam",img);
        imwrite("/home/king/Desktop/OpenCV/opn/Main_project/pics.jpeg",img);
        continue; //continue to next line of code
    }    
    
    
    LoadedImage = imread("pics.jpeg", IMREAD_COLOR);
    cvtColor(LoadedImage,Step1,COLOR_RGB2HSV);
    imwrite("Second.jpeg", Step1);
    waitKey(10);
 
 // You can load colored image directly as gray scale
     LoadedImage = imread("pics.jpeg", CV_LOAD_IMAGE_GRAYSCALE);
     waitKey(1000); // If you want to see video frames in high rates in the loop jist put here waitKey(20). 
    imwrite("Third.jpeg", LoadedImage);
    
  //  Basic resize and rescale 
 // Resize LoadedImage and save the result to same Mat loaded Image.
 // You can also resize( loadedImage, Result, ..... )
 
    LoadedImage = imread("pics.jpeg", IMREAD_COLOR);
    resize(LoadedImage, LoadedImage, Size(1280, 660));  //You can resize to any size you want Size(width,heigth)
    waitKey(1000);
    imwrite("Fourth.jpeg", LoadedImage);       // It is smaller than source. 100x100 image
    
    LoadedImage = imread("pics.jpeg", IMREAD_COLOR);
    resize(LoadedImage, LoadedImage, Size(LoadedImage.cols/2, LoadedImage.rows/2));                      
    waitKey(1000);                  
    imwrite("Fifth.jpeg", LoadedImage);   //It is 2 times smaller then source-->Save
    waitKey(0);
    return 0;
}

