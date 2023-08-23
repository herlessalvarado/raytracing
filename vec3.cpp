#include "vec3.h"

vec3 operator*(float f, vec3 v) { return vec3(v.x * f, v.y * f, v.z * f); }

float clamp(float menor, float mayor, float valor) {
  if (valor < menor) {
    return menor;
  }
  if (valor > mayor) {
    return mayor;
  }
  return valor;
}