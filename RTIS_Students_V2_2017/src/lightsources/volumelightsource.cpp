
#define _USE_MATH_DEFINES
#include "volumelightsource.h"
#include "../core/hemisphericalsampler.h"
#include "../core/matrix4x4.h"

VolumeLightSource::VolumeLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_, Vector3D x_,
                                     Vector3D xy_, double rX_, double rY_, double rZ_) :
        LightSource(pos_, intensity_, samples_), rX(rX_), rY(rY_), rZ(rZ_)
{
    vX = x_.normalized();
    vZ = cross(x_, xy_).normalized();
    vY = cross(vZ, vX).normalized();
}

Vector3D VolumeLightSource::interpolatePoint(const double &x, const double &y, const double &z) const {
    return pos + vX*(x*rX) + vY*(y*rY) + vZ*(x*rZ);
}

SphereLightSource::SphereLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_, Vector3D x_,
                                           Vector3D xy_, double r_) :
        VolumeLightSource(pos_, intensity_, samples_, x_, xy_, r_, r_, r_)
{}

Vector3D SphereLightSource::generatePoint(const Vector3D &opos) const {
    HemisphericalSampler sampler;
    Vector3D relativePoint = sampler.getSample(opos-pos);
    return interpolatePoint(relativePoint.x,relativePoint.y,relativePoint.z);
}

CylinderLightSource::CylinderLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_, Vector3D x_,
                                     Vector3D xy_, double rL_, double rC_) :
        VolumeLightSource(pos_, intensity_, samples_, x_, xy_, rL_, rC_, rC_)
{}

Vector3D CylinderLightSource::generatePoint(const Vector3D &opos) const {
    Matrix4x4 frame(vX.x, vY.x, vZ.x, 0,
                    vX.y, vY.y, vZ.y, 0,
                    vX.z, vY.z, vZ.z, 0,
                    0,    0   , 0   , 0);
    Matrix4x4 frameInv;
    frameInv.inverse(frame);

    Vector3D closestPoint = (pos - opos) - vX*dot((pos - opos), vX);

    Vector3D normal = frameInv.transformVector(opos - closestPoint).normalized();
    double phi = acos((((double)rand() / RAND_MAX) - 0.5)*2) - M_PI_2;

    Vector3D P = Vector3D((((double)rand() / RAND_MAX) - 0.5)*2, 0, 0);
    P = P + normal*rX;
    P.y = P.y*sin(phi);
    P.z = P.z*cos(phi);

    return interpolatePoint(P.x, P.y, P.z);
}
