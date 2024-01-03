#include <iostream>
#include "tgaimage.h"
#include "extra/runfile.h"
#include <cmath>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);


void line2p(int x1,int y1, int x2, int y2, TGAImage &image, TGAColor color)
{
	if(x1>x2 || y1 > y2)
	{
		std::swap(x1,x2);
		std::swap(y1,y2);
	}
	
	for (int px = x1; px < x2; px++)
	{
		float mag = (float)(px - x1) / (float)(x2 - x1);
		//int xdir = x1 + (x2 - x1) * i;
		
		int py = (y1*(1.-mag)) + (y2*mag);
		
		image.set(px,py,color);
	}
}

int main(int argc, char** argv)
{
	//terminal to run > "cmake .. && make && ./rasterizer" in 1 command
    FileRunIndex(argc, argv);//ignore this is garbage mainly done for testing & learning some stuff
	
    TGAImage image(100, 100, TGAImage::RGB);
	/*
	for (size_t i = 0; i < 100; i++)
	{
		image.set(i,i,white);
	}
	image.set(52, 41, red);
	*/

	line2p(13, 20, 80, 40, image, white); 
	line2p(20, 13, 40, 80, image, red); 
	line2p(90, 50, 23, 30, image, red);

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("../images/output.tga");
	return 0;
}


