#include "vec3.h"

float clamp(float menor, float mayor, float valor) {
    if (valor < menor) {
        return menor;
    }
    if (valor > mayor) {
        return mayor;
    }
    return valor;
}