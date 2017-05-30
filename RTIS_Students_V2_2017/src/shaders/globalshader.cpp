
#include "globalshader.h"
#include "../materials/phong.h"
#include "../core/utils.h"
#include "../core/hemisphericalsampler.h"

GlobalShader::GlobalShader() :
        Shader(Vector3D(0,0,0)), ambient(Vector3D(0.1,0.1,0.1)), indirectSamples(3), indirectBounces(1)
{}

GlobalShader::GlobalShader(Vector3D bgColor_, Vector3D ambient) :
        Shader(bgColor_), ambient(ambient), indirectSamples(10), indirectBounces(5)
{}

GlobalShader::~GlobalShader() {}

Vector3D GlobalShader::computeColor(const Ray &ray, const std::vector<Shape *> &objList,
                                    const std::vector<PointLightSource> &lsList) const {
    Intersection *its = new Intersection();
    if (!Utils::getClosestIntersection(ray, objList, *its))
        return bgColor;

    Vector3D i_color = indirectColor(*its, ray, objList, lsList);
    Vector3D d_color;
    for(PointLightSource const &ls : lsList)
    {
        Vector3D wi = (ls.getPosition() - its->itsPoint);
        double distance = wi.length();
        wi = wi.normalized();
        Ray lray = Ray(its->itsPoint, wi);
        lray.maxT = distance;
        if(Utils::hasIntersection(lray, objList))
            continue;

        Vector3D Lp = ls.getIntensity(its->itsPoint);
        Vector3D wo = (-ray.d).normalized();
        Vector3D r  = its->shape->getMaterial().getReflectance(its->normal, wo, wi);
        d_color += Utils::multiplyPerCanal(Lp, r);
    }
    return i_color + d_color;
}

Vector3D GlobalShader::indirectColor(const Intersection &its, const Ray &ray, const std::vector<Shape *> &objList,
                                     const std::vector<PointLightSource> &lsList) const {
    Vector3D Ip;
    if(ray.depth == 0){
        HemisphericalSampler sampler;
        Ip = Vector3D(0);
        for(int i=0; i<indirectSamples; i++){
            Ray secondaryRay;
            secondaryRay.o = its.itsPoint;
            secondaryRay.d = sampler.getSample(its.normal);
            secondaryRay.depth = 1;
            Intersection secondaryIts;
            if (!Utils::getClosestIntersection(secondaryRay, objList, secondaryIts))
                continue;

            Vector3D wo = (-ray.d);
            Vector3D wi = (secondaryRay.d);
            Vector3D r  = its.shape->getMaterial().getReflectance(its.normal, wo, wi);
            Vector3D Li = indirectColor(secondaryIts, secondaryRay, objList, lsList);
            Ip += Utils::multiplyPerCanal(Li, r);
        }
        Ip /= indirectSamples;
    }else if(ray.depth < indirectBounces){
        Vector3D nColor;
        Ray normalRay;
        normalRay.o = its.itsPoint;
        normalRay.d = its.normal;
        normalRay.depth = ray.depth + 1;
        Intersection normalIts;
        if (Utils::getClosestIntersection(normalRay, objList, normalIts))
            nColor = indirectColor(normalIts, normalRay, objList, lsList);

        Vector3D rColor;
        Ray reflectRay;
        reflectRay.o = its.itsPoint;
        reflectRay.d = Utils::computeReflectionDirection(ray.d, its.normal);
        reflectRay.depth = ray.depth + 1;
        Intersection reflectIts;
        if (Utils::getClosestIntersection(normalRay, objList, reflectIts))
            rColor = indirectColor(reflectIts, reflectRay, objList, lsList);

        Ip = (nColor + rColor)/2;
    }else{
        Ip = Utils::multiplyPerCanal(ambient, its.shape->getMaterial().getDiffuseCoefficient());
    }
    return Ip;
}
