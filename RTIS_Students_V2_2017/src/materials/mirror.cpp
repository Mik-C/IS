#include <cmath>
#include <iostream>

#include "mirror.h"

Mirror::Mirror() :
	 k_s(Vector3D(1, 1, 1))
{}

Mirror::Mirror( Vector3D k_s) :
	 k_s(k_s)
{}

Mirror::~Mirror() {}

Vector3D Mirror::getReflectance(const Vector3D &n, const Vector3D &wo, const Vector3D &wi) const {
	Vector3D wr = (((n * dot(n, wo)) * 2) - wo).normalized();
	
	return wr;
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

void Mirror::setSpecular(Vector3D k) { this->k_s = k; }
