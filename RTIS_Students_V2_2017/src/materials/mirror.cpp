#include <cmath>
#include <iostream>

#include "mirror.h"
#include "../core/utils.h"

Mirror::Mirror() :
	 foo(Vector3D(1, 1, 1))
{}

Mirror::Mirror( Vector3D foo) :
	 foo(foo)
{}

Mirror::~Mirror() {}

Vector3D Mirror::getReflectance(const Vector3D &n, const Vector3D &wo, const Vector3D &wi) const {
	return Vector3D(0,0,0);
}

bool Mirror::hasSpecular() const {
	return true;
}

bool Mirror::hasTransmission() const {
	return false;
}

bool Mirror::hasDiffuseOrGlossy() const {
	return false;
}

double Mirror::getIndexOfRefraction() const {
	std::cout << "Warning! Calling \"Material::getIndexOfRefraction()\" for a non-transmissive material"
		<< std::endl;
	return -1;
}

Vector3D Mirror::getDiffuseCoefficient() {
	return foo;
}
