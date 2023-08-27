#include <iostream>

#include "Camara.h"
#include "Light.h"
#include "Mundo.h"
#include "Object.h"
#include "vec3.h"

int main() {
  Camara camara;
  Light light(vec3(400, 300, 0), vec3(1, 1, 1));
  Mundo mundo(camara, light);
  mundo.camara.configurar(3, 60, 800, 600, vec3(0, 5, 50), vec3(0, 0, 0),
                          vec3(0, 1, 0));
  mundo.camara.renderizar(mundo.light);

  return 0;
};
