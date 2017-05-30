
#ifndef RTIS_STUDENTS_V2_2017_TRANSMISSIVE_H
#define RTIS_STUDENTS_V2_2017_TRANSMISSIVE_H

#include "material.h"

class Transmissive : public Material{
    double n;
    Vector3D foo;
public:

    Transmissive();
    Transmissive(double n, Vector3D foo);
    ~Transmissive();

    Vector3D getReflectance(const Vector3D &n, const Vector3D &wo,
                                    const Vector3D &wi) const;
    bool hasSpecular() const;
    bool hasTransmission() const;
    bool hasDiffuseOrGlossy() const;
    double getIndexOfRefraction() const;

    Vector3D getDiffuseCoefficient() const;
};


#endif //RTIS_STUDENTS_V2_2017_TRANSMISSIVE_H
