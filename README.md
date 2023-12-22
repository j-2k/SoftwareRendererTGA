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



converted image4ppm to png:  
![uvimage](images/image4convertedfromppmtopng.png)
