#include "shapes.h"
#include "tgaimage.h"
#include "geometry.h"
#include <vector> 
#include <iostream> 
#include <cmath>
#include <cstdlib>
#include <limits>

//Bresenham Line Algorithm
void line2pOld(int x1,int y1, int x2, int y2, TGAImage &image, TGAColor color)
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

//Bresenham Line Algorithm Overload with ints
void line2p(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    bool steep = false;
    if (std::abs(x0-x1)<std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0>x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    for (int x=x0; x<=x1; x++) {
        float t = (x-x0)/(float)(x1-x0);
        int y = y0*(1.-t) + y1*t;
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
    }
}


//Triangle Method
void LineSweepTriangle(Vec2i p0, Vec2i p1, Vec2i p2, TGAImage &image, TGAColor color) {


    //Sort all 3 points from Y axis top to down
	if(p0.y > p1.y) std::swap(p0,p1);
	if(p0.y > p2.y) std::swap(p0,p2);
	if(p1.y > p2.y) std::swap(p1,p2);
	//Now Triangle is sorted from top to bottom (p0,p1,p2) ... After vertical image flip is (p2,p1,p0)
	//						.p0								.p2
	//						|\								|\
	//						| \								| \
	//						|__\. p1	> VERT FLIP >		|__\. p1
	//						| /								| /
	//						|/								|/
	//						.p2								.p0

	//DIVIDE LOWER BOUND OF TRIANGLE INTO 2 TRIANGLES // refer to unflipped img
	int triangleHeight = p2.y - p0.y;
	for(int y = p0.y; y <=p1.y; y++)
	{//each iteration will step DOWN once (y++) into the triangle and then process the whole line from left to right and then repeat.
		int topSectionHeight = p1.y - p0.y + 1;//top mid section
		float normalizedTriHeight = (float)(y - p0.y) / triangleHeight; 		//get interpolation/magnitude value for the height of the whole triangle
		float normalizedTopSecHeight = (float)(y - p0.y) / topSectionHeight;	//get interpolation/magnitude value for the height of the top section

		Vec2i lerpTH = p0 + (p2 - p0) * normalizedTriHeight;		//getting a vector that points to p2 & is then scaled by the interpolated value/magnitude 
		Vec2i lerpTSH = p0 + (p1 - p0) * normalizedTopSecHeight;	//getting a vector that points to p1 & is then scaled by the interpolated value/magnitude 

		if(lerpTH.x >  lerpTSH.x) std::swap(lerpTH,lerpTSH);	

		//Now process the protuded vectors from the position of their x values from left to right
		//beware of casting to int when using float values
		for(int x = lerpTH.x; x <= lerpTSH.x; x++)//coloring left to right of each line segment
		{
			image.set(x,y,color);
		}
	}

	//duplicated the above code to just color the bottom
	for(int y = p1.y; y <=p2.y; y++)
	{//each iteration will step DOWN once (y++) into the triangle and then process the whole line from left to right and then repeat.
		int botSectionHeight = p2.y - p1.y + 1;//bottom mid section
		float normalizedTriHeight = (float)(y - p0.y) / (float)triangleHeight; 		//get interpolation/magnitude value for the height of the whole triangle
		float normalizedBotSecHeight = (float)(y - p1.y) / (float)botSectionHeight;	//get interpolation/magnitude value for the height of the top section

		Vec2i lerpTH = p0 + (p2 - p0) * normalizedTriHeight;		//getting a vector that points to p2 & is then scaled by the interpolated value/magnitude 
		Vec2i lerpTSH = p1 + (p2 - p1) * normalizedBotSecHeight;	//getting a vector that points to p1 & is then scaled by the interpolated value/magnitude 

		if(lerpTH.x >  lerpTSH.x) std::swap(lerpTH,lerpTSH);	

		//Now process the protuded vectors from the position of their x values from left to right
		//beware of casting to int when using float values
		for(int x = lerpTH.x; x <= lerpTSH.x; x++)//coloring left to right of each line segment
		{
			image.set(x,y,color);
		}
	}

	//I wont bother to combine these like ssloy does since we are just going to do barycentric coordinates anyways which will be much more efficient

	/*
	line2p(p0, p1, image, yellow);
    line2p(p1, p2, image, yellow);
    line2p(p2, p0, image, purple);
	*/
}
/*
void BaryTriangle(Vec2i *pts, TGAImage &image, TGAColor color) { 
	//Bounding Box Initialization
    Vec2i bboxmin(image.get_width()-1,  image.get_height()-1); 
    Vec2i bboxmax(0, 0); 
    Vec2i clamp(image.get_width()-1, image.get_height()-1); 

	//Bounding Box Calculation
    for (int i=0; i<3; i++) { 
        bboxmin.x = std::max(0, std::min(bboxmin.x, pts[i].x));
	bboxmin.y = std::max(0, std::min(bboxmin.y, pts[i].y));

	bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pts[i].x));
	bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pts[i].y));
    } 

	//Loop through the bounding box containing the triangle
    Vec2i P; 
    for (P.x=bboxmin.x; P.x<=bboxmax.x; P.x++) { 
        for (P.y=bboxmin.y; P.y<=bboxmax.y; P.y++) { 
			//If the point in the bounding box resides in the triangle then color it
            Vec3f bc_screen  = barycentric(pts, P); 
            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue; 
			//TGAColor color = TGAColor(rand() % 255, rand() % 255, rand() % 255, 255); //random colors
            image.set(P.x, P.y, color); 
        } 
    } 
} */

void triangle(Vec3f *pts, float *zbuffer, TGAImage &image, TGAColor color) {
	//FINDING THE BOUNDING BOX OF THE TRIANGLE
    Vec2f bboxmin( std::numeric_limits<float>::max(),  std::numeric_limits<float>::max());
    Vec2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
    Vec2f clamp(image.get_width()-1, image.get_height()-1);
    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++) {
            bboxmin[j] = std::max(0.f,      std::min(bboxmin[j], pts[i][j]));
            bboxmax[j] = std::min(clamp[j], std::max(bboxmax[j], pts[i][j]));
        }
    }

	//LOOP THROUGH THE BOUNDING BOX CONTAINING THE TRIANGLE
    Vec3f P;
    for (P.x=bboxmin.x; P.x <= bboxmax.x; P.x++) {
        for (P.y=bboxmin.y; P.y <= bboxmax.y; P.y++) {

            Vec3f bc_screen  = barycentric3D(pts[0], pts[1], pts[2], P);
            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue;//if the point is outside the triangle then skip it


            P.z = 0;
            for (int i=0; i<3; i++) {
				P.z += pts[i][2] *bc_screen[i];
				//bc_screen[i] is the weight of the vertex
				//pts[i][2] is the z value of the vertex
			}

			if (zbuffer[int(P.x+P.y*image.get_width())] < P.z) {
				zbuffer[int(P.x+P.y*image.get_width())] = P.z;
				image.set(P.x, P.y, color);//P.z stores depth
			}
        }
    }
}

Vec3f world2screen(Vec3f v, int width, int height) {
    return Vec3f(int((v.x+1.)*width/2.+.5), int((v.y+1.)*height/2.+.5), v.z);
}

float clampminmax(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}

//https://twitter.com/FreyaHolmer/status/1244407595059884033?lang=en for a nice visual of barycentric coordinates
//P is the point we are testing in the bounding box surrounding the triangle, pts are the 3 points of the triangle
/*Vec3f barycentric(Vec2i *pts, Vec2i P)
{
	//Cross Product (this line is hard to understand)
	Vec3f cx = cross(pts[2].x-pts[0].x, pts[1].x-pts[0].x, pts[0].x-P.x)Vec3f(pts[2].y-pts[0].y, pts[1].y-pts[0].y, pts[0].y-P.y);
	
	//Handle case for Degenerate Triangle
	if(std::abs(cx.z) < 1) return Vec3f(-1,1,1);
	//Return a negative to indicate that the point is outside the triangle & will be discarded by mr rasterizer

	//Return Barycentric Coordinates
	return Vec3f(1.f-(cx.x+cx.y)/cx.z, cx.y/cx.z, cx.x/cx.z);
}*/

Vec3f barycentric3D(Vec3f A, Vec3f B, Vec3f C, Vec3f P) {
    Vec3f s[2];
    for (int i=2; i--; ) {
        s[i][0] = C[i]-A[i];
        s[i][1] = B[i]-A[i];
        s[i][2] = A[i]-P[i];
    }
    Vec3f u = (s[0]^s[1]);
    if (std::abs(u[2])>1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
        return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);
    return Vec3f(-1,1,1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}

void rasterYbuffer(Vec2i p0, Vec2i p1, TGAImage &image, TGAColor color, int ybuffer[]) {
    if (p0.x>p1.x) {
        std::swap(p0, p1);
    }

    for (int x=p0.x; x<=p1.x; x++) {
        float t = (x-p0.x)/(float)(p1.x-p0.x);	//x "forward lerp stepper", literally lerp if t is 0 return p0 if t is 1 return p1, anything in between, it will linearly interpolate over p0 to p1
        int y = p0.y*(1.-t) + p1.y*t;			//get the y value at the current x position by lerping between p0 & p1
        if (ybuffer[x]<y) {						//replace the buffer value with the new y value if the new y value is greater than the current y value in the buffer
			ybuffer[x] = y;
			
			//screen
			for (size_t i = 0; i < image.get_height(); i++)//image.get_height()/2
			{
				image.set(x, i, color);
			}

			//ybuffer
			/*
			for (size_t i = 0; i < image.get_height()/2; i++)
			{
				float m = ybuffer[x]/x;
				image.set(x, i, TGAColor(m*255,m*255,m*255,255));
			}*/
			
			std::cout << ybuffer[x] << std::endl;
        }
    }
}
