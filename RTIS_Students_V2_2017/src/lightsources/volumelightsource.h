
#ifndef RTIS_STUDENTS_V2_2017_VOLUMETRICLIGHTSOURCE_H
#define RTIS_STUDENTS_V2_2017_VOLUMETRICLIGHTSOURCE_H

#include "lightsource.h"

class VolumeLightSource : public LightSource{
public:
    VolumeLightSource() = delete;
    //x_ indicates the relative x direction. xy_ represents a vector in the plane created by x and y directions (it
    //doesn't need to be perpendicular to x
    VolumeLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_,
            Vector3D x_, Vector3D xy_, double rX_, double rY_, double rZ_);

    Vector3D interpolatePoint(const double &x, const double &y, const double &z) const;

protected:
    Vector3D vX;
    Vector3D vY;
    Vector3D vZ;
    double rX;
    double rY;
    double rZ;
};

class SphereLightSource : public VolumeLightSource{
public:
    SphereLightSource() = delete;
    SphereLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_,
            Vector3D x_, Vector3D xy_, double r_);
    Vector3D generatePoint(const Vector3D &opos) const;
};

class CylinderLightSource : public VolumeLightSource{
public:
    CylinderLightSource() = delete;
    CylinderLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_,
            Vector3D x_, Vector3D xy_, double rL_, double rC_);
    Vector3D generatePoint(const Vector3D &opos) const;
};

#endif //RTIS_STUDENTS_V2_2017_VOLUMETRICLIGHTSOURCE_H
