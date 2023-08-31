#ifndef OBJECT_H
#define OBJECT_H

#include "Ray.h"
#include "vec3.h"

class Sphere;
class Plane;
class Object {
   public:
    vec3 color;
    float ka, kd, ks, shininess;

    Object(vec3 col) : color{col} {}

    virtual bool intersect(Ray ray, float &t, vec3 &Pi, vec3 &N) = 0;
};

#include "Plane.h"
#include "Sphere.h"

#endif  // OBJECT_H
