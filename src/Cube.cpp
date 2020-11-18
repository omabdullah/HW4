#include "Cube.h"
#include <limits>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

// reference: https://www.scratchapixel.com/code.php?id=10&origin=/lessons/3d-basic-rendering/ray-tracing-rendering-simple-shapes&src=1

HitRecord Cube::intersect(const Ray& ray)
{
    HitRecord hit;
    hit.t = -1;
    float tmin, tmax, tymin, tymax, tzmin, tzmax; // gets 3d coordinates for each axis

    tmin = (vmin[0] - ray.origin[0]) / ray.direction[0]; // calculates each 3d coordinates of each axis here
    tmax = (vmax[0] - ray.origin[0]) / ray.direction[0];
    tymin = (vmin[1] - ray.origin[1]) / ray.direction[1];
    tymax = (vmax[1] - ray.origin[1]) / ray.direction[1];

    if (tmin > tmax)
    {
        float temp = tmin;
        tmin = tmax;
        tmax = temp;
    }

    if (tymin > tymax)
    {
        float temp = tymin;
        tymin = tymax;
        tymax = temp;
    }

    if ((tmin > tymax) || (tymin > tmax))
        return hit;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (vmin[2] - ray.origin[2]) / ray.direction[2];
    tzmax = (vmax[2] - ray.origin[2]) / ray.direction[2];

    if (tzmin > tzmax)
    {
        float temp = tzmin;
        tzmin = tzmax;
        tzmax = temp;
    }

    if ((tmin > tzmax) || (tzmin > tmax))
        return hit;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    float tVar = tmin;
    if (tVar < 0)
    {
        tVar = tmax;
        if (tVar < 0)
            return hit;
    }

    Vector3d normalVector = -vmax.normalized();

    hit.normal = normalVector;
    hit.t = tVar;
    hit.position = ray.origin + ray.direction * tVar;
    hit.sh = this;
    return hit;
}
