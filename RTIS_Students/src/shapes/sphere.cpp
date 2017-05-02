#include "sphere.h"

Sphere::Sphere(const double radius_, const Matrix4x4 &t_)
    : Shape(t_), radius(radius_)
{ }

bool Sphere::rayIntersectP(const Ray &ray) const
{
    // Pass the ray to local coordinates
    Ray r = worldToObject.transformRay(ray);

    // The ray-sphere intersection equation can be expressed in the
    // form A*t^2 + B*t + C = 0, where:
    // A = d_x^2 + d_y^2 + d_z^2
    // B = 2(o_x*d_x + o_y*d_y + o_z*d_z)
    // C = o_x^2 + o_y^2 + o_z^2 - r^2

    double A = r.d.x * r.d.x + r.d.y * r.d.y + r.d.z * r.d.z;
    double B = 2.0 * (r.o.x * r.d.x + r.o.y * r.d.y + r.o.z * r.d.z);
    double C = r.o.x * r.o.x + r.o.y * r.o.y + r.o.z * r.o.z - (radius * radius);

    // Now we need to solve this quadratic equation for t
    EqSolver solver;
    rootValues roots;

    return solver.rootQuadEq(A, B, C, roots);
}

std::string Sphere::toString() const
{
    std::stringstream s;
    s << "[ " << std::endl
      << " Center (World) = " << objectToWorld.transformPoint(Vector3D(0,0,0)) << ", Radius = " << radius << std::endl
      << "]" << std::endl;

    return s.str();
}

std::ostream& operator<<(std::ostream &out, const Sphere &s)
{
    out << s.toString();
    return out;
}
