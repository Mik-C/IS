
#ifndef RTIS_STUDENTS_V2_2017_MIRROR_H
#define RTIS_STUDENTS_V2_2017_MIRROR_H


#include "material.h"

class Mirror : public Material {
	Vector3D k_s; //specular

public:
	Mirror();
	Mirror(Vector3D k_s);
	~Mirror();

	Vector3D getReflectance(const Vector3D &n, const Vector3D &wo, const Vector3D &wi) const;
	bool hasSpecular() const;
	bool hasTransmission() const;
	bool hasDiffuseOrGlossy() const;
	double getIndexOfRefraction() const;

	void setSpecular(Vector3D k);
};


#endif //RTIS_STUDENTS_V2_2017_MIRROR_H
