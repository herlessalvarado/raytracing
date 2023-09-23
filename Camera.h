#ifndef CAMERA_H
#define CAMERA_H

#include <vector>

#include "CImg.h"
#include "Light.h"
#include "Object.h"
#include "Ray.h"
#include "vec3.h"

using namespace std;
using namespace cimg_library;
typedef unsigned char BYTE;

class Camera {
    vec3 eye, xe, ye, ze;
    float f, a, b, w, h;
    CImg<BYTE>* pImg;

   public:
    Camera() {}

    void configure(float _near, float fov, int width, int height, vec3 pos_eye,
                   vec3 center, vec3 up);

    void render(vector<Light>& lights, vector<Object*> objects, int x);

    vec3 lightning(vector<Light>& lights, vector<Object*> objects, Ray ray, int depth);

    vec3 refract(vec3& I, vec3& N, float& ior);

    void fresnel(vec3& I, vec3& N, float& ior, float& kr);
};

#endif  // CAMERA_H
