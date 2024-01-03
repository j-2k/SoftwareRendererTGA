#include <iostream>
#include "tgaimage.h"
#include "extra/runfile.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int, char**){
    FileRunIndex();

    TGAImage image(100, 100, TGAImage::RGB);
	image.set(52, 41, red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("../images/output.tga");
	return 0;
}

