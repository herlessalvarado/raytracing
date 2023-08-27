#include <iostream>

#include "Camera.h"
#include "Light.h"
#include "Object.h"
#include "World.h"
#include "vec3.h"

int main() {
  Camera camera;
  Light light(vec3(400, 300, 0), vec3(1, 1, 1));
  World world(camera, light);
  world.camera.configure(3, 60, 800, 600, vec3(0, 5, 50), vec3(0, 0, 0),
                         vec3(0, 1, 0));
  world.camera.render(world.light);

  return 0;
};
