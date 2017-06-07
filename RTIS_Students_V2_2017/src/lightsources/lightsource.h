
#ifndef RTIS_STUDENTS_V2_2017_LIGHTSOURCE_H
#define RTIS_STUDENTS_V2_2017_LIGHTSOURCE_H

#include "../core/vector3d.h"
#include <random>

class LightSource {
public:
    LightSource() = delete;

    LightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_);

    // Getters
    Vector3D getPosition() const;

    unsigned int getSamples() const;

    virtual Vector3D generatePoint(const Vector3D &opos) const;

    virtual Vector3D getIntensity(const Vector3D &lpos, const Vector3D &opos) const;

protected:
    Vector3D pos;
    Vector3D intensity; // (unity: watts/sr)
    unsigned int samples;
};

LightSource *PointLightSource(Vector3D pos_, Vector3D intensity_);

class FocusLightSource : public LightSource {
public:
    FocusLightSource() = delete;

    FocusLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_, Vector3D normal_, double angle_);

    virtual Vector3D getIntensity(const Vector3D &lpos, const Vector3D &opos) const;

protected:
    Vector3D normal;
    double mincos;
};

class FocusAreaLightSource : public FocusLightSource {
public:
    FocusAreaLightSource() = delete;

    FocusAreaLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_, Vector3D normal_, double angle_, double dist_);

    virtual Vector3D generatePoint(const Vector3D &opos) const;

protected:
    double r;
    Vector3D vX, vY;
};


#endif //RTIS_STUDENTS_V2_2017_LIGHTSOURCE_H
