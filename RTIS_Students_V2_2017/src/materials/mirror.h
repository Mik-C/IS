
#ifndef RTIS_STUDENTS_V2_2017_MIRROR_H
#define RTIS_STUDENTS_V2_2017_MIRROR_H


#include "material.h"

class Mirror : public Material {
	Vector3D foo;

public:
	Mirror();
	Mirror(Vector3D foo);
	~Mirror();

	Vector3D getReflectance(const Vector3D &n, const Vector3D &wo, const Vector3D &wi) const;
	bool hasSpecular() const;
	bool hasTransmission() const;
	bool hasDiffuseOrGlossy() const;
	double getIndexOfRefraction() const;

	Vector3D getStuff();
};


#endif //RTIS_STUDENTS_V2_2017_MIRROR_H
