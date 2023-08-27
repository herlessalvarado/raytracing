#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
 public:
  vec3 ori, dir;

  Ray() {}

  Ray(vec3 _ori) { ori = _ori; }

  Ray(vec3 _ori, vec3 _dir) {
    ori = _ori;
    dir = _dir;
  }
};

#endif  // RAY_H
