
#ifndef RTIS_STUDENTS_V2_2017_PHONG_H
#define RTIS_STUDENTS_V2_2017_PHONG_H


#include "material.h"

class PhongMaterial : public Material{
    Vector3D k_d; //diffuse
    Vector3D k_s; //specular
    double s;   //shininess

public:
    PhongMaterial();
    PhongMaterial(Vector3D k_d, Vector3D k_s, double s);
    ~PhongMaterial();

    Vector3D getReflectance(const Vector3D &n, const Vector3D &wo,
                                    const Vector3D &wi) const;
    bool hasSpecular() const;
    bool hasTransmission() const;
    bool hasDiffuseOrGlossy() const;
    double getIndexOfRefraction() const;

    void setDiffuse(Vector3D k);
    void setSpecular(Vector3D k);
    void sedShininess(double s);
};


#endif //RTIS_STUDENTS_V2_2017_PHONG_H
