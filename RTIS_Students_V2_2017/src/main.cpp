
#define _USE_MATH_DEFINES
#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <vector>
#include <algorithm>

#include "core/film.h"
#include "core/matrix4x4.h"
#include "core/ray.h"
#include "core/utils.h"

#include "shapes/sphere.h"
#include "shapes/infiniteplane.h"

#include "cameras/ortographic.h"
#include "cameras/perspective.h"

#include "shaders/intersectionshader.h"
#include "shaders/normalshader.h"
#include "shaders/depthshader.h"

#include "shaders/directshader.h"
#include "shaders/globalshader.h"

#include "materials/phong.h"
#include "materials/mirror.h"
#include "materials/transmissive.h"

#include "lightsources/lightsource.h"
#include "lightsources/arealightsource.h"
#include "lightsources/volumelightsource.h"

#include <cmath>
#include <ctime>

void buildSceneSphere(Camera* &cam, Film* &film,
                      std::vector<Shape*>* &objectsList,
                      std::vector<LightSource*>* &lightSourceList)
{
    /* **************************** */
    /* Declare and place the camera */
    /* **************************** */
    //  By default, this gives an ID transform
    //  which means that the camera is located at (0, 0, 0)
    //  and looking at the "+z" direction
    Matrix4x4 cameraToWorld;
    double fovDegrees = 60;
    double fovRadians = Utils::degreesToRadians(fovDegrees);
    cam = new PerspectiveCamera(cameraToWorld, fovRadians, *film);

    /* ************************** */
    /* DEFINE YOUR MATERIALS HERE */
    /* ************************** */
    // (...)
    //  EXAMPLE:  Material *green_50 = new Phong (Vector3D(0.2, 0.7, 0.3), Vector3D(0.2, 0.6, 0.2), 50);
	// Specular, Diffuse & Shineness coefficient
    Material *green_50 = new Phong(Vector3D(0.2, 0.7, 0.3), Vector3D(0.2, 0.6, 0.2), 50);
	Material *red_10 = new Phong(Vector3D(1, 0.0, 0.1), Vector3D(0.2, 0.6, 0.2), 10);
	Material *blue_20 = new Phong(Vector3D(0.0, 0.1, 0.6), Vector3D(0.2, 0.6, 0.2), 20);
    Material *white = new Phong(Vector3D(0.9,0.9,0.9), Vector3D(0.5,0.5,0.5), 5);

    /* ******* */
    /* Objects */
    /* ******* */
    // Create a heterogeneous list of objects of type shape
    // (some might be triangles, other spheres, plans, etc)
    objectsList = new std::vector<Shape*>;

    // Define and place a sphere
    Matrix4x4 sphereTransform1;
    sphereTransform1 = sphereTransform1.translate(Vector3D(-1.0, -0.5, 2*std::sqrt(2.0)));
    Shape *s1 = new Sphere (0.25, sphereTransform1, green_50);

    Matrix4x4 sphereTransform2;
    sphereTransform2 = sphereTransform2.translate(Vector3D(1.0, 0.0, 6));
    Shape *s2 = new Sphere (1, sphereTransform2, red_10);

    Matrix4x4 sphereTransform3;
    sphereTransform3 = sphereTransform3.translate(Vector3D(0.3, -0.75, 3.5));
    Shape *s3 = new Sphere (0.25, sphereTransform3, blue_20);

    //Planes
    Shape *ip1 = new InfinitePlane(Vector3D(0,0,20), Vector3D(0,0,-1), white);
    Shape *ip2 = new InfinitePlane(Vector3D(-10,0,0), Vector3D(1,0,0), white);
    Shape *ip3 = new InfinitePlane(Vector3D(10,0,0), Vector3D(-1,0,0), white);

    // Store the objects in the object list
    objectsList->push_back(s1);
    objectsList->push_back(s2);
    objectsList->push_back(s3);
    objectsList->push_back(ip1);
    objectsList->push_back(ip2);
    objectsList->push_back(ip3);
    std::cout << objectsList->size() << "\n";

    /* ****** */
    /* Lights */
    /* ****** */
    // ADD YOUR LIGHT SOURCES HERE
	lightSourceList = new std::vector<LightSource*>;
	LightSource* l1 = PointLightSource(Vector3D(6.0, 0.0, 0.0), Vector3D(100.0, 100.0, 100.0));
	LightSource* l2 = PointLightSource(Vector3D(0.0, 10.0, 10.0), Vector3D(100.0, 100.0, 100.0));
    LightSource* l3 = PointLightSource(Vector3D(-6.0, 0.0, 0.0), Vector3D(100.0, 100.0, 100.0));
	// DO NOT FORGET TO STORE THE LIGHT SOURCES IN THE "lightSourceList"
	lightSourceList->push_back(l1);
	lightSourceList->push_back(l2);
    lightSourceList->push_back(l3);

}

void buildSceneCornellBox(Camera* &cam, Film* &film,
                          std::vector<Shape*>* &objectsList, std::vector<LightSource*>* &lightSourceList)
{
    /* **************************** */
    /* Declare and place the camera */
    /* **************************** */
    Matrix4x4 cameraToWorld = Matrix4x4::translate(Vector3D(0, 0, -3));
    double fovDegrees = 60;
    double fovRadians = Utils::degreesToRadians(fovDegrees);
    cam = new PerspectiveCamera(cameraToWorld, fovRadians, *film);

    /* ********* */
    /* Materials */
    /* ********* */
    Material *redDiffuse   = new Phong(Vector3D(0.7, 0.2, 0.3), Vector3D(0, 0, 0), 100);
    Material *greenDiffuse = new Phong(Vector3D(0.2, 0.7, 0.3), Vector3D(0, 0, 0), 100);
    Material *greyDiffuse  = new Phong(Vector3D(0.8, 0.8, 0.8), Vector3D(0, 0, 0), 100);
    Material *blueDiffuse  = new Phong(Vector3D(0.3, 0.2, 0.7), Vector3D(0, 0, 0), 100);
    Material *transmissive = new Transmissive(1.1, Vector3D(1));
    Material *mirror       = new Mirror(Vector3D(1, 0.9, 0.85));
    Material *red_100      = new Phong(Vector3D(0.7, 0.2, 0.3), Vector3D(0.7, 0.7, 0.2), 100);

    /* ******* */
    /* Objects */
    /* ******* */
    objectsList = new std::vector<Shape*>;
    double offset = 3.0;
    Matrix4x4 idTransform;
    // Construct the Cornell Box
    Shape *leftPlan   = new InfinitePlane(Vector3D(-offset, 0, 0), Vector3D(1,  0, 0), redDiffuse  );
    Shape *rightPlan  = new InfinitePlane(Vector3D( offset, 0, 0), Vector3D(-1, 0, 0), greenDiffuse);
    Shape *topPlan    = new InfinitePlane(Vector3D( 0, offset, 0), Vector3D(0, -1, 0), greyDiffuse);
    Shape *bottomPlan = new InfinitePlane(Vector3D( 0, -offset, 0), Vector3D(0, 1, 0), greyDiffuse);
    Shape *backPlan   = new InfinitePlane(Vector3D( 0, 0, 3*offset), Vector3D(0, 0, -1), blueDiffuse);
    objectsList->push_back(leftPlan);
    objectsList->push_back(rightPlan);
    objectsList->push_back(topPlan);
    objectsList->push_back(bottomPlan);
    objectsList->push_back(backPlan);

    // Place the Spheres inside the Cornell Box
    Matrix4x4 sphereTransform1;
    double radius = 1;
    sphereTransform1 = Matrix4x4::translate(Vector3D(-offset+radius, -offset+radius, 3.5));
    Shape *s1 = new Sphere (1.5, sphereTransform1, mirror);
    Matrix4x4 sphereTransform2;
    sphereTransform2 = Matrix4x4::translate(Vector3D(1.0, 0.0, 2));
    Shape *s2 = new Sphere (1, sphereTransform2, transmissive);
    Matrix4x4 sphereTransform3;
    radius = 1;
    sphereTransform3 = Matrix4x4::translate(Vector3D(0.3, -offset + radius, 5));
    Shape *s3 = new Sphere (radius, sphereTransform3, red_100);
    objectsList->push_back(s1);
    objectsList->push_back(s2);
    objectsList->push_back(s3);

    /* ****** */
    /* Lights */
    /* ****** */
    lightSourceList = new std::vector<LightSource*>;
    Vector3D lightPosition1 = Vector3D(0, offset-1, 2*offset);
    Vector3D lightPosition2 = Vector3D(0, offset-1, 0);
    Vector3D lightPosition3 = Vector3D(0, offset-1, offset);
    Vector3D intensity = Vector3D(10, 10, 10); // Radiant intensity (watts/sr)
    LightSource* pointLS1 = PointLightSource(lightPosition1, intensity);
    LightSource* pointLS2 = PointLightSource(lightPosition2, intensity);
    LightSource* pointLS3 = PointLightSource(lightPosition3, intensity);
    //lightSourceList->push_back(pointLS1);
    //lightSourceList->push_back(pointLS2);
    //lightSourceList->push_back(pointLS3);
    LightSource* quadLS1 = new QuadLightSource(Vector3D(0, offset, offset), intensity, 30, Vector3D(0,-1,0),
                                               Vector3D(1,0,0), 1, 1);
    LightSource* quadLS2 = new QuadLightSource(Vector3D(-offset, 0, offset), intensity, 30, Vector3D(1,0,0),
                                               Vector3D(0,1,0), 1, 1);
    LightSource* quadBack1 = new QuadLightSource(Vector3D(0,0,3*offset), intensity, 30, Vector3D(0,0,-1),
                                                 Vector3D(0,1,0), offset, offset);
    LightSource* quadBack2 = new QuadLightSource(Vector3D(0,0,2.5*offset), intensity, 30, Vector3D(0,0,1),
                                                 Vector3D(0,1,0), offset, offset);
    LightSource* quadFront = new QuadLightSource(Vector3D(0,0,0), intensity, 30, Vector3D(0,0,1),
                                                 Vector3D(1,0,0), offset, offset);
    LightSource* ellipseBack1 = new QuadLightSource(Vector3D(0,0,3*offset), intensity, 50, Vector3D(0,0,-1),
                                                 Vector3D(0,1,0), offset, offset);
    LightSource* ellipseBack2 = new QuadLightSource(Vector3D(0,0,2.5*offset), intensity*9, 200, Vector3D(0,0,1),
                                                 Vector3D(0,1,0), offset, offset);
    LightSource* sphereLS1 = new SphereLightSource(Vector3D(0,0,1.5*offset), intensity*2, 100, Vector3D(1,0,0),
                                                   Vector3D(0,1,0), 1);
    //lightSourceList->push_back(quadLS1);
    //lightSourceList->push_back(quadLS2);
    //lightSourceList->push_back(quadBack1);
    //lightSourceList->push_back(quadBack2);
    //lightSourceList->push_back(quadFront);
    //lightSourceList->push_back(ellipseBack1);
    //lightSourceList->push_back(ellipseBack2);
    //lightSourceList->push_back(sphereLS1);
}

void buildSceneTest(Camera* &cam, Film* &film,
                          std::vector<Shape*>* &objectsList, std::vector<LightSource*>* &lightSourceList)
{
    /* **************************** */
    /* Declare and place the camera */
    /* **************************** */
    Matrix4x4 cameraToWorld = Matrix4x4::translate(Vector3D(0, 0, -3));
    double fovDegrees = 60;
    double fovRadians = Utils::degreesToRadians(fovDegrees);
    cam = new PerspectiveCamera(cameraToWorld, fovRadians, *film);

    /* ********* */
    /* Materials */
    /* ********* */
    Material *redDiffuse   = new Phong(Vector3D(0.7, 0.2, 0.3), Vector3D(0, 0, 0), 100);
    Material *greenDiffuse = new Phong(Vector3D(0.2, 0.7, 0.3), Vector3D(0, 0, 0), 100);
    Material *greyDiffuse  = new Phong(Vector3D(0.8, 0.8, 0.8), Vector3D(0, 0, 0), 100);
    Material *blueDiffuse  = new Phong(Vector3D(0.3, 0.2, 0.7), Vector3D(0, 0, 0), 100);
    Material *transmissive = new Transmissive(1.1, Vector3D(1));
    Material *mirror       = new Mirror(Vector3D(1, 0.9, 0.85));
    Material *red_100      = new Phong(Vector3D(0.7, 0.2, 0.3), Vector3D(0.7, 0.7, 0.2), 100);

    /* ******* */
    /* Objects */
    /* ******* */
    objectsList = new std::vector<Shape*>;
    double offset = 3.0;
    Matrix4x4 idTransform;
    Shape *bottomPlan = new InfinitePlane(Vector3D( 0, -0.7, 0), Vector3D(0, 1, 0), greyDiffuse);
    objectsList->push_back(bottomPlan);

    // Place the Spheres inside the Cornell Box
    Matrix4x4 sphereTransform1;
    sphereTransform1 = Matrix4x4::translate(Vector3D(0, 0, 0));
    Shape *s1 = new Sphere (0.5, sphereTransform1, redDiffuse);
    objectsList->push_back(s1);

    /* ****** */
    /* Lights */
    /* ****** */
    lightSourceList = new std::vector<LightSource*>;
    Vector3D lightPosition1 = Vector3D(offset,offset,0);
    Vector3D intensity = Vector3D(10, 10, 10)*10; // Radiant intensity (watts/sr)
    LightSource* pointLS1 = PointLightSource(lightPosition1, intensity);
    LightSource* quadLS1 = new QuadLightSource(lightPosition1, intensity, 100, Vector3D(0,-1,0), Vector3D(1,0,0),3,3);
    LightSource* ellipseLS1 = new EllipseLightSource(lightPosition1, intensity, 50, Vector3D(0,-1,0), Vector3D(1,0,0),3,3);
    LightSource* sphereLS1 = new SphereLightSource(lightPosition1, intensity, 30, Vector3D(1,0,0), Vector3D(0,1,0), 1);
    LightSource* sphereLS2 = new SphereLightSource(Vector3D(-offset,offset,0), intensity, 30, Vector3D(1,0,0), Vector3D(0,1,0), 1);
    LightSource* cylLS1 = new CylinderLightSource(lightPosition1, intensity, 200, Vector3D(1,0,0), Vector3D(0,1,0), 1, 0.5);
    LightSource* focusLS1 = new FocusLightSource(lightPosition1, intensity, 1, -lightPosition1, M_PI_4/4);
    LightSource* focusALS1 = new FocusAreaLightSource(lightPosition1, intensity, 100, -lightPosition1, M_PI_4/4, 1);
    LightSource* focusALS2 = new FocusAreaLightSource(Vector3D(-offset,offset,0), intensity, 1000, -Vector3D(-offset,offset,0), M_PI_4/4, 1);

    //lightSourceList->push_back(pointLS1);
    //lightSourceList->push_back(quadLS1);
    //lightSourceList->push_back(ellipseLS1);
    //lightSourceList->push_back(sphereLS1);
    //lightSourceList->push_back(sphereLS2);
    //lightSourceList->push_back(cylLS1);
    //lightSourceList->push_back(focusLS1);
    lightSourceList->push_back(focusALS1);
    //lightSourceList->push_back(focusALS2);
}

void raytrace(Camera* &cam, Shader* &shader, Film* &film,
              std::vector<Shape*>* &objectsList, std::vector<LightSource*>* &lightSourceList)
{
    unsigned int sizeBar = 40;

    size_t resX = film->getWidth();
    size_t resY = film->getHeight();

    // Main raytracing loop
    // Out-most loop invariant: we have rendered lin lines
    for(size_t lin=0; lin<resY; lin++)
    {
        // Inner loop invariant: we have rendered col columns
        for(size_t col=0; col<resX; col++)
        {
            // Compute the pixel position in NDC
            double x = (double)(col + 0.5) / resX;
            double y = (double)(lin + 0.5) / resY;

            // Generate the camera ray
            Ray cameraRay = cam->generateRay(x, y);
            //cameraRay = cam->generateRay(0.5, 0.5);

            // Compute ray color according to the used shader
            Vector3D pixelColor = shader->computeColor( cameraRay, *objectsList, *lightSourceList );

            // Store the pixel color
            film->setPixelValue(col, lin, pixelColor);
        }
    }
}

int main()
{
	const clock_t begin_time = clock();


    std::string separator     = "\n----------------------------------------------\n";
    std::string separatorStar = "\n**********************************************\n";
    std::cout << separator << "RTIS - Ray Tracer for \"Imatge Sintetica\"" << separator << std::endl;

    // Create an empty film
    Film *film;
    film = new Film(720, 576);


    // Declare the shader
    Vector3D bgColor(0.0, 0.0, 0.0); // Background color (for rays which do not intersect anything)
    Vector3D intersectionColor(1,0,0);
    //Shader *shader = new IntersectionShader (intersectionColor, bgColor);
	//Shader *shader = new NormalShader(bgColor);
    //Shader *shader = new DepthShader(Vector3D(0.4, 1, 0.4), 40, bgColor);
	Shader *shader = new DirectShader(bgColor);
    //Shader *shader = new GlobalShader(bgColor, Vector3D(0.1,0.1,0.1));

    // Declare pointers to all the variables which describe the scene
    Camera *cam;
    std::vector<Shape*> *objectsList;
    std::vector<LightSource*> *lightSourceList;

    // Build the scene
    //buildSceneSphere(cam, film, objectsList, lightSourceList);
    //buildSceneCornellBox(cam, film, objectsList, lightSourceList);
    buildSceneTest(cam, film, objectsList, lightSourceList);

    // Launch some rays!
    raytrace(cam, shader, film, objectsList, lightSourceList);

    // Save the final result to file
    std::cout << "\nSaving the result to file output.bmp\n" << std::endl;
    film->save();

	std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << "\n\n\n";
    return 0;
}
