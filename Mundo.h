#ifndef MUNDO_H
#define MUNDO_H

#include "Camera.h"
#include "Light.h"
#include "Object.h"

class Mundo {
 public:
  Camera camera;
  Light light;
  std::vector<Object> objects;

  Mundo(const Camera& camera, const Light& light)
      : camera(camera), light(light){};

  void addObject(const Object& object) { objects.push_back(object); }
};

#endif  // MUNDO_H
