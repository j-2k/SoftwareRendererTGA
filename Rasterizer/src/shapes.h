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
Vec3i barycentric(Vec2i p0, Vec2i p1, Vec2i p2, Vec2i p);