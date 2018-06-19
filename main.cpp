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
#include <sstream>
#include <vector>

using namespace std;
using namespace cv;

struct Polynomial{
    vector<double> coeff;
    double x;
    Polynomial(){ coeff.push_back(0); x = 0;}
    Polynomial(vector<double> f, double x_in){ coeff = f; x = x_in;}
    void set_x(double x_in){x = x_in;}
};
struct Periodic{
    double x;
    double freq;
    int amplitude;
    int phase;
    int type;
    Periodic(){type = 1; freq = 100; amplitude = 10; phase = 10; x = 0; }
    Periodic(int t, double f, int a, int p, double x_in){ type = t; freq = f; amplitude = a; phase = p; x = x_in;}
    void set_x(double x_in){x = x_in;}
};

int main( int argc, char** argv )
{
        string menu = "";
        int selection = 0;
        cout << "Nicholas Cantrell's PIC10C Final Project" << endl;
        cout << "Press any key (followed by \'enter\') to continue..." << endl;
        cin >> menu;
        system("pause");
        system("clear");
        cout << "Main Menu:" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "To graph a periodic function, press \'1\'" << endl;
        cout << "To graph a polynomial function, press \'2\'" << endl;
        cout << "To manually enter a set of points for polynomial interpolation, press \'3\'" << endl;
        cout << "To generate a set of points for polynomial interpolation, press \'4\'" << endl;
        cin >> selection;
        system("clear");


        struct Point2d{
            double x;
            double y;
            Point2d(){x=NULL; y=NULL;}
            Point2d(double x_in, double y_in){ x = x_in; y = y_in;}
        };

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

        auto poly = [](vector<double> f, double x){
                double ret = 0;
                for(int i=0; i<=f.size(); i++){
                    ret += f[i]* pow (x, i);
                }
                return static_cast<double>(ret);
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
                x = 0;
                //cin >> x;
                return static_cast<Polynomial>(Polynomial(coeff,x));
            };
        auto create_periodic = [](){
                int type = 1;
                bool sin = false;
                bool cos = false;
                bool tan = false;
                while(!sin && !cos && !tan){
                    cout << "Press \'1\' for sin(), \'2\' for cos(), or \'3\' for tan(): ";
                    cin >> type;
                    if(type == 1) sin = true;
                    if(type == 2) cos = true;
                    if(type == 3) tan = true;
                    if(!sin && !cos && !tan) cout << "Please make a valid selection" << endl;
                }
                double x = 0;
                double freq = 100;
                int amplitude = 10;
                int phase = 0;

                if(sin || cos || tan){
                    cout << "Please enter the frequency of the function (in hz):";
                    cin >> freq;
                    cout << "Please enter the amplitude of the function: ";
                    cin >> amplitude;
                    cout << "Please enter the phase of the function (in radians): ";
                    cin >> phase;
                    //cout << "Please enter the value of x: ";
                    x = 0;
                }
                return static_cast<Periodic>(Periodic(type, freq, amplitude, phase, x));
            };
        auto create_datapoints = [](){
            vector<Point2d> datapoints;
            int num_p;
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
        auto create_random_datapoints = [&](){
            int num_p;
            double a;
            double b;
            vector<Point2d> datapoints;
            auto f_1 = create_poly();
            cout << "Please enter the beginning of the interval: ";
            cin >> a;
            cout << "Please enter the end of the interval: ";
            cin >> b;
            cout << "Please enter the number of points: ";
            cin >> num_p;

            for(int i=0; i<=num_p; i++){
                double xtmp = ((double)rand() / RAND_MAX) * (b - a) + a;
                Point2d tmp(xtmp, poly(f_1.coeff, xtmp));
                datapoints.push_back(tmp);
                }
            return static_cast<vector<Point2d>>(datapoints);
        };
        auto is_poly = [&](int row, int col, double amplitude, double x_scale, Polynomial poly_in){
            poly_in.set_x(col/1);
            return (((row-2*TOL)<(-1*amplitude*poly(poly_in.coeff, poly_in.x*x_scale))) && ((row+2*TOL)>(-1*amplitude*poly(poly_in.coeff, poly_in.x*x_scale))));
            };
        auto is_sin = [&](int row, int col, Periodic periodic_in){
            //return (((row-TOL)<(amplitude*sin((col+(50)+phase)*PI/freq))) && ((row+TOL)>(amplitude*sin((col+(50)+phase)*PI/freq))));
            return (((row-TOL)<(periodic_in.amplitude*sin((col+(50)+periodic_in.phase)*PI/periodic_in.freq))) && ((row+TOL)>(periodic_in.amplitude*sin((col+(50)+periodic_in.phase)*PI/periodic_in.freq))));
            };
        auto is_cos = [&](int row, int col, Periodic periodic_in){
            //return (((row-TOL)<(amplitude*sin((col+(50)+phase)*PI/freq))) && ((row+TOL)>(amplitude*sin((col+(50)+phase)*PI/freq))));
            return (((row-TOL)<(periodic_in.amplitude*cos((col+(50)+periodic_in.phase)*PI/periodic_in.freq))) && ((row+TOL)>(periodic_in.amplitude*cos((col+(50)+periodic_in.phase)*PI/periodic_in.freq))));
            };
        auto is_tan = [&](int row, int col, Periodic periodic_in){
            //return (((row-TOL)<(amplitude*sin((col+(50)+phase)*PI/freq))) && ((row+TOL)>(amplitude*sin((col+(50)+phase)*PI/freq))));
            return (((row-TOL)<(periodic_in.amplitude*tan((col+(50)+periodic_in.phase)*PI/periodic_in.freq))) && ((row+TOL)>(periodic_in.amplitude*tan((col+(50)+periodic_in.phase)*PI/periodic_in.freq))));
            };



        if((selection == 1) || (selection == 2)){
            Mat img,imgOutput;
            Mat plot(cv::Size(COLS, ROWS), CV_8UC1);
            plot = 255;

                //cout << (is_sin(i,j,1,1,0));
                    if(selection == 1){
                        auto f_2 = create_periodic();
                        for(int i=0;i<plot.cols;i++){
                            for (int j=plot.rows;j>=0;j--){
                                //cout << "selection 1!" << endl;
                                if((i==255) || (j==255) ){plot.at<uchar>(j,i) = 0;} //white
                                if(f_2.type == 1)if(is_sin(j-255,i,f_2)){plot.at<uchar>(j,i) = 0;} //white
                                if(f_2.type == 2)if(is_cos(j-255,i,f_2)){plot.at<uchar>(j,i) = 0;} //white
                                if(f_2.type == 3)if(is_tan(j-255,i,f_2)){plot.at<uchar>(j,-i) = 0;} //white
                            }
                        }
                    }
                    if( selection == 2){
                        auto f_1 = create_poly();
                        for(int i=0;i<plot.cols;i++){
                            for (int j=plot.rows;j>=0;j--){
                                //cout << "selection 2!" << endl;
                                if((i==255) || (j==255) ){plot.at<uchar>(j,i) = 0;} //white
                                if(is_poly(j-255,i-255,10,0.1,f_1)){plot.at<uchar>(j,i) = 0;};
                            }
                        }
                        imshow("Input Image", plot);
                        waitKey();
                    }
                    imshow("Input Image", plot);
                    waitKey();
                }
        if( selection == 3){ auto data = create_datapoints();
            double lx = 0;
            cout << "Please enter the value of x where you want the value of the Polynomial formed with these points: ";
            cin >> lx;
            cout << "The value of the Lagrange Polynomial formed with these points at " + to_string(lx) + " is: " + to_string(lagrange_poly(data,lx)) << endl;
        }
        if( selection == 4){ auto data = create_random_datapoints();
            for(int i=0; i<data.size(); i++){
                cout << "(point " + to_string(i) + ") x: " + to_string(data[i].x) + " y:" + to_string(data[i].y) << endl;
            }
            double lx = 0;
            cout << "Please enter the value of x where you want the value of the Polynomial formed with these points: ";
            cin >> lx;
            cout << "The value of the Lagrange Polynomial formed with these points at " + to_string(lx) + " is: " + to_string(lagrange_poly(data,lx)) << endl;
        }

    return 0;
}
