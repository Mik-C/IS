
#include "arealightsource.h"

AreaLightSource::AreaLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_,
                                 Vector3D normal_, Vector3D up_, double rH, double rV) :
        LightSource(pos_, intensity_, samples_), normal(normal_), rHorizontal(rH), rVertical(rV)
{
    horizontal = cross(normal_, up_).normalized();
    vertical = cross(horizontal, normal_).normalized();
}

Vector3D AreaLightSource::interpolatePoint(const double &x, const double &y) const{
    return pos + horizontal*(x*rHorizontal) + vertical*(y*rVertical);
}

QuadLightSource::QuadLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_,
                                 Vector3D normal_, Vector3D up_, double rH, double rV) :
        AreaLightSource(pos_, intensity_, samples_, normal_, up_, rH, rV)
{}

Vector3D QuadLightSource::generatePoint(const Vector3D &opos) const {
    double x = (((double)random() / RAND_MAX) - 0.5)*2;
    double y = (((double)random() / RAND_MAX) - 0.5)*2;
    return interpolatePoint(x, y);
}

EllipseLightSource::EllipseLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_,
                                       Vector3D normal_, Vector3D up_, double rH, double rV) :
        AreaLightSource(pos_, intensity_, samples_, normal_, up_, rH, rV)
{}

Vector3D EllipseLightSource::generatePoint(const Vector3D &opos) const {
    double t = 2*M_PI*((double)random() / RAND_MAX);
    double r = sqrt(((double)random() / RAND_MAX));
    double x = r*cos(t);
    double y = r*sin(t);
    return interpolatePoint(x, y);
}