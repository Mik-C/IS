#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <vector>
#include <algorithm>

#include "core/film.h"
#include "core/matrix4x4.h"
#include "core/ray.h"
#include "core/utils.h"
#include "core/filter.h"
#include "shapes/sphere.h"
#include "cameras/ortographic.h"
#include "cameras/perspective.h"

void transformationsExercise() {
    /* *************** */
    /* TRANSFORMATIONS */
    /* *************** */
    std::string separator = "\n----------------------------------------------\n";
    std::string separatorStar = "\n**********************************************\n";

    std::cout << separatorStar << "Construct and visualize transforms" << separatorStar << std::endl;

    // Identity Matrix
    Matrix4x4 idMat; // By default, a matrix4x4 is initialized with the identity matrix
    std::cout << "The content of matrix idMat is: \n" << std::endl;
    std::cout << idMat << separator << std::endl;

    // Translation Matrix
    double deltaX, deltaY, deltaZ;
    deltaX = 1;
    deltaY = -2;
    deltaZ = 3;
    Vector3D delta(deltaX, deltaY, deltaZ);
    Matrix4x4 translationMat = Matrix4x4::translate(delta);
    std::cout << "The content of matrix translationMat is: \n" << std::endl;
    std::cout << translationMat << separator << std::endl;

    // Scale Matrix
    Vector3D scaleFactor(2, 1, -1);
    Matrix4x4 scaleMatrix = Matrix4x4::scale(scaleFactor);
    std::cout << "The content of matrix scaleMatrix is: \n" << std::endl;
    std::cout << scaleMatrix << separator << std::endl;

    // Rotate around X Matrix
    double angleInDegrees = 60;
    double thetaInRadians = Utils::degreesToRadians(angleInDegrees);
    Vector3D rotateXAxis(1, 0, 0);
    Matrix4x4 rotateXMatrix = Matrix4x4::rotate(thetaInRadians, rotateXAxis);
    std::cout << "The content of matrix rotateXMatrix is: \n" << std::endl;
    std::cout << rotateXMatrix << separator << std::endl;

    // Rotate around an arbitrary axis Matrix
    double theta = Utils::degreesToRadians(30);
    Vector3D rotateAxis(1, 1, 1);
    Matrix4x4 rotateArtitraryAxisMatrix = Matrix4x4::rotate(theta, rotateAxis);
    std::cout << "The content of matrix rotateArtitraryAxisMatrix is: \n" << std::endl;
    std::cout << rotateArtitraryAxisMatrix << separator << std::endl;

    // Transposed and Inversion
    std::cout << separatorStar << "Inverting and Transposing a Matrix" << separatorStar << std::endl;
    Matrix4x4 translationMatTransposed;
    translationMat.transpose(translationMatTransposed);
    std::cout << "The transpose of matrix \n\n" << translationMat << "\n is \n\n"
              << translationMatTransposed << separator << std::endl;

    Matrix4x4 inverseTranslationMat;
    translationMat.inverse(inverseTranslationMat);
    std::cout << "The inverse of matrix \n\n" << translationMat << "\n is \n\n" << inverseTranslationMat << std::endl;
    std::cout << "And their multiplication should thus give the identity matrix:\n\n";
    std::cout << translationMat * inverseTranslationMat;

    // Combine here some transforms, and visualize the result
    std::cout << separatorStar << "Combine transforms and visualize the result" << separatorStar << std::endl;

    //Matrix4x4 scaleTranslate = (...);
    Matrix4x4 scaleTranslate = scaleMatrix * translationMat;
    std::cout << "The content of matrix scaleTranslate is: \n" << std::endl;
    std::cout << scaleTranslate << separator << std::endl;

    //Matrix4x4 translateScale = (...);
    Matrix4x4 translateScale = translationMat * scaleMatrix;
    std::cout << "The content of matrix translateScale is: \n" << std::endl;
    std::cout << translateScale << separator << std::endl;
}

void normalTransformExercise() {
    std::string separator = "\n----------------------------------------------\n";

    // NOTE: points, vectors and normals are represented, in this framework, using
    //  the Vector3D class. It is up to the programmer to take care of whether the
    //  Vector3D is representing a point, a vector or a normal. For example, when
    //  applying a transform using a Matrix4x4, the programmer must choose which
    //  "applyTransform" method of the namespace Matrix4x4 should be used.

    Vector3D v(1, 1, 0);
    Vector3D n(-1.0 / sqrt(2), 1.0 / sqrt(2), 0);
    Matrix4x4 S = Matrix4x4::scale(Vector3D(2, 1, 1));

    std::cout << "Vector v = " << v << "\n" << std::endl;
    std::cout << "Normal n = " << n << "\n" << std::endl;
    std::cout << "Scale Matrix: \n" << std::endl;
    std::cout << S << std::endl;

    Vector3D vTransformed = S.transformVector(v);
    std::cout << "Vector v\' = " << vTransformed << "\n" << std::endl;

    Vector3D nTransformed = S.transformVector(n);
    std::cout << "Vector n\' = " << nTransformed << "\n\n";

    std::cout << "dot(n\', v\') = " << dot(nTransformed, vTransformed) << "\n\n";

    S.transpose(S);
    S.inverse(S);

    nTransformed = S.transformVector(n);
    std::cout << "Vector n\' = " << nTransformed << "\n\n";
    std::cout << "dot(n\', v\') = " << dot(nTransformed, vTransformed) << "\n\n";
}

void paintingAnImageExercise() {
    // Define the film (i.e., image) resolution
    size_t resX, resY;
    resX = 512;
    resY = 512;
    Film film(resX, resY);

    for (unsigned int col = 0; col < resX; col++) {
        for (unsigned int row = 0; row < resY; row++) {
            Vector3D color((col + 0.5) / resX, (row + 0.5) / resY, 0);
            film.setPixelValue(col, row, color);
        }
    }

    // Save the final result to file
    film.save("gaussFilter.bmp");
}

void initFilm(Film* f, int resX, int resY) {
    // Create the original image
    //  Draw a circle centered at centerX, centerY (in pixels, image space)
    //   and with ray r (also in pixels)
    int centerX = resX / 2;
    int centerY = resY / 2;
    int r = std::min(centerX, centerY) / 2;

    for (int lin = 0; lin < resX; lin++) {
        for (int col = 0; col < resY; col++) {
            // Use the equation of the sphere to determine the pixel color
            if ((lin - centerX) * (lin - centerX) + (col - centerY) * (col - centerY) < r * r) {
                Vector3D v(1, 1, 0);
                f->setPixelValue(col, lin, v);
            }
        }
    }
}

void filteringAnImageExercise() {
    // Create two instances of the film class with the same resolution
    int resX, resY;
    resX = 512;
    resY = 512;
    Film f1(resX, resY);
    Film f2(resX, resY);

    // Filter-related variables
    // Declare here your filter-related variables
    // (e.g., FILTER SIZE)
    int iterations = 100;
    Filter *filter = new Filter();
    Film *read, *write, *temp;

    // Implement here your image filtering algorithm
    // MEAN Filter
    std::cout << "Mean filter . . . \n";

    initFilm(&f1, resX, resY);
    filter->setMean(3, 3);
    read = &f1;
    write = &f2;
    for (int it = 0; it < iterations; it++) {
        filter->convolution(read, write);

        temp = read;
        read = write;
        write = temp;
    }
    read->save("meanFilter.bmp");
    std::cout << "Done!\n";

    // GAUSS Filter
    std::cout << "Gauss filter . . . \n";

    initFilm(&f1, resX, resY);
    filter->setGauss(3, 3);
    read = &f1;
    write = &f2;
    for (int it = 0; it < iterations; it++) {
        filter->convolution(read, write);

        temp = read;
        read = write;
        write = temp;
    }
    read->save("gaussFilter.bmp");
    std::cout << "Done!\n";
}

void completeSphereClassExercise() {
    // Make your intersection tests here
    Matrix4x4 transform;
    transform = transform.translate(Vector3D(0, 0, 3));
    Sphere s = Sphere(1, transform);
    Ray r1 = Ray(Vector3D(0, 0, 0), Vector3D(0, 0, 1));
    Ray r2 = Ray(Vector3D(0, 0, 0), Vector3D(0, 1, 0));

    std::cout << "Sphere s:\n" << s << "\n";
    std::cout << "Ray r1:\n" << r1 << "\n";
    std::cout << "Ray r2:\n" << r2 << "\n";

    std::cout << "Intersection of ray r1 with the sphere: " << string(s.rayIntersectP(r1) ? "True" : "False") << "\n";
    std::cout << "Intersection of ray r2 with the sphere: " << string(s.rayIntersectP(r2) ? "True" : "False") << "\n";
}

void eqSolverExercise() {
    EqSolver solver;
    rootValues roots;

    double A, B, C;

    A = 5;
    B = 6;
    C = 1;

    bool hasRoots = solver.rootQuadEq(A, B, C, roots);

    if (!hasRoots) {
        std::cout << "Equation " << A << "x^2 + " << B << "x + " << C << " has no real roots!" << std::endl;
    } else {
        std::cout << "Equation " << A << "x^2 + " << B << "x + " << C << " solution:\n";
        for (int i = 0; i < roots.nValues; i++)
            std::cout << "\tx = " << roots.values[i] << "\n";
        std::cout << "\n";
    }

    A = 5;
    B = 2;
    C = 1;

    hasRoots = solver.rootQuadEq(A, B, C, roots);

    if (!hasRoots) {
        std::cout << "Equation " << A << "x^2 + " << B << "x + " << C << " has no real roots!" << std::endl;
    } else {
        std::cout << "Equation " << A << "x^2 + " << B << "x + " << C << " solution:\n";
        for (int i = 0; i < roots.nValues; i++)
            std::cout << "\tx = " << roots.values[i] << "\n";
        std::cout << "\n";
    }
    std::cout << "\n";
}

void raytrace() {
    // Define the film (i.e., image) resolution
    size_t resX, resY;
    resX = 512;
    resY = 512;
    Film film(resX, resY);

    Matrix4x4 transform;
    transform = transform.translate(Vector3D(0, 0, 3));
    Sphere s = Sphere(1, transform);

    Vector3D red = Vector3D(1, 0, 0);
    Vector3D black = Vector3D(0, 0, 0);

    /* ******************* */
    /* Orthographic Camera */
    /* ******************* */
    std::cout << "Orthographic raytracing . . . \n";

    Matrix4x4 cameraToWorld; // By default, this gives an ID transform
    // meaning that the camera space = world space
    OrtographicCamera camOrtho(cameraToWorld, film);

    for (int j = 0; j < resY; j++) {
        for (int i = 0; i < resX; i++) {
            double u = (i + 0.5) / (double) resX;
            double v = (j + 0.5) / (double) resY;
            Ray r = camOrtho.generateRay(u, v);
            if (s.rayIntersectP(r))
                film.setPixelValue(i, j, red);
            else
                film.setPixelValue(i, j, black);
        }
    }
    film.save("sphereOrtho.bmp");
    std::cout << "Done!\n";

    /* ******************* */
    /* Perspective Camera */
    /* ******************* */
    std::cout << "Perspective raytracing . . . \n";

    double fovRadians = Utils::degreesToRadians(60);
    PerspectiveCamera camPersp(cameraToWorld, fovRadians, film);

    for (int j = 0; j < resY; j++) {
        for (int i = 0; i < resX; i++) {
            double u = (i + 0.5) / (double) resX;
            double v = (j + 0.5) / (double) resY;
            Ray r = camPersp.generateRay(u, v);
            if (s.rayIntersectP(r))
                film.setPixelValue(i, j, red);
            else
                film.setPixelValue(i, j, black);
        }
    }
    film.save("spherePersp.bmp");
    std::cout << "Done!\n";
}

int main() {
    std::string separator = "\n----------------------------------------------\n";

    std::cout << separator << "RTIS - Ray Tracer for \"Imatge Sintetica\"" << separator << std::endl;

    // ASSIGNMENT 1
    transformationsExercise();
    normalTransformExercise();
    paintingAnImageExercise();
    filteringAnImageExercise();

    // ASSIGNMENT 2
    eqSolverExercise();
    completeSphereClassExercise();
    raytrace();

    std::cout << "\n\n" << std::endl;
    return 0;
}
