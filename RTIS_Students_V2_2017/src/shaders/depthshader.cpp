#include "depthshader.h"
#include "depthshader.h"
#include "../core/utils.h"
#include <cmath>

DepthShader::DepthShader() :
	color(Vector3D(0, 1, 0))
{ }

DepthShader::DepthShader(Vector3D color_, double maxDist_, Vector3D bgColor_) :
	Shader(bgColor_), maxDist(maxDist_), color(color_)
{ }

Vector3D DepthShader::computeColor(const Ray &r, const std::vector<Shape*> &objList, const std::vector<PointLightSource> &lsList) const
{
	Intersection *its = new Intersection();
	if (!Utils::getClosestIntersection(r, objList, *its))
		return bgColor;
	else
	{
		double depth = sqrt(pow(its->itsPoint.x - r.o.x, 2) + pow(its->itsPoint.y - r.o.y, 2) + pow(its->itsPoint.z - r.o.z, 2));
		if ( (depth) >= maxDist )			return bgColor;		else 			return color * (1.0 - depth / maxDist);
	}
}