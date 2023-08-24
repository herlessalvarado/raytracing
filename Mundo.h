#ifndef MUNDO_H
#define MUNDO_H

#include "Camara.h"
#include "Luz.h"
#include "Objeto.h"

class Mundo {
 public:
  Camara camara;
  Luz luz;
  std::vector<Objeto> objetos;

  Mundo(const Camara& camara, const Luz& luz) : camara(camara), luz(luz){};

  void añadirObjeto(const Objeto& objeto) { objetos.push_back(objeto); }
};

#endif  // MUNDO_H
