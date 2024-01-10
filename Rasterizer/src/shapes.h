#include "tgaimage.h"
#include "geometry.h"

//Bresenham Line Algorithm
void line2p(int x1,int y1, int x2, int y2, TGAImage &image, TGAColor color);

//Bresenham Line Algorithm Overload with Vec2i
void line2p(Vec2i p0, Vec2i p1, TGAImage &image, TGAColor color);

//Triangle Method
void triangle(Vec2i p0, Vec2i p1, Vec2i p2, TGAImage &image, TGAColor color);

//Barycentric Coordinates
//Watch these https://www.youtube.com/watch?v=ngoZZkMuCOM by Brendan Galea, https://www.youtube.com/watch?v=HYAgJN3x4GA by Sebastian Lague
Vec3f barycentric(Vec2i *pts, Vec2i P);
/* AI explanation of barycentric coordinates
This function calculates the barycentric coordinates of a point P with respect to a triangle defined by points pts[0], pts[1], and pts[2].
Here's a breakdown of the code:
Vec3f u = Vec3f(pts[2][0]-pts[0][0], pts[1][0]-pts[0][0], pts[0][0]-P[0])^Vec3f(pts[2][1]-pts[0][1], pts[1][1]-pts[0][1], pts[0][1]-P[1]);
This line calculates the cross product of two vectors. The vectors are defined by the differences in the x and y coordinates of the triangle's vertices and point P. The result is a new vector u in 3D space.

if (std::abs(u.z)<1) return Vec3f(-1,1,1);
This line checks if the z-coordinate of the vector u is close to zero (indicating that the triangle is degenerate 
or the point lies on the plane of the triangle). If it is, the function returns a vector with negative coordinates as a flag.

return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);
This line calculates the barycentric coordinates of the point P with respect to the triangle. The barycentric coordinates are returned as a Vec3f (a 3D vector), 
where each component of the vector represents the weight of the corresponding vertex of the triangle.

In barycentric coordinates, a point inside a triangle can be represented as a weighted sum of the triangle's vertices.
The weights (or coordinates) always sum to 1, and each one ranges from 0 to 1. If a weight is 0, the point lies on the opposite side of the corresponding vertex.
If a weight is 1, the point coincides with that vertex.
*/