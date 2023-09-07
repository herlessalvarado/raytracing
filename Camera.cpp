#include "Camera.h"

#include <cmath>
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
            Object* closestObject = nullptr;
            float minT = std::numeric_limits<float>::infinity();
            vec3 minPi = vec3();
            vec3 minL = vec3();
            vec3 minN = vec3();
            bool hasIntersected = false;
            for (auto object : objects) {
                if (object->intersect(ray, t, Pi, N)) {
                    hasIntersected = true;
                    if (t < minT && t > 0) {
                        minT = t;
                        minPi = Pi;
                        minN = N;
                        closestObject = object;
                    }
                }
            }
            if (hasIntersected == true) {
                vec3 ambient = light.color * closestObject->ka;
                vec3 L = light.pos - minPi;
                L.normalize();
                minL = L;  // rs
                float diff = L.dot(minN);
                vec3 diffuse = light.color * closestObject->kd * max(0.0f, diff);
                vec3 R = 2.0f * diff * minN - L;
                vec3 V = -dir;
                vec3 especular = light.color * (closestObject->ks * (pow(max(0.0f, R.dot(V)), closestObject->shininess)));
                color = closestObject->color * (diffuse + ambient + especular);
                color.max_to_one();
            }
            if (minT != std::numeric_limits<float>::infinity()) {
                Ray shadowRay;
                shadowRay.ori = minPi + 0.005 * N;
                shadowRay.dir = minL;
                for (auto object : objects) {
                    if (object->intersect(shadowRay, t, Pi, N)) {
                        float distance_to_light = sqrt(pow(minPi.x - light.pos.x, 2.0) + pow(minPi.y - light.pos.y, 2.0) + pow(minPi.z - light.pos.z, 2.0));
                        float distance_to_current_object = sqrt(pow(minPi.x - Pi.x, 2.0) + pow(minPi.y - Pi.y, 2.0) + pow(minPi.z - Pi.z, 2.0));
                        if (distance_to_light > distance_to_current_object) {
                            color = closestObject->color * (light.color * closestObject->ka);
                        }
                    }
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
