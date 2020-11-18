#include "Scene.h"
#include <cmath>
using namespace Raytracer148;
using namespace std;
using namespace Eigen;

HitRecord Scene::closestHit(const Ray& ray) {
    HitRecord result;
    result.t = -1;
    bool foundSomething = false;

    for (unsigned int i = 0; i < shapes.size(); i++) {
        HitRecord r = shapes[i]->intersect(ray);
        if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) {
            result = r;
            foundSomething = true;
        }
    }

    return result;
}


// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray& ray) {
    // For now we'll have diffuse shading with no shadows, so it's easy!
    HitRecord r = closestHit(ray);

    Vector3d result;
    result[0] = result[1] = result[2] = 0;

    if (r.t < numeric_limits<double>::epsilon()) return result;
    r.position = ray.origin + r.t * ray.direction - ray.direction * 0.00000000000001;

    //diffuse
    Vector3d lightDir = (lightPos - r.position).normalized();


    Ray shdws; // ray for shadows, problem 3
    shdws.origin = r.position;
    shdws.direction = lightDir;

    for (unsigned int i = 0; i < shapes.size(); i++) { // colors shadowed locations with black (problem 3)
        HitRecord r = shapes[i]->intersect(shdws);
        if (r.t > 0.00000000001) return result;
    }

    double dot = lightDir.dot(r.normal);
    if (dot < 0) dot = 0;

    result = r.sh->ks * pow(r.normal.normalized().dot((-ray.direction.normalized() + lightDir).normalized()), 32) + r.sh->kd * dot; // phong result, problem 2

    Vector3d ref; // generates location of reflection hits (problem 4)
    ref = ray.direction.normalized() - 2 * (ray.direction.normalized().dot(r.normal)) * r.normal;
    Ray reflectingRay;
    reflectingRay.origin = r.position;
    reflectingRay.direction = ref;

    if (counter > 2) { // keeps going until 2 reflection runs created (problem 4)
        return result;
    }
    else {
        counter++;
        return result = result + 0.5 * trace(reflectingRay);
    }
    return result;
}

void Scene::render(Image& image) {
    // We make the assumption that the camera is located at (0,0,0)
    // and that the image plane happens in the square from (-1,-1,1)
    // to (1,1,1).

    assert(image.getWidth() == image.getHeight());

    int size = image.getWidth();
    double pixelSize = 2. / size;
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++) {
            Ray curRay;
            curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;

            curRay.direction[0] = (x + 0.5) * pixelSize - 1;
            curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
            curRay.direction[2] = 1;

            Vector3d color = trace(curRay);
            image.setColor(x, y, color[0], color[1], color[2]);
        }
}