#include <iostream>
#include <random>

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
    Camera camera;
    Light light(vec3(0, 600, 100), vec3(1, 1, 1));
    World world(camera, light);
    world.camera.configure(3, 60, 800, 600, vec3(0, 0, 100), vec3(0, 0, 0),
                           vec3(0, 1, 0));
    Plane *plane = new Plane(vec3(0, -10, -60), vec3(0, 1, 0), vec3(1, 1, 0), "concrete");
    world.addObject(plane);
    // for (int i = 0; i < 50; i++) {
    //     Sphere *sphere = new Sphere(vec3(randomFloat(-60, 60), randomFloat(10, 40), randomFloat(1, 10)), randomFloat(1, 10), vec3(randomFloat(0, 1), randomFloat(0, 1), randomFloat(0, 1)), "glass");
    //     world.addObject(sphere);
    // }
    Sphere *sphere = new Sphere(vec3(-20, 10, 1), 15, vec3(0, 0, 1), "glass");
    world.addObject(sphere);
    Sphere *sphere2 = new Sphere(vec3(20, 15, 1), 15, vec3(1, 0, 1), "glass");
    world.addObject(sphere2);
    world.camera.render(world.light, world.objects);

    return 0;
};
