#include "Camera.h"

#include <iostream>

using namespace std;

void Camera::configure(float _near, float fov, int width, int height,
                       vec3 pos_eye, vec3 center, vec3 up) {
    f = _near;
    w = width;
    h = height;
    a = 2 * f * tan(fov * M_PI / 360);
    b = w / h * a;
    eye = pos_eye;
    ze = eye - center;
    ze.normalize();
    xe = up.cross(ze);
    xe.normalize();
    ye = ze.cross(xe);
}

void Camera::render(Light& light, vector<Object*> objects) {
    Ray ray;
    ray.ori = eye;
    vec3 dir;

    pImg = new CImg<BYTE>(w, h, 1, 3);
    CImgDisplay dis_img(
        (*pImg), "Imagen RayTracing en Perspectiva desde una Camara Pinhole");

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
            for (auto object : objects) {
                if (object->intersect(ray, t, Pi, N)) {
                    vec3 ambient = light.color * object->ka;
                    vec3 L = light.pos - Pi;
                    // double distance_to_light = L.modulus();
                    L.normalize();
                    float diff = L.dot(N);
                    vec3 diffuse = light.color * object->kd * max(0.0f, diff);
                    vec3 R = 2.0f * diff * N - L;
                    vec3 V = -dir;
                    vec3 especular = light.color * (object->ks * (pow(max(0.0f, R.dot(V)), object->shininess)));
                    color = object->color * (diffuse + ambient + especular);
                    color.max_to_one();
                }
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
