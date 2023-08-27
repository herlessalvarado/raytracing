#ifndef MUNDO_H
#define MUNDO_H

#include "Camara.h"
#include "Light.h"
#include "Objeto.h"

class Mundo {
 public:
  Camara camara;
  Light light;
  std::vector<Objeto> objetos;

  Mundo(const Camara& camara, const Light& light) : camara(camara), light(light){};

  void añadirObjeto(const Objeto& objeto) { objetos.push_back(objeto); }
};

#endif  // MUNDO_H
