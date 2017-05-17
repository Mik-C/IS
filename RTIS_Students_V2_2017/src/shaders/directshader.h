
#ifndef RTIS_STUDENTS_V2_2017_DIRECTSHADER_H
#define RTIS_STUDENTS_V2_2017_DIRECTSHADER_H

#include "shader.h"

class Directshader : public Shader
{
public:
    Directshader();
    Directshader(double maxDist_, Vector3D bgColor_);
    ~Directshader();

    virtual Vector3D computeColor(const Ray &r,
                                  const std::vector<Shape*> &objList,
                                  const std::vector<PointLightSource> &lsList) const;

private:
    double maxDist; // Used to store the value of the maximum distance which can be visualized
};


#endif //RTIS_STUDENTS_V2_2017_DIRECTSHADER_H
