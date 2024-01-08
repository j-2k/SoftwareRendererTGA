#include <iostream>
#include "tgaimage.h"
#include "extra/runfile.h"
#include <cmath>
#include "geometry.h"
#include "model.h"
#include <vector>
#include <string>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const TGAColor blue  = TGAColor(0,   0,   255, 255);
const TGAColor yellow = TGAColor(255, 255, 0, 255);
const TGAColor purple = TGAColor(255, 0, 255, 255);

Model *model = NULL;
const int width  = 200;
const int height = 200;

//Bresenham Line Algorithm
void line2p(int x1,int y1, int x2, int y2, TGAImage &image, TGAColor color)
{
	bool steep = false;
	if(std::abs(x1-x2) < std::abs(y1-y2)){
		std::swap(x1,y1);
		std::swap(x2,y2);
		steep = true;
	}
	
	if(x1>x2){				// || y1 > y2){
		std::swap(x1,x2);
		std::swap(y1,y2);
	}

	int dx = x2 - x1;
	int dy = y2 - y1;

	int derror2 = std::abs(dy)*2;
	float error2 = 0;

	int y = y1;
	
	for (int px = x1; px <= x2; px++){
		float mag = (float)(px - x1) / (float)(x2 - x1);
		int py = (y1*(1.-mag)) + (y2*mag);
		if(steep)
			{image.set(py,px,color);} //if steep (transposed) then return to normal
		else
			{image.set(px,py,color);} //normal

		error2 += derror2;
		if (error2 > dx){
			y += (y2>y1 ? 1:-1);
			error2 -= dx*2;
		}
		
	}
}
//Bresenham Line Algorithm Overload with Vec2i
void line2p(Vec2i p0, Vec2i p1, TGAImage &image, TGAColor color) {
    bool steep = false;
    if (std::abs(p0.x-p1.x)<std::abs(p0.y-p1.y)) {
        std::swap(p0.x, p0.y);
        std::swap(p1.x, p1.y);
        steep = true;
    }
    if (p0.x>p1.x) {
        std::swap(p0, p1);
    }

    for (int x=p0.x; x<=p1.x; x++) {
        float t = (x-p0.x)/(float)(p1.x-p0.x);
        int y = p0.y*(1.-t) + p1.y*t;
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
    }
}

//Triangle Method
void triangle(Vec2i p0, Vec2i p1, Vec2i p2, TGAImage &image, TGAColor color) {
    //Sort all 3 points from Y axis top to down
	if(p0.y > p1.y) std::swap(p0,p1);
	if(p0.y > p2.y) std::swap(p0,p2);
	if(p1.y > p2.y) std::swap(p1,p2);
	
	
	line2p(p0, p1, image, yellow);
    line2p(p1, p2, image, yellow);
    line2p(p2, p0, image, purple);
}

int main(int argc, char** argv)
{
	//terminal to run > "cmake .. && make && ./rasterizer" in 1 command
    int run = FileRunIndex(argc, argv);//ignore this is garbage mainly done for testing & learning some stuff
	
    TGAImage image(width, height, TGAImage::RGB);

	/* UV RENDERING
	for (size_t x = 0; x < width; x++)
	{
		float magX = (float)x / (float)width;
		for (size_t y = 0; y < height; y++)
		{
			float magY = (float)y / (float)height;
			TGAColor uvc = TGAColor((magX)*255, (magY)*255, 0, 255);
			image.set(x,y,uvc);
		}
	}
	*/

	model = new Model("../../models/duoranger.obj");
	/* Wireframe Rendering
	for (int i=0; i<model->nfaces(); i++) { 
    std::vector<int> face = model->face(i); 
    for (int j=0; j<3; j++) { 
        Vec3f v0 = model->vert(face[j]); 
        Vec3f v1 = model->vert(face[(j+1)%3]); 
        int x0 = (v0.x+1.)*width/2.; 
        int y0 = (v0.y+1.)*height/2.; 
        int x1 = (v1.x+1.)*width/2.; 
        int y1 = (v1.y+1.)*height/2.; 
		
		const TGAColor color = TGAColor(rand()%255, rand()%255, rand()%255, 255);
        line2p(x0, y0, x1, y1, image, color); 
		} 
	}
	*/
	
	/*Triangle Rendering*/
	Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)}; 
	Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)}; 
	Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)}; 

    triangle(t0[0], t0[1], t0[2], image, yellow);
    triangle(t1[0], t1[1], t1[2], image, yellow);
    triangle(t2[0], t2[1], t2[2], image, purple);


	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	std::string rstr = std::to_string(run);
	std::string output = "../../images/output" + rstr + ".tga";

	image.write_tga_file(output.c_str());
	delete model;
	return 0;
}


