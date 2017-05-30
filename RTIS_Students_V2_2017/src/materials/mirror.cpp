#include <cmath>
#include <iostream>

#include "mirror.h"
#include "../core/utils.h"

Mirror::Mirror() :
	 stuff(Vector3D(1, 1, 1))
{}

Mirror::Mirror( Vector3D stuff) :
	 stuff(stuff)
{}

Mirror::~Mirror() {}

Vector3D Mirror::getReflectance(const Vector3D &n, const Vector3D &wo, const Vector3D &wi) const {
	return stuff;
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
