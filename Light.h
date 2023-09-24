#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"

class Light {
   public:
    vec3 pos, color;
    float intensity;

    Light(vec3 pos, vec3 color, float intensity) : pos(pos), color(color), intensity(intensity) {}
};

#endif  // LIGHT_H
