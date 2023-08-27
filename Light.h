#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"

class Light {
 public:
  vec3 pos, color;
  Light(vec3 pos, vec3 color) : pos(pos), color(color) {}
};

#endif  // LIGHT_H
