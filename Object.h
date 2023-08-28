#ifndef OBJECT_H
#define OBJECT_H

#include "Ray.h"
#include "vec3.h"

class Object {
   public:
    vec3 color;
    float ka, kd, ks, shininess;

    Object(vec3 col) : color{col} {}

    virtual bool intersect(Ray ray, float &t, vec3 &Pi, vec3 &N) = 0;
};

class Sphere : public Object {
   public:
    vec3 center;
    float radius;

    Sphere(vec3 cen, float r, vec3 col) : center{cen}, radius{r}, Object(col) {
        ka = 0.1;
        kd = 0.8;
        ks = 0.9;
        shininess = 32.0;
    };

    bool intersect(Ray ray, float &t, vec3 &Pi, vec3 &N) override {
        vec3 d = ray.dir;
        vec3 o = ray.ori;
        float a = d.dot(d);
        float b = 2 * d.dot(o - center);
        float c = (o - center).dot(o - center) - radius * radius;
        float D = b * b - 4 * a * c;
        if (D <= 0) {
            return false;
        }
        float t1 = (-b + sqrt(D)) / (2 * a);
        float t2 = (-b - sqrt(D)) / (2 * a);
        t = std::min(t1, t2);
        if (t <= 0) {
            return false;
        }
        Pi = o + (d * t);   // punto de interseccion
        N = (Pi - center);  // normal
        N.normalize();
        return true;
    }
};

#endif  // OBJECT_H
