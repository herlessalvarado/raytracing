#ifndef OBJETO_H
#define OBJETO_H

#include "Ray.h"
#include "vec3.h"

class Objeto {
 public:
  vec3 color;
  Objeto(vec3 col) : color{col} {}

  // virtual bool intersectar(Ray ray, float &t) = 0;
};

class Esfera : public Objeto {
 public:
  vec3 centro;
  float radio;

  Esfera(vec3 cen, float r, vec3 col) : centro{cen}, radio{r}, Objeto(col){};
  bool intersectar(Ray ray, float &t, vec3 &Pi, vec3 &N) {
    vec3 d = ray.dir;
    vec3 o = ray.ori;
    float a = d.punto(d);
    float b = 2 * d.punto(o - centro);
    float c = (o - centro).punto(o - centro) - radio * radio;
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
    N = (Pi - centro);  // normal
    N.normalize();
    return true;
  }
};

#endif  // OBJETO_H
