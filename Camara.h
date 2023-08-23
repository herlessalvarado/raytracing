#ifndef CAMARA_H
#define CAMARA_H

#include <vector>

#include "CImg.h"
#include "Objeto.h"
#include "Rayo.h"
#include "vec3.h"

using namespace std;
using namespace cimg_library;
typedef unsigned char BYTE;

class Camara {
  vec3 eye, xe, ye, ze;
  float f, a, b, w, h;
  CImg<BYTE> *pImg;

 public:
  Camara() {}
  void configurar(float _near, float fov, int ancho, int alto, vec3 pos_eye,
                  vec3 center, vec3 up);
  void renderizar();
};

#endif  // CAMARA_H
