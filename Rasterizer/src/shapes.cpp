#include "shapes.h"
#include "tgaimage.h"
#include "geometry.h"

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
	//https://twitter.com/FreyaHolmer/status/1244407595059884033?lang=en for a nice visual of barycentric coordinates

	/*
	line2p(p0, p1, image, yellow);
    line2p(p1, p2, image, yellow);
    line2p(p2, p0, image, purple);
	*/
}
