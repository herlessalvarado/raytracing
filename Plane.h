#ifndef PLANE_H
#define PLANE_H

#include "Object.h"

class Plane : public Object {
   public:
    vec3 point, normal;

    Plane(vec3 point, vec3 normal, vec3 col, std::string type) : point{point}, normal{normal}, Object(col, type) {
        ka = 0.1;
        kd = 0.8;
        ks = 0.9;
        shininess = 32.0;
    };

    bool intersect(Ray ray, float &t, vec3 &Pi, vec3 &N) override {
        vec3 d = ray.dir;
        vec3 o = ray.ori;
        float divider = d.dot(normal);
        if (divider == 0) return false;
        t = ((point - o).dot(normal)) / divider;
        if (t <= 0) {
            return false;
        }
        Pi = o + (d * t);  // punto de interseccion
        N = normal;        // normal
        return true;
    }
};

#endif  // PLANE_H
