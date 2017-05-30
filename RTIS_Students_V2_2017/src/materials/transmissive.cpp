
#include "transmissive.h"

Transmissive::Transmissive() :
        n(1.2), foo(Vector3D(1, 1, 1))
{}

Transmissive::Transmissive( double n, Vector3D foo) :
        n(n), foo(foo)
{}

Transmissive::~Transmissive() {}

Vector3D Transmissive::getReflectance(const Vector3D &n, const Vector3D &wo, const Vector3D &wi) const {
    return Vector3D(0,0,0);
}

bool Transmissive::hasSpecular() const {
    return false;
}

bool Transmissive::hasTransmission() const {
    return true;
}

bool Transmissive::hasDiffuseOrGlossy() const {
    return false;
}

double Transmissive::getIndexOfRefraction() const {
    return n;
}

Vector3D Transmissive::getDiffuseCoefficient() const {
    return foo;
}
