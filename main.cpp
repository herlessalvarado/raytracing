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
    Light light(vec3(400, 300, 0), vec3(1, 1, 1));
    World world(camera, light);
    world.camera.configure(3, 60, 800, 600, vec3(0, 0, 100), vec3(0, 0, 0),
                           vec3(0, 1, 0));
    for (int i = 0; i < 50; i++) {
        Sphere *sphere = new Sphere(vec3(randomFloat(-60, 60), randomFloat(-50, 50), 0), randomFloat(1, 5), vec3(0, 0, 1));
        world.addObject(sphere);
    }
    world.camera.render(world.light, world.objects);

    return 0;
};
