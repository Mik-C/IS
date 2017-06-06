
#ifndef RTIS_STUDENTS_V2_2017_GLOBALSHADER_H
#define RTIS_STUDENTS_V2_2017_GLOBALSHADER_H

#include "shader.h"

class GlobalShader : public Shader{
public:
    GlobalShader();
    GlobalShader(Vector3D bgColor_, Vector3D ambient);
    ~GlobalShader();

    virtual Vector3D computeColor(const Ray &r,
                                  const std::vector<Shape*> &objList,
                                  const std::vector<LightSource*> &lsList) const;

    Vector3D indirectColor(const Intersection &its,
                           const Ray &r,
                           const std::vector<Shape*> &objList,
                           const std::vector<LightSource*> &lsList) const;

private:
    Vector3D ambient;
    int indirectSamples;
    int indirectBounces;
};


#endif //RTIS_STUDENTS_V2_2017_GLOBALSHADER_H
