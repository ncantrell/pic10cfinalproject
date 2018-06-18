#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#define ROWS 512
#define COLS 512
#define PI 3.14159265
#define TOL 1.0

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

struct Polynomial{
    vector<double> coeff;
    double x;
    Polynomial(){ coeff.push_back(0); x = 0;}
    Polynomial(vector<double> f, double x_in){ coeff = f; x = x_in;}
    void set_x(double x_in){x = x_in;}
};

int main( int argc, char** argv )
{
        auto create_poly = [](){
                vector<double> coeff;
                double x = 0;
                int deg_n = 0;
                cout << "Please enter the degree of the polynomial: ";
                cin >> deg_n;
                for(int i=0; i<=deg_n; i++){
                    double tmp = 0;
                    cout << "What is the leading coefficient for the x^" + to_string(i) + " term: ";
                    cin >> tmp;
                    coeff.push_back(tmp);
                    }
                cout << "Please enter the value of x: ";
                cin >> x;
                    return static_cast<Polynomial>(Polynomial(coeff,x));
                };
        auto f_1 = create_poly();
        auto poly = [](vector<double> f, double x){
                double ret = 0;
                for(int i=0; i<=f.size(); i++){
                    ret += f[i]* pow (x, i);
                }
                return static_cast<double>(ret);
            };
        auto is_poly = [&](int row, int col, double amplitude, double x_scale, Polynomial poly_in){
            poly_in.set_x(col/1);
            return (((row-2*TOL)<(-1*amplitude*poly(poly_in.coeff, poly_in.x*x_scale))) && ((row+2*TOL)>(-1*amplitude*poly(poly_in.coeff, poly_in.x*x_scale))));
            };

        auto is_sin = [&](int row, int col, double freq, int amplitude, int phase){
            return (((row-TOL)<(amplitude*sin((col+(50)+phase)*PI/freq))) && ((row+TOL)>(amplitude*sin((col+(50)+phase)*PI/freq))));
            };


        cout << "The value of your polynomial at " + to_string(f_1.x) + " is: " + to_string(poly(f_1.coeff, f_1.x)) << endl;
        Mat img,imgOutput;	// image object(s)
    //if(((img = imread( argv[1], 0)).empty()))
    //{
    	Mat plot(cv::Size(COLS, ROWS), CV_8UC1);
    	plot = 255;
    	for(int i=0;i<plot.cols;i++)
        {
            for (int j=plot.rows;j>=0;j--)
            {
	    	//cout << (is_sin(i,j,1,1,0));
                if((i==255) || (j==255) ){plot.at<uchar>(j,i) = 0;} //white
                if(is_sin(j-255,i,100,10,0)){plot.at<uchar>(j,i) = 0;} //white
                if(is_poly(j-255,i-255,10,0.1,f_1)){plot.at<uchar>(j,i) = 0;};
            }
        }
        imshow("Input Image", plot);
        waitKey();
        return 0;
    //}
     //return -1;
}



