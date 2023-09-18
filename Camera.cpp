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
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            dir = ze * (-f) + ye * a * (y / h - 0.5) + xe * b * (x / w - 0.5);
            dir.normalize();
            ray.dir = dir;
            vec3 color = lightning(light, objects, ray, 0);
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

vec3 Camera::lightning(Light& light, vector<Object*> objects, Ray ray, int depth) {
    float t;
    vec3 Pi, N, color;

    Object* closestObject = nullptr;
    float minT = std::numeric_limits<float>::infinity();
    vec3 minPi, minL, minN;
    bool hasIntersected = false;
    for (auto object : objects) {
        if (object->intersect(ray, t, Pi, N)) {
            if (t < minT && t > 0) {
                hasIntersected = true;
                minT = t;
                minPi = Pi;
                minN = N;
                closestObject = object;
            }
        }
    }
    if (hasIntersected) {
        vec3 ambient = light.color * closestObject->ka;
        vec3 diffuse = vec3(), specular = vec3();
        vec3 L = light.pos - minPi;
        float L_distance = L.modulus();
        L.normalize();
        minL = L;

        // Shadow
        Ray shadowRay;
        shadowRay.ori = minPi + 0.005 * minN;
        shadowRay.dir = minL;
        bool inShadow = false;
        for (auto object : objects) {
            if (object->intersect(shadowRay, t, Pi, N)) {
                if ((Pi - minPi).modulus() < L_distance) {
                    inShadow = true;
                    break;
                }
            }
        }

        vec3 V = -ray.dir;

        // No Shadow
        if (!inShadow) {
            float diff = L.dot(minN);
            diffuse = light.color * closestObject->kd * max(0.0f, diff);
            vec3 R = 2.0f * diff * minN - L;
            specular = light.color * (closestObject->ks * (pow(max(0.0f, R.dot(V)), closestObject->shininess)));
        }

        // Reflection
        vec3 reflective = vec3();
        if (closestObject->isReflective() && depth < 7) {
            vec3 reflected = 2 * V.dot(minN) * minN - V;
            reflected.normalize();
            Ray reflected_ray(minPi + 0.005 * minN, reflected);
            reflective = lightning(light, objects, reflected_ray, depth + 1);
        }
        color = closestObject->color * (ambient + diffuse + specular) + closestObject->kr * reflective;
        color.max_to_one();
    }
    return color;
}

vec3 Camera::refract(vec3& I, vec3& N, float& ior) {
    float cosi = clamp(-1, 1, I.dot(N));
    float etai = 1, etat = ior;
    vec3 n = N;
    if (cosi < 0) {
        cosi = -cosi;
    } else {
        std::swap(etai, etat);
        n = -N;
    }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? vec3() : eta * I + (eta * cosi - sqrtf(k)) * n;
}

void Camera::fresnel(vec3& I, vec3& N, float& ior, float& kr) {
    float cosi = clamp(-1, 1, I.dot(N));
    float etai = 1, etat = ior;
    if (cosi > 0) {
        std::swap(etai, etat);
    }
    // Compute sini using Snell's law
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    // Total internal reflection
    if (sint >= 1) {
        kr = 1;
    } else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        kr = (Rs * Rs + Rp * Rp) / 2;
    }
    // As a consequence of the conservation of energy, the transmittance is given by:
    // kt = 1 - kr;
}
