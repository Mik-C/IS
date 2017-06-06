#include <cmath>
#include <iostream>

#include "phong.h"

Phong::Phong() :
        k_d(Vector3D(1,1,1)), k_s(Vector3D(1,1,1)), s(double(1))
{}

Phong::Phong(Vector3D k_d, Vector3D k_s, double s) :
        k_d(k_d), k_s(k_s), s(s)
{}

Phong::~Phong() {}

Vector3D Phong::getReflectance(const Vector3D &n, const Vector3D &wo, const Vector3D &wi) const {
    Vector3D r_d = k_d * (dot(wi, n));
    Vector3D wr = (((n * dot(n, wi)) * 2) - wi);
    Vector3D r_s = k_s * (pow(dot(wo, wr), s));

    return r_d + r_s;
}

Vector3D Phong::getDiffuseCoefficient() const {
    return k_d;
}

bool Phong::hasSpecular() const {
    return false;
}

bool Phong::hasTransmission() const {
    return false;
}

bool Phong::hasDiffuseOrGlossy() const {
    return true;
}

double Phong::getIndexOfRefraction() const {
    std::cout << "Warning! Calling \"Material::getIndexOfRefraction()\" for a non-transmissive material"
              << std::endl;
    return -1;
}

void Phong::setDiffuse(Vector3D k) {this->k_d = k;}
void Phong::setSpecular(Vector3D k) {this->k_s = k;}
void Phong::setShininess(double s) {this->s = s;}
