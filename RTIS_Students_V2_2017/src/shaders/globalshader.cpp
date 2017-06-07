
#include "globalshader.h"
#include "../materials/phong.h"
#include "../core/utils.h"
#include "../core/hemisphericalsampler.h"

GlobalShader::GlobalShader() :
        Shader(Vector3D(0,0,0)), ambient(Vector3D(0.1,0.1,0.1)), indirectSamples(3), indirectBounces(1)
{}

GlobalShader::GlobalShader(Vector3D bgColor_, Vector3D ambient) :
        Shader(bgColor_), ambient(ambient), indirectSamples(8), indirectBounces(3)
{}

GlobalShader::~GlobalShader() {}

Vector3D GlobalShader::computeColor(const Ray &ray, const std::vector<Shape *> &objList,
                                    const std::vector<LightSource*> &lsList) const {

    if(ray.depth > 10000)
        return Vector3D(0,0,0);

    Intersection *its = new Intersection();
    if (!Utils::getClosestIntersection(ray, objList, *its))
        return bgColor;

    Vector3D d_color;
    Vector3D i_color = indirectColor(*its, ray, objList, lsList);

    if(its->shape->getMaterial().hasSpecular()){
        Ray reflectRay;
        reflectRay.o = its->itsPoint;
        reflectRay.d = Utils::computeReflectionDirection(ray.d, its->normal);
        reflectRay.depth = ray.depth + 1;
        d_color = computeColor(reflectRay, objList, lsList);

    }else if(its->shape->getMaterial().hasTransmission()){
        Ray refractRay;
        refractRay.o = its->itsPoint;
        refractRay.depth = ray.depth+ 1;
        Vector3D normal = its->normal;
        double cosT1 = dot(-ray.d, normal);
        double cosT2;
        double eta;
        double radicant;
        if(cosT1 >= 0) {
            eta = its->shape->getMaterial().getIndexOfRefraction();
            radicant = (1 - pow(eta,2) * (1 - pow(cosT1,2)));
        }else{
            normal = -normal;
            cosT1 = -cosT1;
            eta = 1/its->shape->getMaterial().getIndexOfRefraction();
            radicant = (1 - pow(eta,2) * (1 - pow(cosT1,2)));
        }
        if(radicant >= 0){
            cosT2 = sqrt(radicant);
            refractRay.d = ray.d*eta + normal*(eta*cosT1 - cosT2);
            d_color = computeColor(refractRay, objList, lsList);
        }else{
            refractRay.d = Utils::computeReflectionDirection(ray.d, its->normal);
            d_color = computeColor(refractRay, objList, lsList);
        }

    }else if(its->shape->getMaterial().hasDiffuseOrGlossy()){
        for(LightSource* const &ls : lsList)
        {
            unsigned int samples = ls->getSamples();
            Vector3D Light, reflectance;

            for(unsigned int i=0; i<samples; i++){
                Vector3D lpos = ls->generatePoint(its->itsPoint);
                Vector3D wi = (lpos - its->itsPoint);
                double distance = wi.length();
                wi = wi.normalized();
                Ray lray = Ray(its->itsPoint, wi);
                lray.maxT = distance-Epsilon;
                if(Utils::hasIntersection(lray, objList))
                    continue;

                Light += ls->getIntensity(lpos, its->itsPoint);
                Vector3D wo = (-ray.d).normalized();
                reflectance += its->shape->getMaterial().getReflectance(its->normal, wo, wi);
            }
            Light /= samples;
            reflectance /= samples;
            d_color += Utils::multiplyPerCanal(Light.clamp(0,1), reflectance.clamp(0,1));
        }
    }

    return d_color + i_color;
}

Vector3D GlobalShader::indirectColor(const Intersection &its, const Ray &ray, const std::vector<Shape *> &objList,
                                     const std::vector<LightSource*> &lsList) const {
    Vector3D Ip;
    if(its.shape->getMaterial().hasDiffuseOrGlossy()) {
        if (ray.depth == 0) {
            HemisphericalSampler sampler;
            Ip = Vector3D(0);
            for (int i = 0; i < indirectSamples; i++) {
                Ray secondaryRay;
                secondaryRay.o = its.itsPoint;
                secondaryRay.d = sampler.getSample(its.normal);
                secondaryRay.depth = 1;
                Intersection secondaryIts;
                if (!Utils::getClosestIntersection(secondaryRay, objList, secondaryIts))
                    continue;

                Vector3D wo = (-ray.d);
                Vector3D wi = (secondaryRay.d);
                Vector3D r = its.shape->getMaterial().getReflectance(its.normal, wo, wi);
                Vector3D Li = indirectColor(secondaryIts, secondaryRay, objList, lsList);
                Ip += Utils::multiplyPerCanal(Li, r);
            }
            Ip /= indirectSamples;
        } else if (ray.depth < indirectBounces) {
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
            reflectRay.depth = ray.depth + 1; // We incremented it because otherwise the stack memory runs off.
            Intersection reflectIts;
            if (Utils::getClosestIntersection(reflectRay, objList, reflectIts))
                rColor = indirectColor(reflectIts, reflectRay, objList, lsList);

            Ip = (nColor + rColor) / 2;
        } else {
            Ip = Utils::multiplyPerCanal(ambient, its.shape->getMaterial().getDiffuseCoefficient());
        }
    }else if(its.shape->getMaterial().hasSpecular()){
        Ray reflectRay;
        reflectRay.o = its.itsPoint;
        reflectRay.d = Utils::computeReflectionDirection(ray.d, its.normal);
        reflectRay.depth = ray.depth + 1;
        Intersection reflectIts;
        if (Utils::getClosestIntersection(reflectRay, objList, reflectIts))
            Ip = indirectColor(reflectIts, reflectRay, objList, lsList);
    }
    return Ip;
}
