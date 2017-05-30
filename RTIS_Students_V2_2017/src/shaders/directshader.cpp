
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
                                    const std::vector<PointLightSource> &lsList) const {
	Intersection *its = new Intersection();

	if(ray.depth > 10)
		return Vector3D(0,0,0);

	if (!Utils::getClosestIntersection(ray, objList, *its))
		return bgColor;

	Vector3D color = Vector3D(0,0,0);

	if(its->shape->getMaterial().hasSpecular()){
		Ray reflectRay;
		reflectRay.o = its->itsPoint;
		reflectRay.d = Utils::computeReflectionDirection(ray.d, its->normal);
		reflectRay.depth = ray.depth + 1;
		color = computeColor(reflectRay, objList, lsList);

	}else if(its->shape->getMaterial().hasDiffuseOrGlossy()){
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
			color += Utils::multiplyPerCanal(Lp, r);
		}
	}
	return color;
}
