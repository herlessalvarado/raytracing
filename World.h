#ifndef WORLD_H
#define WORLD_H

#include "Camera.h"
#include "Light.h"
#include "Object.h"

class World {
   public:
    Camera camera;
    std::vector<Light> lights;
    std::vector<Object*> objects;

    World(const Camera& camera)
        : camera(camera){};

    void addObject(Object* object) { objects.push_back(object); }

    void addLight(Light light) { lights.push_back(light); }
};

#endif  // WORLD_H
