
#ifndef RTIS_STUDENTS_V2_2017_LIGHTSOURCE_H
#define RTIS_STUDENTS_V2_2017_LIGHTSOURCE_H

#include "../core/vector3d.h"

class LightSource {
public:
    LightSource() = delete;

    LightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_);

    // Getters
    Vector3D getPosition() const;

    unsigned int getSamples() const;

    virtual Vector3D generatePoint() const;

    virtual Vector3D getIntensity(const Vector3D &lpos, const Vector3D &opos) const;

protected:
    Vector3D pos;
    Vector3D intensity; // (unity: watts/sr)
    unsigned int samples;
};

LightSource *PointLightSource(Vector3D pos_, Vector3D intensity_);


#endif //RTIS_STUDENTS_V2_2017_LIGHTSOURCE_H
