#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;


int thresh = 110;
int main( int, char** argv )
{
  Mat img;
  Mat img_gray;
  img = imread( argv[1], IMREAD_COLOR );
  cvtColor( img, img_gray, COLOR_BGR2GRAY );
  blur( img_gray, img_gray, Size(3,3) );


  threshold( img_gray, img_gray, thresh, 255, THRESH_BINARY );

  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  findContours( img_gray, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );


  vector<vector<Point> > poly( contours.size() );
  vector<Point2f>circle_center( contours.size() );
  vector<float>circle_radius( contours.size() );
  Mat dst = Mat::zeros( img_gray.size(), CV_8UC3 );
  if(!contours.empty())
  {
	  RNG rng(time(0));
	  size_t i = 0;
	  for( ; i < contours.size(); i++ )
	  {
		  Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		  approxPolyDP( Mat(contours[i]), poly[i], 5, true );
		  drawContours( dst, poly, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point() );

		  minEnclosingCircle( poly[i], circle_center[i], circle_radius[i] );
		  circle( dst, circle_center[i], (int)circle_radius[i], color, 2, 8 );
	  }
  }

  imwrite( "images/Output_Image.jpg", dst );

  return(0);
}



