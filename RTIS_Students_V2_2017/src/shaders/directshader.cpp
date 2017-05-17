
#include "directshader.h"
#include "../materials/phong.h"
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
	//std::cout << "1!" << std::endl;
	
	Intersection *its = new Intersection();
	if (!Utils::getClosestIntersection(r, objList, *its))
		return bgColor;
		
	Vector3D color(0.4, 1, 0.4);
	for (size_t lsIndex = 0; lsIndex < lsList.size(); lsIndex++)
	{
		Vector3D intensityLP = lsList.at(lsIndex).getIntensity(its->itsPoint);
		Vector3D wi = lsList.at(lsIndex).getPosition() - its->itsPoint;
		wi.normalized();
		Vector3D wo = (0, 0, -1);
		Vector3D reflectance = its->shape->getMaterial().getReflectance(its->normal, wi, wo);
		color = color + dot(intensityLP, reflectance);
	}
	return color;
		
	

	//return bgColor;

    /*
	Intersection *its = new Intersection();
    if (!Utils::getClosestIntersection(r, objList, *its))
        return bgColor;
    
    double depth = sqrt(pow(its->itsPoint.x - r.o.x, 2) + pow(its->itsPoint.y - r.o.y, 2) + pow(its->itsPoint.z - r.o.z, 2));
    if ( (depth) >= maxDist )
         return bgColor;

    Vector3D color(0,0,0);
    for(int i=0; i<lsList.size(); i++){ //Implement light intensity formula
		//std::cout << "2!" << std::endl;
		//p es punt interesaccio aka its->itsPoint
		//wi es direccio des de p al focus
		Vector3D wi = lsList[i].getPosition() - its->itsPoint;
		wi.normalized();
		//n es la normal al punt p
		Vector3D n = its->normal;
		//viewing direction, sempre perpendicular a pantalla
		Vector3D wo = (0, 0, -1);
		//obtenim intensitat al punt p
		Vector3D l = lsList[i].getIntensity(its->itsPoint);
		//agafa el phong del objecte amb que intersecciona
		Vector3D r = its->shape->getMaterial().getReflectance(n, wi, wo);
		color += dot(l,r);
    }
	//std::cout << "Yass!" << std::endl;
	return color;
	
    */

}
