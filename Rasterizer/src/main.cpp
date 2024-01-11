#include "precompiledheaders.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const TGAColor blue  = TGAColor(0,   0,   255, 255);
const TGAColor yellow = TGAColor(255, 255, 0, 255);
const TGAColor purple = TGAColor(255, 0, 255, 255);

Model *model = NULL;
const int width  = 1000;
const int height = 1000;

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
	/* Obj Wireframe Rendering Lines Old
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

	/*Obj Triangle Rendering*/
	for (int i=0; i<model->nfaces(); i++) { 
    std::vector<int> face = model->face(i); 
	Vec2i screen_coords[3]; 
		for (int j=0; j<3; j++) { 
			Vec3f world_coords = model->vert(face[j]);
			screen_coords[j] = Vec2i((world_coords.x+1.)*width/2., (world_coords.y+1.)*height/2.); 
		} 

		TGAColor c = TGAColor(255,20,255, 255);
		BaryTriangle(screen_coords,image,c);
	}
	
	/*Triangle Rendering Old
	Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)}; 
	Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)}; 
	Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)}; 

    LineSweepTriangle(t0[0], t0[1], t0[2], image, yellow);
    LineSweepTriangle(t1[0], t1[1], t1[2], image, yellow);
    LineSweepTriangle(t2[0], t2[1], t2[2], image, purple);
	*/

	/*Triangle Rendering Using Barycentric Coordinates
	Vec2i triangle[3] = {Vec2i(50,50),   Vec2i(150, 50),  Vec2i(150, 150)};
	BaryTriangle(triangle, image, yellow);
	*/


	image.flip_vertically(); //origin at the left bottom corner of the image
	std::string rstr = std::to_string(run);
	std::string output = "../../images/output" + rstr + ".tga";

	image.write_tga_file(output.c_str());
	delete model;
	return 0;
}


