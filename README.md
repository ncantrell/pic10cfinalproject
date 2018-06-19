# Final Project pic10c Spring 2018  
Graphing calculator and polynomial interpolation

----
### Key Features
 
----
### Quick Start

## Dependencies
This project used the OpenCV library for rendering the graphs. Initially, my hope had been to render via ASCII drawings, but I wasn't satisified with the resulting image quality using non-monospaced fonts.


----
### Final Project (Grading Question's)

## Process
Initially, I considered attempting to make some sort of Tetris clone using the terminal, but I eventually decided to make a graphing calculator instead because I had a previous background in image processing, and I wanted to do something that involved the "Numerical Methods" techniques I was learning in Math 151A.

I first looked at rendering the graphing calculator as ASCII characters and even had a primitive x,y axis drawn in ASCII characters, but the non-monospace font (and my lack of ability to control font display) led me to use OpenCV cv::Mat objects and a namedWindow from OpenCV's "highgui" include.

I wanted to practice functional programming so I used Lambda functions whenever possible. 

## Problems and Problem Solving
My first problem was with non-monospaced fonts making simple line by line rendering difficult.
After deciding to switch to OpenCV, I ended up spending something like 6 hours trying to get the OpenCV dependency working on my current laptop with Code::Blocks. 

"sudo apt-get install libopencv-dev" wasn't getting working compiled binaries for Code::Blocks, so I ended up trying to compile OpenCV 3.0 and 2.4.11 from source. Inevitably, I had weird problems with Cmake and eventually just gave up and used one of my older laptops that already had OpenCV Installed.

This had the side effect of making it difficult to work on the project because the laptop power connector and battery were both in bad shape so if the laptop moved: it often resulted in a cold shutdown from loss of power. Eventually these repetitive cold shutdowns resulted in my Linux/Chrubuntu Display manager getting dorked resulting in a login-loop that prevented me from working on the program during my flight to Tokyo.

## Solutions and Lessons Learned
I was eventually able to recover from the Bootloop using a tip from askubuntu (source: https://askubuntu.com/a/954426) which was to run "dpkg-reconfigure lightdm" to fix the login-loop.

The problem that was much more difficult to overcome was recovering from the lost time of that 10 hour flight. I had planned to utilize that time productively to get caught up on putting the finishing touches on this project, but had to sleep for most of the flight instead.

## Future Work
I would like to replace the CLI for entering equations with a GUI, and solve some of the weird aliasing problems using alternative distance metrics than the static "tolerance" I #define'ed. Would also like to add Neville's method and a symbolic solver that not only can solve for y values for a given x, but can also output the equation for the function that interpolates between those points.
