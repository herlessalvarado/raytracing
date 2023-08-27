#include <iostream>

#include "Camera.h"
#include "Light.h"
#include "Mundo.h"
#include "Object.h"
#include "vec3.h"

int main() {
  Camera camera;
  Light light(vec3(400, 300, 0), vec3(1, 1, 1));
  Mundo mundo(camera, light);
  mundo.camera.configure(3, 60, 800, 600, vec3(0, 5, 50), vec3(0, 0, 0),
                         vec3(0, 1, 0));
  mundo.camera.render(mundo.light);

  return 0;
};
