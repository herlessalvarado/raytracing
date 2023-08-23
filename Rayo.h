#ifndef RAYO_H
#define RAYO_H

#include "vec3.h"
class Rayo {
 public:
  vec3 ori, dir;
  Rayo() {}
  Rayo(vec3 _ori) { ori = _ori; }
  Rayo(vec3 _ori, vec3 _dir) {
    ori = _ori;
    dir = _dir;
  }
};

#endif  // RAYO_H
