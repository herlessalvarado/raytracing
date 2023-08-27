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

void Camara::renderizar(Light& light) {
  Ray ray;
  ray.ori = eye;
  vec3 dir;

  pImg = new CImg<BYTE>(w, h, 1, 3);
  CImgDisplay dis_img(
      (*pImg), "Imagen RayTracing en Perspectiva desde una Camara Pinhole");

  Sphere sphere(vec3(2, 0, 0), 8, vec3(0, 0, 1));
  vec3 color;
  float t;
  vec3 Pi, N;
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      dir = ze * (-f) + ye * a * (y / h - 0.5) + xe * b * (x / w - 0.5);
      dir.normalize();
      ray.dir = dir;
      color.set(0, 0, 0);
      // todos los objects con el t mas cercano
      if (sphere.intersect(ray, t, Pi, N)) {
        // color = sphere.color;
        vec3 ambiente = light.color * 0.1;
        vec3 L = light.pos - Pi;
        L.normalize();
        float difuso = L.punto(N);
        vec3 difusa = light.color * 0.8 * max(0.0f, difuso);
        vec3 R = 2.0f * difuso * N - L;
        vec3 V = -dir;
        vec3 especular = light.color * (0.9 * (pow(max(0.0f, R.punto(V)), 32)));
        color = sphere.color * (difusa + ambiente + especular);
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
