#ifndef MUNDO_H
#define MUNDO_H

#include "Camara.h"
#include "Light.h"
#include "Object.h"

class Mundo {
 public:
  Camara camara;
  Light light;
  std::vector<Object> objects;

  Mundo(const Camara& camara, const Light& light)
      : camara(camara), light(light){};

  void addObject(const Object& object) { objects.push_back(object); }
};

#endif  // MUNDO_H
