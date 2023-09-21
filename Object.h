#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include "Ray.h"
#include "vec3.h"

class Sphere;
class Plane;
class Cylinder;
class Object {
   public:
    vec3 color;
    // ka = ambient coefficient
    // kd = diffuse coefficient
    // ks = specular coefficient
    // kr = reflective coefficient
    // ior = index of refraction
    // shininess = shininess
    float ka, kd, ks, kr = 0, ior = 0, shininess;
    std::string type;

    Object(vec3 col, std::string type) : color{col}, type{type} {}

    virtual bool intersect(Ray ray, float &t, vec3 &Pi, vec3 &N) = 0;

    bool isReflective() {
        return type == "mirror";
    };

    bool isReflectiveAndRefractive() {
        return ior != 0;
    };
};

#include "Cylinder.h"
#include "Plane.h"
#include "Sphere.h"

#endif  // OBJECT_H
