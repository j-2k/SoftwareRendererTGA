#include "precompiledheaders.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const TGAColor blue  = TGAColor(0,   0,   255, 255);
const TGAColor yellow = TGAColor(255, 255, 0, 255);
const TGAColor purple = TGAColor(255, 0, 255, 255);

//const Vec3f light_direction(1,-1,-1); //Vec3f(-1,-1,-1);
const Vec3f light_direction(0,0,-1);

Model *model = NULL;
const int width  = 1000;
const int height = 1000;
//const int depth = 255;

//Vec3f camera(0,0,7);
//int *zbuffer = NULL;

//Shader Stage
Vec3f eye(1,1,1);
Vec3f origin(0,0,0);
Vec3f up(0,1,0);


/* First Camera Prespective Projection
Vec3f m2v(Matrix m) {
    return Vec3f(m[0][0]/m[3][0], m[1][0]/m[3][0], m[2][0]/m[3][0]);//(x/w,y/w,z/w) divide by w to get the normalized vector
}

Matrix v2m(Vec3f v) {	//converts a vector to a matrix
    Matrix m(4, 1);
    m[0][0] = v.x;
    m[1][0] = v.y;
    m[2][0] = v.z;
    m[3][0] = 1.f;
    return m;
}

Matrix viewport(int x, int y, int w, int h) {	//converts the viewport to a matrix
    Matrix m = Matrix::identity(4);
    m[0][3] = x+w/2.f;		//moves the viewport to the center of the screen
    m[1][3] = y+h/2.f;		//moves the viewport to the center of the screen
    m[2][3] = depth/2.f;	//what is happening here? this is scaling the viewport to the depth of the screen

    m[0][0] = w/2.f;	//scale the viewport
    m[1][1] = h/2.f; 	//scale the viewport
    m[2][2] = depth/2.f;//scale the viewport
    return m;
}

void triangle(Vec3i t0, Vec3i t1, Vec3i t2, Vec2i uv0, Vec2i uv1, Vec2i uv2, TGAImage &image, float intensity, int *zbuffer) {
    if (t0.y==t1.y && t0.y==t2.y) return; // i dont care about degenerate triangles
    if (t0.y>t1.y) { std::swap(t0, t1); std::swap(uv0, uv1); }
    if (t0.y>t2.y) { std::swap(t0, t2); std::swap(uv0, uv2); }
    if (t1.y>t2.y) { std::swap(t1, t2); std::swap(uv1, uv2); }

    int total_height = t2.y-t0.y;
    for (int i=0; i<total_height; i++) {
        bool second_half = i>t1.y-t0.y || t1.y==t0.y;
        int segment_height = second_half ? t2.y-t1.y : t1.y-t0.y;
        float alpha = (float)i/total_height;
        float beta  = (float)(i-(second_half ? t1.y-t0.y : 0))/segment_height; // be careful: with above conditions no division by zero here
        Vec3i A   =               t0  + Vec3f(t2-t0  )*alpha;
        Vec3i B   = second_half ? t1  + Vec3f(t2-t1  )*beta : t0  + Vec3f(t1-t0  )*beta;
        Vec2i uvA =               uv0 +      (uv2-uv0)*alpha;
        Vec2i uvB = second_half ? uv1 +      (uv2-uv1)*beta : uv0 +      (uv1-uv0)*beta;
        if (A.x>B.x) { std::swap(A, B); std::swap(uvA, uvB); }
        for (int j=A.x; j<=B.x; j++) {
            float phi = B.x==A.x ? 1. : (float)(j-A.x)/(float)(B.x-A.x);
            Vec3i   P = Vec3f(A) + Vec3f(B-A)*phi;
            Vec2i uvP =     uvA +   (uvB-uvA)*phi;
            int idx = P.x+P.y*width;
            if (zbuffer[idx]<P.z) {
                zbuffer[idx] = P.z;
                TGAColor color = model->diffuse(uvP);
                image.set(P.x, P.y, TGAColor(color.r*intensity, color.g*intensity, color.b*intensity));
            }
        }
    }
}
*/


int main(int argc, char** argv)
{
	//terminal to go to build first then os type run > "cmake ../.. && make && ./rasterizer" in 1 command
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
	//model = new Model("../../models/african_head.obj");

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

	/*Obj Triangle Rendering NO DEPTH BUFFER
	for (int i=0; i<model->nfaces(); i++) { 
    std::vector<int> face = model->face(i); 
	Vec2i screen_coords[3]; 
	Vec3f world_coords[3];
		for (int j=0; j<3; j++) { 
			//Read the 3 verticies world cords from a face
			Vec3f world_coords_v = model->vert(face[j]);
			//(width & height /2) are used to center the image according to the resolution set
			screen_coords[j] = Vec2i((world_coords_v.x+1.) * width/2., (world_coords_v.y+1.) * height/2.); 
			//Vec2i above is just xy no z coords we have no depth buffer yet, thats why some faces are clipping this is just screen space.
			world_coords[j] = world_coords_v;
		}

		//in order to do lighting we need a normal vector ofc, to get this normal vector we need to do a cross product of 2 vectors on each face (the triangle)
		Vec3f normal = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);
		//ORDER OF CROSS PRODUCT MATTERS, if you get a negative normal vector then you need to swap the order of the cross product
		normal.normalize();


		
		//Classic Lighting method using Dot Product of the normal vector & the light direction vector
		float lightIntensity = normal*light_direction;

		//https://twitter.com/FreyaHolmer/status/1200807790580768768?lang=en dot product visualization by Freya Holmer
		//If the dot product is negative that means the 2 vectors angles are greater than 90 degrees apart else if they are less than 90 degrees apart then the dot product is positive & recieves light
		if(lightIntensity > 0)
		{
			TGAColor lightCol = TGAColor(lightIntensity*255,lightIntensity*255,lightIntensity*255, 255);
			BaryTriangle(screen_coords,image,lightCol);
		}
	}*/
	
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

	/*2D Mesh Scene Test to Understand Depth Buffer
	//https://github.com/ssloy/tinyrenderer/wiki/Lesson-3:-Hidden-faces-removal-(z-buffer) see original 2D/3D images here
	
	int yBuffer[width];
	for(int i = 0; i < width; i++)
	{	
		//initializes the whole array block to the negative min value which is probably -2147483648 or negative inf
		yBuffer[i] = std::numeric_limits<int>::min();
	}

	rasterYbuffer(Vec2i(20, 34),   Vec2i(744, 400), image, red,   yBuffer);
    rasterYbuffer(Vec2i(120, 434), Vec2i(444, 400), image, green, yBuffer);
	rasterYbuffer(Vec2i(330, 463), Vec2i(594, 200), image, blue,  yBuffer);

	
	// scene "2d mesh"
    line2p(Vec2i(20, 34),   Vec2i(744, 400), image, red);
    line2p(Vec2i(120, 434), Vec2i(444, 400), image, green);
    line2p(Vec2i(330, 463), Vec2i(594, 200), image, blue);

    // screen line
    line2p(Vec2i(10, 10), Vec2i(790, 10), image, white);
	*/

	/*Z Buffer implementation WITH Obj Triangle Rendering & Lighting 
	float *zbuffer = new float[width*height];
    for (int i=width*height; i--; zbuffer[i] = -std::numeric_limits<float>::max());

    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec3f pts[3];
		Vec3f world_coords[3];
        for (int i=0; i<3; i++){
			pts[i] = world2screen(model->vert(face[i]), width, height);
			world_coords[i] = (model->vert(face[i]));
		}
		Vec3f normal = ((world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]));
		normal.normalize();
		Vec3f lightDir = light_direction;
		lightDir.normalize();
		float dot01 = clampminmax(normal*lightDir,0.f,1.f);
		int lightIntensity = (int)clampminmax((dot01 * 255.f),0.f,255.f);
		triangle(pts, zbuffer, image, TGAColor(lightIntensity, lightIntensity, lightIntensity, 255));
		//triangle(pts, zbuffer, image, TGAColor(rand()%255, rand()%255, rand()%255, 255));
    }
	*/

	/*First Prespective Projection


	zbuffer = new int[width*height];
    for (int i=0; i<width*height; i++) {
    zbuffer[i] = std::numeric_limits<int>::min();
    }

    { // draw the model
        Matrix Projection = Matrix::identity(4);
        Matrix ViewPort   = viewport(width/8, height/8, width*3/4, height*3/4);
        Projection[3][2] = -1.f/camera.z;

        TGAImage image(width, height, TGAImage::RGB);
        for (int i=0; i<model->nfaces(); i++) {
            std::vector<int> face = model->face(i);
            Vec3i screen_coords[3];
            Vec3f world_coords[3];
            for (int j=0; j<3; j++) {
                Vec3f v = model->vert(face[j]);
                screen_coords[j] =  m2v(ViewPort*Projection*v2m(v));
                world_coords[j]  = v;
            }
            Vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);
            n.normalize();
            float intensity = n*light_direction;
            if (intensity>0) {
                Vec2i uv[3];
                for (int k=0; k<3; k++) {
                    uv[k] = model->uv(i, k);
                }
                triangle(screen_coords[0], screen_coords[1], screen_coords[2], uv[0], uv[1], uv[2], image, intensity, zbuffer);
            }
        }

		image.flip_vertically(); //origin at the left bottom corner of the image
		std::string rstr = std::to_string(run);
		std::string output = "../../images/output" + rstr + ".tga";

		image.write_tga_file(output.c_str());
    }


	
	{
	    // dump z-buffer (debugging purposes only)
        TGAImage zbimage(width, height, TGAImage::GRAYSCALE);
        for (int i=0; i<width; i++) {
            for (int j=0; j<height; j++) {
                zbimage.set(i, j, TGAColor(zbuffer[i+j*width], 1));
            }
        }
        zbimage.flip_vertically(); // i want to have the origin at the left bottom corner of the image
		std::string rstr = std::to_string(run);
		std::string output = "../../images/depth" + rstr + ".tga";
        zbimage.write_tga_file(output.c_str());
    }
    delete model;
    delete [] zbuffer;
    */
	
    /*First Shader & Model, View, Projection Transformations*/



	return 0;
}


