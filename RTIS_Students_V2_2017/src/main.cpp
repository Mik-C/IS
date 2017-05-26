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

#include "materials/phong.h"

void buildSceneSphere(Camera* &cam, Film* &film,
                      std::vector<Shape*>* &objectsList,
                      std::vector<PointLightSource>* &lightSourceList)
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

    // Store the objects in the object list
    objectsList->push_back(s1);
    objectsList->push_back(s2);
    objectsList->push_back(s3);
    objectsList->push_back(ip1);
    std::cout << objectsList->size() << "\n";

    /* ****** */
    /* Lights */
    /* ****** */
    // ADD YOUR LIGHT SOURCES HERE
	lightSourceList = new std::vector<PointLightSource>;
	PointLightSource l1 = PointLightSource(Vector3D(10.0, 0.0, 0.0), Vector3D(100.0, 100.0, 100.0));
	PointLightSource l2 = PointLightSource(Vector3D(0.0, 10.0, 10.0), Vector3D(100.0, 100.0, 100.0));
    PointLightSource l3 = PointLightSource(Vector3D(0.0, 0.0, 0.0), Vector3D(100.0, 100.0, 100.0));
	// DO NOT FORGET TO STORE THE LIGHT SOURCES IN THE "lightSourceList"
	//lightSourceList->push_back(l1);
	//lightSourceList->push_back(l2);
    lightSourceList->push_back(l3);

}

void raytrace(Camera* &cam, Shader* &shader, Film* &film,
              std::vector<Shape*>* &objectsList, std::vector<PointLightSource>* &lightSourceList)
{
    unsigned int sizeBar = 40;

    size_t resX = film->getWidth();
    size_t resY = film->getHeight();

    // Main raytracing loop
    // Out-most loop invariant: we have rendered lin lines
    for(size_t lin=0; lin<resY; lin++)
    {
        // Show progression
        if ( lin%(resY/sizeBar) == 0)
            std::cout << ".";

        // Inner loop invariant: we have rendered col columns
        for(size_t col=0; col<resX; col++)
        {
            // Compute the pixel position in NDC
            double x = (double)(col + 0.5) / resX;
            double y = (double)(lin + 0.5) / resY;

            if(x < 0.55 || x > 0.6 || y < 0.62 || y > 0.64)
                continue;

            std::cout << "\n" << lin << " " << col << "\n";

            // Generate the camera ray
            Ray cameraRay = cam->generateRay(x, y);

            // Compute ray color according to the used shader
            Vector3D pixelColor = shader->computeColor( cameraRay, *objectsList, *lightSourceList );

            // Store the pixel color
            film->setPixelValue(col, lin, pixelColor);
        }
    }
}

int main()
{
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
	Shader *shader = new Directshader(8, bgColor);

    // Declare pointers to all the variables which describe the scene
    Camera *cam;
    std::vector<Shape*> *objectsList;
    std::vector<PointLightSource> *lightSourceList;

    // Build the scene
    buildSceneSphere(cam, film, objectsList, lightSourceList);

    // Launch some rays!
    raytrace(cam, shader, film, objectsList, lightSourceList);

    // Save the final result to file
    std::cout << "\n\nSaving the result to file output.bmp\n" << std::endl;
    film->save();

    std::cout << "\n\n" << std::endl;
    return 0;
}
