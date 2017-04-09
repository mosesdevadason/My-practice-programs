This is to demonstrate how to write a C interface for C++ code, STL containers 
etc that can be used in C programs.
The header file contains only C constructs in the funtion prototypes. The
prototypes are enclosed within extern "C" construct. These will be the wrappers
for the C++ code. This is done to prevent name mangling by the C++ compiler. Now 
we can write c programs which can make use of the C++ features like STL etc by 
calling these wrapper c functions.

Here, simple C wrappers have been written to create and use C++ hash map STL
container
