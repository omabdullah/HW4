#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "Cube.h"
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
    Image im(400, 400);

    Scene scene;

    Vector3d center, kAmb, kDif, kSpec; // grabs phong variables (diffuse ambient specular)

    kAmb[0] = 0;
    kAmb[1] = 0.5;
    kAmb[2] = 0.5;

    kDif[0] = 0;
    kDif[1] = 1;
    kDif[2] = 1;

    kSpec[0] = kSpec[1] = kSpec[2] = 1.0;

    center[0] = 0;
    center[1] = 0;
    center[2] = 4;
    scene.addShape(new Sphere(center, 2, kAmb, kDif, kSpec));

    kAmb[0] = 0.1;
    kAmb[1] = 0;
    kAmb[2] = 0.3;

    kDif[0] = 0.75;
    kDif[1] = 0;
    kDif[2] = 0.55;

    center[0] = -.5;
    center[1] = 1;
    center[2] = 2.5;
    scene.addShape(new Sphere(center, .5, kAmb, kDif, kSpec));


    kAmb[0] = 0.5;
    kAmb[1] = 0;
    kAmb[2] = 0.3;

    kDif[0] = 0.5;
    kDif[1] = 0;
    kDif[2] = 0.5;

    center[0] = 0.5;
    center[1] = 1.25;
    center[2] = 2.75;
    scene.addShape(new Sphere(center, .5, kAmb, kDif, kSpec));

    kAmb[0] = 0.1;
    kAmb[1] = 0.1;
    kAmb[2] = 0;

    kDif[0] = 0.5;
    kDif[1] = 0.5;
    kDif[2] = 0;

    Vector3d min = Vector3d(-2.5, -2.5, 3.0); // 3d coordinates of cube, new shape for problem 1
    Vector3d max = Vector3d(-2.0, 2.0, 3.01);
    scene.addShape(new Cube(min, max, kAmb, kDif, kSpec)); // gets coordinates from above and diff/specular/ambient from above

    scene.render(im);
    im.writePNG("test.png");

    return 0;
}
