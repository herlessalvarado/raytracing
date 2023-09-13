#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include "Ray.h"
#include "vec3.h"

class Sphere;
class Plane;
class Object {
   public:
    vec3 color;
    float ka, kd, ks, kr = 0, shininess;
    std::string type;

    Object(vec3 col, std::string type) : color{col}, type{type} {}

    virtual bool intersect(Ray ray, float &t, vec3 &Pi, vec3 &N) = 0;

    bool isReflective() {
        return type == "glass";
    };
};

#include "Plane.h"
#include "Sphere.h"

#endif  // OBJECT_H
