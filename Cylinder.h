#ifndef CYLINDER_H
#define CYLINDER_H

#include "Object.h"
#include "iostream"

class Cylinder : public Object {
   public:
    vec3 top, bottom;
    float radius;

    Cylinder(vec3 top, vec3 bottom, float r, vec3 col, std::string type) : top{top}, bottom{bottom}, radius{r}, Object(col, type) {
        if (type == "glass") kr = 1, ior = 1.5;
        if (type == "air") ior = 1;
        if (type == "water") ior = 1.33;
        if (type == "diamond") ior = 1.8;
        ka = 0.05;
        kd = 0.15;
        ks = 0.95;
        shininess = 150;
    };

    float sign(float x) {
        if (x > 0.0) {
            return 1.0;
        } else if (x < 0.0) {
            return -1.0;
        } else {
            return 0.0;
        }
    }

    bool intersect(Ray ray, float &t, vec3 &Pi, vec3 &N) override {
        vec3 ba = bottom - top;
        vec3 oc = ray.ori - top;
        float baba = ba.dot(ba);
        float bard = ba.dot(ray.dir);
        float baoc = ba.dot(oc);
        float k2 = baba - bard * bard;
        float k1 = baba * oc.dot(ray.dir) - baoc * bard;
        float k0 = baba * oc.dot(oc) - baoc * baoc - radius * radius * baba;
        float h = k1 * k1 - k2 * k0;
        if (h < 0.0) return false;  // no intersection
        h = std::sqrt(h);
        t = (-k1 - h) / k2;
        // body
        float y = baoc + t * bard;
        if (y > 0.0 && y < baba) {
            Pi = (oc + t * ray.dir - ba * y / baba) / radius;
            N = this->normal(Pi);
            return true;
        }
        // caps
        t = (((y < 0.0) ? 0.0 : baba) - baoc) / bard;
        if (std::abs(k1 + k2 * t) < h) {
            Pi = ba * this->sign(y) / std::sqrt(baba);
            N = this->normal(Pi);
            return true;
        }
        return false;  // no intersection
    }

    vec3 normal(vec3 p) {
        vec3 pa = p - top;
        vec3 ba = bottom - top;
        float baba = ba.dot(ba);
        float paba = pa.dot(ba);
        float h = paba / baba;
        return (pa - ba * h) / radius;
    }
};

#endif  // CYLINDER_H
