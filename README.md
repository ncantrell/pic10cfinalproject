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

This had the side effect of making it difficult to work on the project because the laptop power connector and battery were both in bad shape so if the laptop moved: it often resulted in a cold shutdown from loss of power.

2) Detail your research (e.g. include links to tutorials, and/or stackoverflow-like phorums), as well as your struggles (e.g. compilation/linking issues, etc) and the way you either solved them and/or worked around them.

## Solutions and Lessons Learned
3) Detail the issues you came up with, and most importantly, all things you took away from the process. 
(Remember, the main goal of this assignment is to have you showcase your learning process.)

## Future Work
4) let us know about possible ways to improve it.
