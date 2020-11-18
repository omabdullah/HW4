#ifndef Cube_h
#define Cube_h

#include "Shape.h"

namespace Raytracer148
{
    class Cube : public Shape
    {
    public:
        Cube(const Eigen::Vector3d& v1, const Eigen::Vector3d& v2, Eigen::Vector3d& kamb, Eigen::Vector3d& kdif, Eigen::Vector3d& kspec) : vmin(v1), vmax(v2) {  // takes in coordinates and ambient, diffusion, and specular variables
            ka = kamb;
            kd = kdif;
            ks = kspec;
        }
        virtual HitRecord intersect(const Ray& ray);

        Eigen::Vector3d vmin, vmax;
    };
}

#endif
