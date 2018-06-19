# Final Project PIC10C Spring 2018  
Graphing calculator and polynomial interpolation

![alt text](https://raw.githubusercontent.com/ncantrell/pic10cfinalproject/master/menu1.png)
![alt text](https://raw.githubusercontent.com/ncantrell/pic10cfinalproject/master/menu2.png)
![alt text](https://raw.githubusercontent.com/ncantrell/pic10cfinalproject/master/polynomial2.png)

(This project demonstrates the application of some of the topics learned in my PIC10C and MATH 151A classes during Spring Quarter of 2018.)

----

## Quick Start
#### Step 1) Install Requirements (ie. "OpenCV")*
https://docs.opencv.org/trunk/d7/d9f/tutorial_linux_install.html (Linux Development)
https://docs.opencv.org/3.4/d3/d52/tutorial_windows_install.html (Windows Development)
#### Step 2) Configure IDE to link the OpenCV shared libraries
#### Step 3) Compile main.cpp

#### *Motivation behind using OpenCV
This project used the OpenCV library for rendering the graphs. Initially, my hope had been to render via ASCII drawings, but I wasn't satisified with the resulting image quality (primarily due to my terminal using a non-monospaced font).

----
## Final Project (Grading Question's)

### Process
Initially, I considered attempting to make some sort of Tetris clone using the terminal, but I eventually decided to make a graphing calculator instead because I had a previous background in image processing, and I wanted to do something that involved the "Numerical Methods" techniques I was learning in Math 151A.

I first looked at rendering the graphing calculator as ASCII characters and even had a primitive x,y axis drawn in ASCII characters, but the non-monospace font (and my lack of ability to control font display) led me to use OpenCV cv::Mat objects and a namedWindow from OpenCV's "highgui" include.

I wanted to practice functional programming so I used Lambda functions whenever possible. 

### Problems and Problem Solving
My first problem was with non-monospaced fonts making simple line by line rendering difficult.
After deciding to switch to OpenCV, I ended up spending something like 6 hours trying to get the OpenCV dependency working on my current laptop with Code::Blocks. 

"sudo apt-get install libopencv-dev" wasn't getting working compiled binaries for Code::Blocks, so I ended up trying to compile OpenCV 3.0 and 2.4.11 from source. Inevitably, I had weird problems with Cmake and eventually just gave up and used one of my older laptops that already had OpenCV Installed.

This had the side effect of making it difficult to work on the project because the laptop power connector and battery were both in bad shape so if the laptop moved: it often resulted in a cold shutdown from loss of power. 

Eventually these repetitive cold shutdowns resulted in my Linux/Chrubuntu Display manager getting dorked resulting in a login-loop that prevented me from working on the program during my flight to Tokyo.

### Solutions and Lessons Learned
I was eventually able to recover from the login-loop using a tip from askubuntu (source: https://askubuntu.com/a/954426) which was to run "dpkg-reconfigure lightdm" to fix the login-loop.

The problem that was much more difficult to overcome was recovering from the lost time of that 10 hour flight. I had planned to utilize that time productively to get caught up on putting the finishing touches on this project, but had to sleep for most of the flight instead.

I think one of the most frustrating lessons to take away from these problems is that my time management skills and tendency to procrastinate have not improved nearly as much as I thought they had. Additionally, development environment is always frustrating to setup and deal with, but I think getting more familiar with Docker might help me here.

One of the aspects of working on this project that I really enjoyed was getting familiar with Lambda functions in C++.

### Future Work
I would like to replace the CLI for entering equations with a GUI, and solve some of the weird aliasing problems using alternative distance metrics than the static "tolerance" I #define'ed as 'TOL'. 

Would also like to add Neville's method and a symbolic solver that not only can solve for y values for a given x, but can also output the equation for the function that interpolates between those points.

Another feature that I really want to integrate is C++ 11 multithreading to improve the rendering speed.

### Topic Application Summary

## Usage of Topics covered in class: 

(yes) Generic algorithms, lambda functions, binders and adapters 
->wanted to practice using lambda functions, so almost every function in this project is a lambda function

(no) Move semantics
->The only large copy operations were being handled by opencv, so it didn't feel prudent to spend time on this0

(yes) Iterators (The advantages of passing a range [first,last) over passing a container.)
->I used several vector iterators in this project

(no) Smart pointers
->I didn't see any applications for pointers when working on this project. 

(no) RAII idiom 
->I didn't create a copy constructor, copy assignment operator, or destructor so, by the Rule of 3-4.5, this project didn't seem to require RAII...
(OTOH, I believe that OpenCV has a lot of RAII going on under the hood)

(no)Qt 
->I would like to add a GUI to replace the CLI, but my access to a computer that can run Qt Creator has been limited since the end of the quarter. Although, if I had finished non-GUI coding earlier in the quarter, I could have used the PIC lab to do this.

(no) Templates/Template functions/Classes 
->There was not much code in this project replicating logic with different data types. For this reason, I didn't see a ton of benefit to writing any of the code to make use of template functionality.

(no) Inheritance and polymorphism 
->I wanted to use this project to practice functional programming, so I used Lambda functions and struct data types instead of custom classes\

(no) Function pointers 
->for this project, Lambda functions seemed like a better tool.

(yes) C++ STL containers 
->I used several vectors in this project

(yes) git version control

----
## Key Features
### Periodic Function Graphing
#### f(x)=sin(x)
![alt text](https://raw.githubusercontent.com/ncantrell/pic10cfinalproject/master/Periodic1.png)
![alt text](https://raw.githubusercontent.com/ncantrell/pic10cfinalproject/master/Periodic2.png)
#### f(x)=cos(x)
![alt text](https://raw.githubusercontent.com/ncantrell/pic10cfinalproject/master/Periodic5.png)
![alt text](https://raw.githubusercontent.com/ncantrell/pic10cfinalproject/master/Periodic6.png)
#### f(x)=tan(x)
![alt text](https://raw.githubusercontent.com/ncantrell/pic10cfinalproject/master/Periodic3.png)
![alt text](https://raw.githubusercontent.com/ncantrell/pic10cfinalproject/master/Periodic4.png)

### Polynomial Graphing
#### f(x)=(x^3)-5x
![alt text](https://raw.githubusercontent.com/ncantrell/pic10cfinalproject/master/polynomial1.png)
![alt text](https://raw.githubusercontent.com/ncantrell/pic10cfinalproject/master/polynomial2.png)
#### f(x)=x+5
![alt text](https://raw.githubusercontent.com/ncantrell/pic10cfinalproject/master/polynomial3.png)
![alt text](https://raw.githubusercontent.com/ncantrell/pic10cfinalproject/master/polynomial4.png)

### Polynomial Interpolation (Lagrange Polynomial)
![alt text](https://raw.githubusercontent.com/ncantrell/pic10cfinalproject/master/lagrange1.png)
![alt text](https://raw.githubusercontent.com/ncantrell/pic10cfinalproject/master/lagrange2.png)

 
