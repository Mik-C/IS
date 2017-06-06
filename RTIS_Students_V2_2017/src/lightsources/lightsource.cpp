
#include "lightsource.h"

LightSource::LightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_) :
        pos(pos_), intensity(intensity_), samples(samples_) {}

Vector3D LightSource::getPosition() const {
    return pos;
}

LightSource* PointLightSource(Vector3D pos_, Vector3D intensity_) {
    return new LightSource(pos_, intensity_, 1);
}

unsigned int LightSource::getSamples() const {
    return samples;
}

Vector3D LightSource::generatePoint() const {
    return pos;
}

Vector3D LightSource::getIntensity(const Vector3D &lpos, const Vector3D &opos) const {
    double sqDistance = (opos - lpos).lengthSq();
    Vector3D result = intensity / sqDistance;
    return result;
}