#include<iostream>
#include <stdio.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/video/tracking.hpp>
using namespace std;
using namespace cv;
int threshold_value = 0;
int threshold_type = 3; //for threshold
int const max_BINARY_value = 255;
int const max_type = 1;
const char* window_name = "Image Processing";
const char* trackbar_type = "\t\tHello User!\n\t\tWelcome to Image Processing\t\t\n";
const int alpha_slider_max = 1000; //slider
int alpha_slider;
double alpha;
double beta;
Mat src1,src_gray;
Mat src2,src3,src4,src5;
Mat dst;
static void on_trackbar( int, void* ){  //creating a trackbar
   alpha = (double) alpha_slider/alpha_slider_max ;
   beta = ( 1.0 - alpha );
   addWeighted( src1, alpha, src2, beta, 0.0, dst);
   imshow( "Linear Blend", dst );
}
class Capture{
    private:
        Mat img;  //creating a Mat object to store the frame later
        Mat LoadedImage,Step1;  //for loading saved image
        VideoCapture cap;
    public:
        int photo(){
            cap.open(0); //associating cap with webcam to use a camera 0
            cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
            cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
            while(waitKey(100)!= 27){ //Take images from webcam pressing ESC
                cap>>img;
                imshow("From webcam",img);
                imwrite("/home/king/Desktop/OpenCV/opn/Main_project/First.jpeg",img);
                continue; //continue to next line of code
            }     
            LoadedImage = imread("First.jpeg", IMREAD_COLOR);
            cvtColor(LoadedImage,Step1,COLOR_RGB2HSV);
            imwrite("Second.jpeg", Step1);
            waitKey(10);
            
            LoadedImage = imread("First.jpeg", CV_LOAD_IMAGE_GRAYSCALE);
            waitKey(1000); 
            imwrite("Third.jpeg", LoadedImage);
            return 0;
        } 
        
};

class Process{
    private:
        Mat gray; 
    public:
        int Bar(){
            src1 = imread("First.jpeg");
            src2 = imread("Second.jpeg");
            src3 = imread("Third.jpeg");
            src_gray = imread ("Third.jpeg");
            if( src1.empty() ) { printf("Error loading src1 \n"); return -1; }
            if( src2.empty() ) { printf("Error loading src2 \n"); return -1; }
            if( src3.empty() ) { printf("Error loading src3 \n"); return -1; }
            alpha_slider = 0;
            namedWindow(window_name, CV_WINDOW_NORMAL); // Create Window
            resizeWindow("Window",500,600); //600x600-->size
            moveWindow("Window",500000,3000); //moving window to x,y co-ordinate
            char TrackbarName[50];
            sprintf( TrackbarName, "Alpha x %d", alpha_slider_max );
            createTrackbar( TrackbarName, "Linear Blend", &alpha_slider, alpha_slider_max, on_trackbar );
            
            createTrackbar( trackbar_type, &threshold_type, max_type, Threshold_Demo( 0, 0 ) ); //copied
            threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );
            
            on_trackbar( alpha_slider, 0 );
            waitKey(0);
            
            //Threshold_Demo( 0, 0 );
            
            void Threshold_Demo( int, void* )
            {
                threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );
                imshow( window_name, dst );
            }
            
            return 0;
        }  
};

int main(){
    Capture C;
    Process P;
    cout<<"Press ESC key to capture photo"<<endl;
    C.photo();
    P.Bar();
    return 0;
}
