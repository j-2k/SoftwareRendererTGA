# ImagePPM
Testing how to get a ppm image from cpp, work flow is awful on windows with cmake but whatever.  

I'm not sure what workflow I should use but cmake makes me want to use VSC and not VS, but ill just write some stuff for how to make this garbage work, since this took me an hour to figure out.  
to get a image from cpp code in ppm format,  

Build the project with redirecting the standard output stream to a image file (ppm in this case & using CMake, ps I have no idea how to use CMake, so I'm guna learn that before I continue)  
### 1. cmake --build build
build the new changes   
### 2. your/directory/of/executable.exe > image.ppm   
convert output stream to image file ppm, I used cmd, powershell, cmder all cool     
### 3. go to file of executable, image.ppm should be there, open ppm on imagemagic or photoeditor photoshop, gimp etc etc. no native support for ppm on windows.

# C++ notes about file structures with cpp and h files
#### I didnt touch cpp and needed a refresher on translation units & headers so I wrote this here for myself
basic c++ notes about translation units (.cpp) & header files (.h/.hpp),  
use #pragma once to include a header file only ONCE in a translation unit. ( USE PRAGMA IN TRANSLATION UNITS ALWAYS )   
use header files only to hold declarations about certain information, example:  
debug.h > should contain function declarations only related to debugging/console,  
```cpp
//the only line inside debug.h
void Debug(const char* msg);
```
use cpp files to implement the declarations in the header files like so:  
```cpp
//the only line inside debug.cpp
#pragma once
#include "debug.h"
void Debug(const char* msg) {return msg}  
```
in your main to use this function do #include "debug.h" (quotes for files relative to the current file and angled brackets only for compiler include paths)
```cpp
//somewhere in main
#pragma once
#include "debug.h"
#include <iostream>
int main()
{
  Debug("Hello")
}
```
# first ppm image
converted image4ppm to png:  
![uvimage](images/image4convertedfromppmtopng.png)
