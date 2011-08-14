#include <cmath>
#include <iostream>
#include <vector>

#include "ppm.h"
#include "raytracer.h"
#include "utils.h"

int main() {
	std::cout << "Hello world" << std::endl;

    /*std::cout << "Generating random image" << std::endl;

    raytracer::PpmFile ppm(768, 1024);
    const raytracer::Color red(1, 0, 0);
    const raytracer::Color yellow(1, 1, 0);
    for (int i = 0; i < ppm.height(); ++i) {
      for (int j = 0; j < ppm.width(); ++j)
        ppm.SetPixel(i, j, i % 2 == 0 ? red : yellow);
    }

    ppm.WriteToFile("test");*/


    raytracer::Surface checkerboard;
    checkerboard.Diffuse = [](const raytracer::Vector3& pos) { 
      return (static_cast<int>(std::floor(pos.z) + std::floor(pos.x)) % 2 != 0) ? raytracer::Color(1, 1, 1) : raytracer::Color(0, 0, 0);
    };
    checkerboard.Specular = [](const raytracer::Vector3& pos) {
      return raytracer::Color(1, 1, 1);
    };
    checkerboard.Reflect = [](const raytracer::Vector3& pos) {
      return (static_cast<int>(std::floor(pos.z) + std::floor(pos.x)) % 2 != 0) ? 0.1 : 0.7;
    };
    checkerboard.roughness = 150;

    raytracer::Surface shiny;
    shiny.Diffuse = [](const raytracer::Vector3& pos) { 
      return raytracer::Color(1, 1, 1);
    };
    shiny.Specular = [](const raytracer::Vector3& pos) {
      return raytracer::Color(0.5, 0.5, 0.5);
    };
    shiny.Reflect = [](const raytracer::Vector3& pos) {
      return 0.6;
    };
    shiny.roughness = 50;

    std::vector<raytracer::SceneObject*> things;
    things.push_back(new raytracer::Plane(checkerboard, raytracer::Vector3(0, 1, 0), 0));
    things.push_back(new raytracer::Sphere(shiny, raytracer::Vector3(0, 1, 0), 1));
    things.push_back(new raytracer::Sphere(shiny, raytracer::Vector3(-1, 0.5, 1.5), 0.5));

    std::vector<raytracer::Light> lights;
    raytracer::Light light1(raytracer::Vector3(-2,2.5,0), raytracer::Color(.49, .07, .07));
    raytracer::Light light2(raytracer::Vector3(1.5,2.5,1.5), raytracer::Color(.07,.07,.49));
    raytracer::Light light3(raytracer::Vector3(1.5,2.5,-1.5), raytracer::Color(.07,.49,.071));
    raytracer::Light light4(raytracer::Vector3(0,3.5,0), raytracer::Color(.21,.21,.35));
    lights.push_back(light1);
    lights.push_back(light2);
    lights.push_back(light3);
    lights.push_back(light4);
    
    raytracer::Camera camera(raytracer::Vector3(3,2,4), raytracer::Vector3(-1,.5,0));

    raytracer::Scene default_scene = {things, lights, camera};
	
    raytracer::RayTracer r(600, 600);
    r.Render(default_scene);
    r.image_.WriteToFile("abcdefg");

	return 0;
}
