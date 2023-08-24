#ifndef LUZ_H
#define LUZ_H

#include "vec3.h"

class Luz {
 public:
  vec3 pos, color;
  Luz(vec3 pos, vec3 color) : pos(pos), color(color) {}
};

#endif  // LUZ_H
