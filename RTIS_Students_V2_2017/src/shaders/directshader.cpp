
#include "directshader.h"
#include "../core/utils.h"

Directshader::Directshader() :
        Shader(Vector3D(0,0,0)), maxDist(100000)
{}

Directshader::Directshader(double maxDist_, Vector3D bgColor_) :
        Shader(bgColor_), maxDist(maxDist_)
{}

Directshader::~Directshader() {}

Vector3D Directshader::computeColor(const Ray &r, const std::vector<Shape *> &objList,
                                    const std::vector<PointLightSource> &lsList) const {

    Intersection *its = new Intersection();
    if (!Utils::getClosestIntersection(r, objList, *its))
        return bgColor;
    else{
        double depth = sqrt(pow(its->itsPoint.x - r.o.x, 2) + pow(its->itsPoint.y - r.o.y, 2) + pow(its->itsPoint.z - r.o.z, 2));
        if ( (depth) >= maxDist )
            return bgColor;

        Vector3D color(0,0,0);
        for(int i=0; i<lsList.size(); i++){ //Implement light intensity formula

        }
    }

}
