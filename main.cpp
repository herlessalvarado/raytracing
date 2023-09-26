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

void setupObjects(World &world) {
    Plane *wall = new Plane(vec3(0, 0, -60), vec3(0, 0, 1), vec3(0.82, 0.82, 0.82), "concrete", false);
    Plane *table = new Plane(vec3(0, -30, 0), vec3(0, 1, 0), vec3(0.5451, 0.2706, 0.0745), "concrete", false);
    // Cylinder *bottle = new Cylinder(vec3(0, 20, 0), vec3(0, -30, 0), 20, vec3(0, 0.6, 0.6), "glass");
    // Cylinder *airBottle = new Cylinder(vec3(0, 20, 20), vec3(0, -30, 20), 18, vec3(1, 0, 0), "glass");
    Sphere *firefly1 = new Sphere(vec3(0, 0, 3), 1, vec3(1, 1, 0), "insect", true);
    Sphere *firefly2 = new Sphere(vec3(-40, 10, 10), 1, vec3(1, 1, 0), "insect", true);
    Sphere *firefly3 = new Sphere(vec3(40, 10, 10), 1, vec3(1, 1, 0), "insect", true);
    world.addObject(wall);
    world.addObject(table);
    // world.addObject(bottle);
    // world.addObject(airBottle);
    world.addObject(firefly1);
    world.addObject(firefly2);
    world.addObject(firefly3);
}

void setupSphereLights(World &world) {
    vector<Object *> objects = world.objects;
    for (auto object : objects) {
        Sphere *sphere = dynamic_cast<Sphere *>(object);
        if (sphere != nullptr && sphere->isLight && sphere->type == "insect") {
            Light light(sphere->center, sphere->color, 0.1);
            world.addLight(light);
        }
    }
    return;
}

int main() {
    Camera camera;
    World world(camera);
    int y = 0;
    int z = 0;
    for (int i = 0; i < 720; i++) {
        world.lights.clear();
        world.objects.clear();
        if (i >= 240 && i < 480) {
            world.camera.configure(3, 60, 800, 600, vec3(y++, 0, 100), vec3(0, 0, 0),
                                   vec3(0, 1, 0));
        } else if (i >= 480) {
            world.camera.configure(3, 60, 800, 600, vec3(y, z++, 100), vec3(0, 0, 0),
                                   vec3(0, 1, 0));
        } else {
            world.camera.configure(3, 60, 800, 600, vec3(0, 0, 100), vec3(0, 0, 0),
                                   vec3(0, 1, 0));
        }
        // Light light(vec3(-200, 0, 0), vec3(1, 1, 1), 1);
        // world.addLight(light);
        Plane *wall = new Plane(vec3(0, 0, -60), vec3(0, 0, 1), vec3(0.82, 0.82, 0.82), "concrete", false);
        Plane *table = new Plane(vec3(0, -30, 0), vec3(0, 1, 0), vec3(0.5451, 0.2706, 0.0745), "concrete");
        Cylinder *bottle = new Cylinder(vec3(0, 30, 20), vec3(0, -30, 20), 20, vec3(0, 0.6, 0.6), "glass");
        float angle1 = i * 0.1;
        float angle2 = i * 0.2;
        float angle3 = i * 0.15;
        Sphere *firefly1 = new Sphere(vec3(10 * cos(angle1), 10 * sin(angle1), -40), 1, vec3(1, 1, 0), "insect", true);
        Sphere *firefly2 = new Sphere(vec3(10 * cos(angle2), 10 * sin(angle2), -40), 1, vec3(1, 1, 0), "insect", true);
        Sphere *firefly3 = new Sphere(vec3(10 * cos(angle3), 10 * sin(angle3), -40), 1, vec3(1, 1, 0), "insect", true);
        Sphere *sphere = new Sphere(vec3(-40, 0, 20), 10, vec3(0, 1, 0), "mirror", false);
        Sphere *sphere2 = new Sphere(vec3(40, 0, 20), 10, vec3(0, 1, 0), "mirror", false);
        world.addObject(wall);
        world.addObject(table);
        world.addObject(bottle);
        world.addObject(firefly1);
        world.addObject(firefly2);
        world.addObject(firefly3);
        world.addObject(sphere);
        world.addObject(sphere2);
        setupSphereLights(world);
        world.camera.render(world.lights, world.objects, i);
    }

    return 0;
};
