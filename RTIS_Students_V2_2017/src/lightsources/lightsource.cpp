
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

Vector3D LightSource::generatePoint(const Vector3D &opos) const {
    return pos;
}

Vector3D LightSource::getIntensity(const Vector3D &lpos, const Vector3D &opos) const {
    double sqDistance = (opos - lpos).lengthSq();
    Vector3D result = intensity / sqDistance;
    return result;
}

FocusLightSource::FocusLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_,
                                   Vector3D normal_, double angle_) :
        LightSource(pos_, intensity_, samples_), normal(normal_.normalized()), mincos(cos(angle_))
{}

Vector3D FocusLightSource::getIntensity(const Vector3D &lpos, const Vector3D &opos) const {
    double  dotResult = dot(normal, (opos-lpos).normalized());
    if(dotResult < mincos)
        return Vector3D(0,0,0);
    double sqDistance = (opos - lpos).lengthSq();
    Vector3D result = intensity / sqDistance;
    return result;
}

FocusAreaLightSource::FocusAreaLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_, Vector3D normal_,
                                           double angle_, double dist_) :
        FocusLightSource(pos_+normal_.normalized()*dist_, intensity_, samples_, normal_, angle_)
{
    Vector3D rnd;
    rnd.rand();
    vX = cross(normal_, rnd).normalized();
    vY = cross(vX, normal_).normalized();
    r = tan(angle_)*dist_;
}

Vector3D FocusAreaLightSource::generatePoint(const Vector3D &opos) const {
    double t = 2*M_PI*((double)random() / RAND_MAX);
    double r = sqrt(((double)random() / RAND_MAX));
    double x = r*cos(t);
    double y = r*sin(t);
    return pos + vX*(x*r) + vY*(y*r);
}
