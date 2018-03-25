#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
using namespace cv;
const int alpha_slider_max = 1000;
int alpha_slider;
double alpha;
double beta;
Mat src1;
Mat src2,src3,src4,src5;
Mat dst;
static void on_trackbar( int, void* )
{
   alpha = (double) alpha_slider/alpha_slider_max ;
   beta = ( 1.0 - alpha );
   addWeighted( src1, alpha, src2, beta, 0.0, dst);
   imshow( "Linear Blend", dst );
}
int main( void ){
   Mat gray; 
   src1 = imread("pics.jpeg");
   src2 = imread("Second.jpeg");
   src3 = imread("Third.jpeg");
   src4 = imread("Fourth.jpeg");
   src5 = imread("Fifth.jpeg");
   if( src1.empty() ) { printf("Error loading src1 \n"); return -1; }
   if( src2.empty() ) { printf("Error loading src2 \n"); return -1; }
   if( src3.empty() ) { printf("Error loading src3 \n"); return -1; }
   if( src4.empty() ) { printf("Error loading src4 \n"); return -1; }
   if( src5.empty() ) { printf("Error loading src5 \n"); return -1; }
   Mat src6= imread("sam2.bmp",1); // load source image
   cvtColor(src6, gray, CV_BGR2GRAY); //perform gray scale conversion.
   imwrite("Next.bmp",src6);
   alpha_slider = 0;
   namedWindow("Linear Blend", CV_WINDOW_NORMAL); // Create Window
   resizeWindow("Window",500,600); //600x600-->size
   moveWindow("Window",500000,3000); //moving window to x,y co-ordinate
   char TrackbarName[50];
   sprintf( TrackbarName, "Alpha x %d", alpha_slider_max );
   createTrackbar( TrackbarName, "Linear Blend", &alpha_slider, alpha_slider_max, on_trackbar );
   on_trackbar( alpha_slider, 0 );
   waitKey(0);
   return 0;
}
