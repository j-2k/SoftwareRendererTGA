// JumaGFX_CMake.cpp : Defines the entry point for the application.
//

#include "JumaGFX_CMake.h"
#include <iostream>
using namespace std;

int main()
{
    // Image
    int image_width = 513;
    int image_height = 513;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
	return 0;
}