# Showcase Images
***Note: All important project information is after the images section!***

## Stage 0 Render TGA Image
![uvimage](cpp2ppm_CMake/images/image4convertedfromppmtopng.png)

## Stage 1 Bresenham's line Algorithm
<img src="https://github.com/j-2k/ImagePPM/assets/52252068/945a6815-6874-4052-a663-5d4f9e0ebaea">

## Stage 2 Wireframe Rendering
![quakewirefr](https://github.com/j-2k/ImagePPM/assets/52252068/f08e0dfe-5763-414a-b97f-b1c1d26c95ce)
![render1](https://github.com/j-2k/ImagePPM/assets/52252068/51ddfa12-b44a-4e64-b8d1-03f0e73fbe6b)
![Untitled-2](https://github.com/j-2k/ImagePPM/assets/52252068/24be2bd9-eec7-4f21-b87e-4963a82f53b8)



# ImagePPM
Testing how to get a ppm image from cpp, work flow is awful on windows with cmake but whatever.  
I used VS22, and chose a cmake as a base project. Will try to do proper build instructions later, I will try building to both mac & windows.

I'm not sure what workflow I should use but cmake makes me want to use VSC and not VS, but ill just write some stuff for how to make this garbage work, since this took me an hour to figure out.  
to get a image from cpp code in ppm format,  

*this build instructions writing from me is garbage, im going to later copy what other good people write for build instructions, im just writing this for myself*

## Prerequisites
- CMake (version 3.12 or higher)
- A C++ compiler that supports C++20
## Building
### 1. clone the project
```zsh
git clone https://github.com/j-2k/ImagePPM.git
```
### 2. go to the "out" directory
```zsh
#ex > assuming ur in imagePPM master folder, 
cd cpp2ppm_CMake/out/
```
### 3. make an empty build folder in out 
```zsh
#build is already taken & not empty, so build ur
#own proj files with in a different build folder/name
mkdir build2
cd build2
```
### 4. generate the build files
```zsh
#cmake .. goes into the parent directory to find CMAKELISTS.text file
#to generate build files
cmake ..
```
### 5. build the project
```zsh
#do make or cmake --build .
make
#or
cmake --build .
```
### 6. Run the project & output stream to ppm
```zsh
#find the path to the exe (file path/to/directory/with/exe)/jumagfx_cmake.exe > image.ppm
#incase you didnt put the exe in some other place this should just work
./jumagfx_cmake.exe > image.ppm
# the "." will search the current dir & run the exe file remove .exe if on terminal
./jumagfx_cmake > image.ppm
```




<details>
  <summary> Old personal build notes</summary>
building is the mostly? the same in all os but im just writing some stuff I learned/did along the way  
maybe just the compiler setting is different between os (msvc) & the build systems(make ninja nmake visualstudio etc)? but idk much about that.
  
## Windows
Build the project with redirecting the standard output stream to a image file (ppm in this case & using CMake, ps I have no idea how to use CMake, so I'm guna learn that before I continue)  
### 1. cmake --build build
build the new changes   
### 2. your/directory/of/executable.exe > image.ppm   
convert output stream to image file ppm, I used cmd, powershell, cmder all cool     
### 3. go to file of executable, image.ppm should be there, open ppm on imagemagic or photoeditor photoshop, gimp etc etc. no native support to open ppm images on windows, however MAC actually lets you open & see PPM images.
## MacOS
Building proj on mac
### 1. enter a empty build folder and run "cmake (PATH TO CMAKELISTS.txt)/." to generate build files
example > in out/build/mac folder is empty, when inside that dir in terminal do "cmake ../../../."
### 2. do "make" or "cmake --build ." to build the project
exmaple > inside mac should be build folders do make or cmake --build . to build project & gen a exe file
### 3. locate jumagfx_cmake.exe and run the command "path/to/jumagfx_cmake.exe > image.ppm" to generate a ppm image in the current directory.
example > "cpp2ppm_CMake/out/build/mac/JumaGFX_CMake/JumaGFX_CMake > image.ppm"
</details>



# C++ notes about file structures with cpp and h files
#### I didnt touch cpp and needed a refresher on translation units & headers so I wrote this here for myself
basic c++ notes about translation units (.cpp) & header files (.h/.hpp),  
use #pragma once to include a header file only ONCE in a translation unit (DONT FORGET TO USE PRAGMA IN H FILES! IMPORTANT!).  
an example of duplicate definitions without pragma:  
assume car.h, engine.h, & main.cpp if main.cpp contains both h files & calls them, with car having to print "car" and engine printing "engine". then main will give "car" & "engine" printed but if the car h file includes engine h without pragma you will get 2 engine prints and 1 car print if that makes sense. So use pragma once in both h files just for sake of guarding against this issue.  
use header files only to hold declarations about certain information, example:  
debug.h > should contain function declarations only related to debugging/console,  
```cpp
//inside debug.h
#pragma once
void Debug(const char* msg);
```
use cpp files to implement the declarations in the header files like so:  
```cpp
//the only line inside debug.cpp
#include "debug.h"
void Debug(const char* msg) {return msg}  
```
in your main to use this function do #include "debug.h" (quotes for files relative to the current file and angled brackets only for compiler include paths)
```cpp
//somewhere in main
#include "debug.h"
#include <iostream>
int main()
{
  Debug("Hello")
}
```
# first ppm image
converted image4ppm to png:  
![uvimage](cpp2ppm_CMake/images/image4convertedfromppmtopng.png)
