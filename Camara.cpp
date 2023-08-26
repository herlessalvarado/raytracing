#include "Camara.h"

#include <iostream>

using namespace std;

void Camara::configurar(float _near, float fov, int ancho, int alto,
                        vec3 pos_eye, vec3 center, vec3 up) {
  f = _near;
  w = ancho;
  h = alto;
  a = 2 * f * tan(fov * M_PI / 360);
  b = w / h * a;
  eye = pos_eye;
  ze = eye - center;
  ze.normalize();
  xe = up.cruz(ze);
  xe.normalize();
  ye = ze.cruz(xe);
}

void Camara::renderizar(Luz& luz) {
  Rayo rayo;
  rayo.ori = eye;
  vec3 dir;

  pImg = new CImg<BYTE>(w, h, 1, 3);
  CImgDisplay dis_img(
      (*pImg), "Imagen RayTracing en Perspectiva desde una Camara Pinhole");

  Esfera esf(vec3(2, 0, 0), 8, vec3(0, 0, 1));
  vec3 color;
  float t;
  vec3 Pi, N;
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      dir = ze * (-f) + ye * a * (y / h - 0.5) + xe * b * (x / w - 0.5);
      dir.normalize();
      rayo.dir = dir;
      color.set(0, 0, 0);
      // todos los objetos con el t mas cercano
      if (esf.intersectar(rayo, t, Pi, N)) {
        // color = esf.color;
        vec3 ambiente = luz.color * 0.2;
        color = esf.color * ambiente;
      }
      (*pImg)(x, h - 1 - y, 0) = (BYTE)(color.x * 255);
      (*pImg)(x, h - 1 - y, 1) = (BYTE)(color.y * 255);
      (*pImg)(x, h - 1 - y, 2) = (BYTE)(color.z * 255);
    }
  }
  dis_img.render((*pImg));
  dis_img.paint();
  string nombre_archivo = "imagen" + to_string(1) + ".bmp";
  pImg->save(nombre_archivo.c_str());
  while (!dis_img.is_closed()) {
    dis_img.wait();
  }
}
