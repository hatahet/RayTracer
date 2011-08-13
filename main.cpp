#include <iostream>

#include "ppm.h"

int main() {
	std::cout << "Hello world" << std::endl;

    std::cout << "Generating random image" << std::endl;

    raytracer::PpmFile ppm(768, 1024);
    const raytracer::Color red(255, 0, 0);
    const raytracer::Color yellow(255, 255, 0);
    for (int i = 0; i < ppm.height(); ++i) {
      for (int j = 0; j < ppm.width(); ++j)
        ppm.SetPixel(i, j, i % 2 == 0 ? red : yellow);
    }

    ppm.WriteToFile("test");

	
	return 0;
}
