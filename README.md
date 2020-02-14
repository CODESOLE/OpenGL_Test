# OpenGL_Test
My OpenGL learning repo!
Showcase Video => https://youtu.be/hgZkJ1DKMDc

## Build Instructions for Ubuntu and its variants

First install Visual Studio Code :<br />
`snap install code`<br />
Secondly install necessary libs, copy-paste terminal this :<br />
    
`sudo apt-get update; sudo apt-get install build-essential libevent-pthreads-2.1-6 doxygen xorg-dev libglu1-mesa-dev;sudo apt-get install libglfw3-dev;sudo apt-get install libglew-dev`<br />

Pay attention to libevent-pthreads-`<VERSION>` this version can be change, install according to up to date version
    
Finally download this repo extract it and open that folder with vs code press F5 to run it, by the way don't forget to install Microsoft's C/C++ extension before run that. Otherwise it gives you a error that says "Configured debug type 'cppdbg' is not supported".

Currently just runs on Linux.
