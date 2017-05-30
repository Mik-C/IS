
#ifndef RTIS_STUDENTS_V2_2017_DIRECTSHADER_H
#define RTIS_STUDENTS_V2_2017_DIRECTSHADER_H

#include "shader.h"

class DirectShader : public Shader
{
public:
    DirectShader();
    DirectShader(Vector3D bgColor_);
    ~DirectShader();

    virtual Vector3D computeColor(const Ray &r,
                                  const std::vector<Shape*> &objList,
                                  const std::vector<PointLightSource> &lsList) const;

private:
};


#endif //RTIS_STUDENTS_V2_2017_DIRECTSHADER_H
