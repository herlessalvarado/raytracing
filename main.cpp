#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <string>

#include "Camera.h"
#include "Light.h"
#include "Object.h"
#include "World.h"
#include "vec3.h"

float randomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

int main() {
    std::srand(std::time(NULL));
    std::vector<std::string> types;
    types.push_back("glass");
    types.push_back("concrete");
    Camera camera;
    Light light(vec3(40, 100, 40), vec3(1, 1, 1));
    World world(camera, light);
    world.camera.configure(3, 60, 800, 600, vec3(0, 0, 100), vec3(0, 0, 0),
                           vec3(0, 1, 0));
    Plane *wall = new Plane(vec3(0, 0, -60), vec3(0, 0, 1), vec3(1, 1, 1), "concrete");
    world.addObject(wall);
    Plane *table = new Plane(vec3(0, -30, 0), vec3(0, 1, 0), vec3(1, 1, 0), "concrete");
    world.addObject(table);
    Cylinder *cylinder = new Cylinder(vec3(0, 10, 0), vec3(0, -30, 0), 20, vec3(0, 0.6, 0.6), "glass");
    world.addObject(cylinder);
    // for (int i = 0; i < 50; i++) {
    //     int randomIndex = rand() % 5;
    //     Sphere *sphere = new Sphere(vec3(randomFloat(-60, 60), randomFloat(5, 50), randomFloat(1, 10)), randomFloat(1, 10), vec3(randomFloat(0, 1), randomFloat(0, 1), randomFloat(0, 1)), types[randomIndex]);
    //     world.addObject(sphere);
    // }
     Sphere *sphere = new Sphere(vec3(-30, 0, 6), 4, vec3(0, 0, 1), "concrete");
     world.addObject(sphere);
     Sphere *sphere2 = new Sphere(vec3(-45, -10, 10), 4, vec3(1, 0, 0), "concrete");
     world.addObject(sphere2);
    world.camera.render(world.light, world.objects);

    return 0;
};
