
#ifndef RTIS_STUDENTS_V2_2017_AREALIGHTSOURCE_H
#define RTIS_STUDENTS_V2_2017_AREALIGHTSOURCE_H

#include "lightsource.h"

class AreaLightSource : public LightSource{
public:
    AreaLightSource() = delete;
    AreaLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_,
                    Vector3D normal_, Vector3D up_, double rH, double rV);
    Vector3D interpolatePoint(const double &x, const double &y) const;

protected:
    Vector3D normal;
    Vector3D vertical;
    Vector3D horizontal;
    double rVertical;
    double rHorizontal;
};

class QuadLightSource : public AreaLightSource{
public:
    QuadLightSource() = delete;
    QuadLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_,
                    Vector3D normal_, Vector3D up_, double rH, double rV);

    Vector3D generatePoint(const Vector3D &opos) const;
};

class EllipseLightSource : public AreaLightSource{
public:
    EllipseLightSource() = delete;
    EllipseLightSource(Vector3D pos_, Vector3D intensity_, unsigned int samples_,
                       Vector3D normal_, Vector3D up_, double rH, double rV);

    Vector3D generatePoint(const Vector3D &opos) const;
};

#endif //RTIS_STUDENTS_V2_2017_AREALIGHTSOURCE_H
