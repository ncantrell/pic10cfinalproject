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
struct Point2d{
    double x;
    double y;
    Point2d(){x=NULL; y=NULL;}
    Point2d(double x_in, double y_in){ x = x_in; y = y_in;}
};

int main( int argc, char** argv )
{
        auto create_datapoints = [&](){
            int num_p;
            vector<Point2d> datapoints;
            cout << "Please enter the number of points: ";
            cin >> num_p;
            for(int i=0; i<num_p; i++){ //create a uniform random double within the interval [a,b]
                double tmpx, tmpy;
                string str,tok;
                cout << "Please enter (point " + to_string(i) + ") as \"x,y\": ";
                std::cin >> str;
                std::stringstream ss(str);
                while( ss.good() )
                {
                    string substr;
                    std::getline(ss, substr, ',');
                    ss >> tmpy;
                    std::getline(ss, substr);
                    std::stringstream ss2(substr);
                    ss2 >> tmpx;
                }
                Point2d tmp(tmpx, tmpy);
                datapoints.push_back(tmp);
            }
            return static_cast<vector<Point2d>>(datapoints);
        };

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
        auto lagrange_poly = [](vector<Point2d> &datapoints, double x){
            double ret = 0;
            for(int k=0; k<datapoints.size(); k++){
                double L_k=datapoints[k].y;
                for(int i=0; i<datapoints.size(); i++){
                    if(i!=k){ L_k *= (x-datapoints[i].x)/(datapoints[k].x - datapoints[i].x); } //if statement to avoid divide by zero
                }
                ret += L_k;
            }
            return static_cast<double>(ret);
        };
        auto data = create_datapoints();
        for(int i=0; i<data.size(); i++){
            cout << "(point " + to_string(i) + ") x: " + to_string(data[i].x) + " y:" + to_string(data[i].y) << endl;
        }
        double lx = 0;
        cout << "Please enter the value of x where you want the value of the Lagrange Interpolating Polynomial formed with these points: ";
        cin >> lx;
        cout << "The value of the Lagrange Polynomial formed with these points at " + to_string(lx) + " is: " + to_string(lagrange_poly(data,lx)) << endl;
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
