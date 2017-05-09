#include <cmath>
#include <iostream>

#include "phong.h"

PhongMaterial::PhongMaterial() {
    this->k_d = Vector3D(1,1,1);
    this->k_s = Vector3D(1,1,1);
    this->s = 1;
}

PhongMaterial::PhongMaterial(Vector3D k_d, Vector3D k_s, double s) {
    this->k_d = k_d;
    this->k_s = k_s;
    this->s = s;
}

PhongMaterial::~PhongMaterial() {}

Vector3D PhongMaterial::getReflectance(const Vector3D &n, const Vector3D &wo, const Vector3D &wi) const {
    Vector3D r_d = k_d * (dot(wi, n));
    Vector3D wr = (n * dot(n, wi)) * 2 - wi;
    Vector3D r_s = k_s * (pow(dot(wo, wr), s));

    return r_d + r_s;
}

bool PhongMaterial::hasSpecular() const {
    return true;
}

bool PhongMaterial::hasTransmission() const {
    return false;
}

bool PhongMaterial::hasDiffuseOrGlossy() const {
    return true;
}

double PhongMaterial::getIndexOfRefraction() const {
    std::cout << "Warning! Calling \"Material::getIndexOfRefraction()\" for a non-transmissive material"
              << std::endl;
    return -1;
}

void PhongMaterial::setDiffuse(Vector3D k) {this->k_d = k;}
void PhongMaterial::setSpecular(Vector3D k) {this->k_s = k;}
void PhongMaterial::sedShininess(double s) {this->s = s;}
