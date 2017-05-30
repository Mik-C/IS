
#include "directshader.h"
#include "../core/utils.h"

DirectShader::DirectShader() :
        Shader(Vector3D(0,0,0))
{}

DirectShader::DirectShader(Vector3D bgColor_) :
        Shader(bgColor_)
{}

DirectShader::~DirectShader() {}

Vector3D DirectShader::computeColor(const Ray &r, const std::vector<Shape *> &objList,
                                    const std::vector<PointLightSource> &lsList) const {
	Intersection *its = new Intersection();
	if (!Utils::getClosestIntersection(r, objList, *its))
		return bgColor;

	Vector3D color = Vector3D(0,0,0);
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
		Vector3D wo = (-r.d).normalized();
		Vector3D r  = its->shape->getMaterial().getReflectance(its->normal, wo, wi);
		color += Utils::multiplyPerCanal(Lp, r);
	}
	return color;
}
