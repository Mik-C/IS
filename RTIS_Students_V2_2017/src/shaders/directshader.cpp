
#include "directshader.h"
#include "../core/utils.h"

DirectShader::DirectShader() :
        Shader(Vector3D(0,0,0))
{}

DirectShader::DirectShader(Vector3D bgColor_) :
        Shader(bgColor_)
{}

DirectShader::~DirectShader() {}

Vector3D DirectShader::computeColor(const Ray &ray, const std::vector<Shape *> &objList,
                                    const std::vector<LightSource*> &lsList) const {

	if(ray.depth > 10000)
		return Vector3D(0,0,0);

    Intersection *its = new Intersection();
	if (!Utils::getClosestIntersection(ray, objList, *its))
		return bgColor;
    its->normal = its->normal.normalized();

	Vector3D color = Vector3D(0,0,0);

    if(its->shape->getMaterial().hasSpecular()){
        Ray reflectRay;
        reflectRay.o = its->itsPoint;
        reflectRay.d = Utils::computeReflectionDirection(ray.d, its->normal);
        reflectRay.depth = ray.depth + 1;
        color = computeColor(reflectRay, objList, lsList);

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
            color = computeColor(refractRay, objList, lsList);
        }else{
            refractRay.d = Utils::computeReflectionDirection(ray.d, its->normal);
            color = computeColor(refractRay, objList, lsList);
        }

    }else if(its->shape->getMaterial().hasDiffuseOrGlossy()){
		for(LightSource* const &ls : lsList)
		{
            unsigned int samples = ls->getSamples();
            Vector3D Light, reflectance;

            for(unsigned int i=0; i<samples; i++){
                Vector3D lpos = ls->generatePoint();
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
            color += Utils::multiplyPerCanal(Light, reflectance);
		}
	}
	return color;
}
