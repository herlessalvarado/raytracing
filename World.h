#ifndef WORLD_H
#define WORLD_H

#include "Camera.h"
#include "Light.h"
#include "Object.h"

class World {
   public:
    Camera camera;
    Light light;
    std::vector<Object*> objects;

    World(const Camera& camera, const Light& light)
        : camera(camera), light(light){};

    void addObject(Object* object) { objects.push_back(object); }
};

#endif  // WORLD_H
