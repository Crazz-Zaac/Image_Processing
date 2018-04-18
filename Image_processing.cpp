/*
 
*/
#include <iostream>
#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/video/background_segm.hpp>
#include <opencv2/video/tracking.hpp>
using namespace std;
using namespace cv;
const int alpha_slider_max = 2000; //defining the maximum value for the trackbar
int alpha_slider;
double alpha;
double beta;
Mat src1,src2,src3,src4,src5,src6; //For six different images
Mat dst; 
static void on_trackbar( int, void* ){
   alpha = (double) alpha_slider/alpha_slider_max ; //typecasting 
   beta = ( 1.0 - alpha );
   
   //First two images
   addWeighted( src2, alpha, src1, beta, 0.0, dst);
   imshow( "First Linear Blend", dst );
   
   //Second two images
   addWeighted( src4, alpha, src3, beta, 0.0, dst);
   imshow( "Second Linear Blend", dst );
   
   //Last two images
   addWeighted( src5, alpha, src6, beta, 0.0, dst);
   imshow( "Third Linear Blend", dst );
}

class Capture{
    private:
        Mat img,Rgb,Rgb1,image,Grey,output;  //creating a Mat object to store the frame later
        Mat LoadedImage,Binary,Step1;  //for loading saved image
        VideoCapture cap; 
        string s1;
    public:
        int photo(){
            cap.open(0); //associating cap with webcam to use a camera 0
            cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
            cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
            while(waitKey(100)!= 27){ //Take images from webcam pressing ESC
                cap>>img;
                imshow("From webcam",img);
                imwrite("/home/king/Desktop/OpenCV/opn/Main_project/First.jpeg",img);
                s1="From webcam";
                void destroyWindow(const string&s1);     
                continue; //continue to next line of code
            }
            //Taking the captured image and changing the taken picture into Hue Saturation Vector
            LoadedImage = imread("First.jpeg", IMREAD_COLOR);
            cvtColor(LoadedImage,Step1,COLOR_RGB2HSV);
            imwrite("Second.jpeg", Step1);
            waitKey(10);
            //Changing the taken picture into Grayscale
            LoadedImage = imread("First.jpeg", CV_LOAD_IMAGE_GRAYSCALE); 
            waitKey(1000); 
            imwrite("Third.jpeg", LoadedImage);
            //Changing the Grayscale image into Binary
            Rgb = imread("Third.jpeg",WINDOW_AUTOSIZE);
            threshold(Rgb,Binary,150,250,THRESH_BINARY); //transforms into binary
            imwrite("Fourth.jpeg",Binary);
            //Changing the Grayscale image into Binary
            Rgb1 = imread("Third.jpeg",WINDOW_AUTOSIZE);
            threshold(Rgb,Binary,20, 255,THRESH_TRUNC); //transforms into binary
            imwrite("Fifth.jpeg",Binary);
            //Changing the Grayscale image into Binary
            image= imread("First.jpeg");
            inRange(image,Scalar(0, 125, 0),Scalar(255, 200, 255), output);
            imwrite("Sixth.jpeg",output);
            return 0;
        } 
        
};

class Process{
    private:
    
    public:
        int Bar(){
            //Taking the saved images from the source
            src1 = imread("First.jpeg");
            src2 = imread("Second.jpeg");
            src3 = imread("Third.jpeg");
            src4 = imread("Fourth.jpeg");
            src5 = imread("Fifth.jpeg");
            src6 = imread("Sixth.jpeg");
            //Checking if images are available or not
            if( src1.empty() ) { printf("Error loading src1 \n"); return -1; }
            if( src2.empty() ) { printf("Error loading src2 \n"); return -1; }
            if( src3.empty() ) { printf("Error loading src3 \n"); return -1; }
            if( src4.empty() ) { printf("Error loading src4 \n"); return -1; }
            if( src5.empty() ) { printf("Error loading src5 \n"); return -1; }
            if( src6.empty() ) { printf("Error loading src6 \n"); return -1; }
            
            alpha_slider = 0; //initializing
            //First window with two sources
            namedWindow("First Linear Blend", CV_GUI_EXPANDED);//CV_WINDOW_NORMAL); // Create Window
            resizeWindow("First Linear Blend",400,400); //size of window
            moveWindow("First Linear Blend",50,100); //moving window to x,y co-ordinate
            //Second window with two sources
            namedWindow("Second Linear Blend", CV_WINDOW_NORMAL); // Create Window
            resizeWindow("Second Linear Blend",400,400); //size of window
            moveWindow("Second Linear Blend",500,100); //moving window to x,y co-ordinate
            //Third window with two sources
            namedWindow("Third Linear Blend", CV_WINDOW_NORMAL); // Create Window
            resizeWindow("Third Linear Blend",400,400); //size of window
            moveWindow("Third Linear Blend",950,100); //moving window to x,y co-ordinate
            
            //setting Trackbar 
            char TrackbarName[50];
            sprintf( TrackbarName, "Alpha x %d", alpha_slider_max );
            createTrackbar( TrackbarName, "First Linear Blend", &alpha_slider, alpha_slider_max, on_trackbar );
            on_trackbar( alpha_slider, 0 );
            waitKey(0);
            return 0;
        }
};

int main(){
    Capture C;
    Process P;
    C.photo();
    P.Bar();
    return 0;
}
