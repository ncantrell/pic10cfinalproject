#define ROWS 512
#define COLS 512
#define PI 3.14159265
#define TOL .5

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv; 

bool is_sin(int row, int col, double freq, int amplitude, int phase){
    return (((row-TOL)<amplitude*sin((col-phase)*PI/10)) && (sin(col*PI/10)<(row+TOL)));
}

int main( int argc, char** argv )
{
  Mat img,imgOutput;	// image object(s)

    if((!(img = imread( argv[1], 0)).empty()))
    {
    	Mat plot(cv::Size(COLS, ROWS), CV_64FC1);
    	plot = 255;
    	for(int i=0;i<plot.rows;i++) 
	{
	  for (int j=0;j<plot.cols;j++)
  	  {
	    	//cout << (is_sin(i,j,1,1,0));
	    	if(true) plot.at<uchar>(j,i) = 0; //white
  		}
	}
	imshow("Input Image", plot);

     waitKey();

      return 0;
    }

     return -1;
}
