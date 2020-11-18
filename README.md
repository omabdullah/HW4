# HW4

PSID: 1838738 Osama Abdullah

THe objective of this assignment is to utilize a barebones ray tracing program to implement additional shapes, add Phong and colored shading, the ability to cast shadows, and finally support for mirrored surfaces which reflect the rays of light according to the law of reflection. 

We are given a handful of files as the source code. Image.h/cpp, which provides the functionality of outputting the png files that we will be viewing to see the result of each feature, using a core function, libpng. We are also given Sphere.h/cpp which provides us the source code to generate spheres on the canvas, three of which have already been placed by default. We also have a very notable file, one of which a lot of time is spent to implement essential features, such as the phong and colored shading, and also shadow and reflection support. Another notable file is the main.cpp, which initiates the entire project, setting up the scene, ray tracing, saves the output. The main.cpp is where we will define coordinates and other variables to initialize new shapes into the program.

For this assignment, similar to the previous homeworks, we will be using Visual Studio on Windows, however, OpenGL will not be used for any part of this assignment and will only purely use Eigen and the Raytracer148 libraries. A side note, should the program have compiliation errors, be sure to update the Eigen dependency with the latest version (Eigen 3.3.8), which can be found here https://gitlab.com/libeigen/eigen/-/releases/3.3.8 . You can simply delete the old Eigen files and paste the new ones and it should run as intended.

After the aforementioned concerns are addressed, you should be able to simply compile the code from the repository and be able to view the test.png that is generated from the code.

Now we will begin to go through the features of the program by first demonstrating the finished product.
![FinishedProduct](https://github.com/omabdullah/HW4/blob/main/problem4complete.png?raw=true "FinishedProduct")

As we can see in this output, an additional shape was created, which in this case is a rectangular object. The objects are shaded with different colors, while using the Phong shading technique that was learned from the previous assignment. We can also note that shadowing and light reflection has also been implemented in this finished product.

![Problem1](https://github.com/omabdullah/HW4/blob/main/problem1.png?raw=true "Problem1")

Now, the first problem of the assignment asks us to implement an additional shape to the program, which may at a first glance seem to be an easy task, but this arguably took the most amount of time. It is created through the new Cube.cpp and Cube.h files. Beginning with the Cube.h header file, we can immediately notice it is very similar to the Sphere's header file, which takes in variables v1 and v2 and sets vmin to v1 and vmax to v2. This allows us to set the coordinates and size of the cube accurately along the x, y, and z axis. This is followed by the HitRecord insersect(const Ray& ray) function, which allows us to intersect a ray through what is called the "intersection test" to check if lines are intersecting with each other to properly form that object. We also have the Cube.cpp file where all the magic truly happens. We can immediately see within this file that we have several float variables, known as tmin, tmax, tymin, tymax, tzmin, tzmax. These allow us to log exactly the extent and boundaries that the object can go on each axis, x, y, and z. We can see this occurring in the following line for example: tmin = (vmin[0] - ray.origin[0]) / ray.direction[0];. This marks the minimum for the x axis, while tmax = (vmax[0] - ray.origin[0]) / ray.direction[0]; intuitevely logs the maximum by simply subtracting from the vmax on the [0] index which signifies the x axis, whereas [1] would be y, etc. After these min and maxes are properly adjusted, the normal is calculated into a Vector3d by the following: Vector3d normal = -vmax.normalized(); Finally, we return the the normal, position, and t value.



![Problem2](https://github.com/omabdullah/HW4/blob/main/problem2color.png?raw=true "Problem2")
![Problem2.5](https://github.com/omabdullah/HW4/blob/main/problem2phong.png?raw=true "Problem2.5")

As you can see here, first the color was added as shown in the left image, followed by the full Phong shading in the second image, we achieve this simutaneously by allowing the sphere and the newly developed rectangular object to take in three additional variables: kamb, kdif, and kspec. These define the ambient, diffusion, and specular values while also manipulating the color simutaneously by taking them as arguments in main such as "scene.addShape(new Sphere(center, 2, kAmb, kDif, kSpec));" To go over this, it takes the center, the radius, and the three aforementioned Phong essential variables. These variables in return allow for the calculation of Phong shading. Since we already have diffuse given to us, we just have to add on ambient and specular. We take the ambient value and add it onto our result while the equation for specular is also added on like our previous assignment as such "pow(r.normal.normalized().dot((-ray.direction.normalized() + lightDir).normalized()), 32)". This gives us our completed coloring and Phong shading feature.

![Problem3](https://github.com/omabdullah/HW4/blob/main/problem3shadows.png?raw=true "Problem3")

As you can notably observe, shadows within this image have been implemented. This process was rather simple in comparison to the other features as it only requires a few steps. We create a new Ray called shadowRay which stores in the member variables of origin and direction the r.position and lightDir by the following:    
    Ray shadowRay;
   shadowRay.origin = r.position;
   shadowRay.direction = lightDir;
Then, a for loop (shown below) is created to go through the amount of shapes and then using the position and light source to color the area where light does not reach, making it black, in return creating our shadow. This is done through the intersect function on the shadowRay ray. 
    for (unsigned int i = 0; i < shapes.size(); i++) {
        HitRecord r = shapes[i]->intersect(shdws);
        if (r.t > 0.00000000001) return result;
    }

![Problem4](https://github.com/omabdullah/HW4/blob/main/problem4complete.png?raw=true?raw=true "Problem4")

Finally, we can add support for the light reflection onto our objects, which in the above image is shown as the white bubble on the spheres, reflecting from the ray of light's positioning.
This is done by manipulating the result by adding the Phong shading and coloring to the reflection. We create a reflectionRay and when the ray hits an object, we get the hit position, which then we calculate the direction it would reflect using a formula known as I - 2.0 * dot(N, I) * N. Then we cast another ray from the hit position of the original in the direction of the reflection. We store the result of the aforementioned formula in a Vector3d variable called ref, and create a reflectingRay Ray, storing the origin from r.position and direction from the Vector3d ref (the formula). After this, we want to trace the reflections onto the canvas by creating a counting flag and running an if/else statement. If the counter reaches over 2, it will return the result, but prior to this, in the else statement, it will increment the counter by one and return result + 0.5 * trace(reflectingRay). This will add onto the reflections to the result. You can notice reflections on the top two spheres on the edges and also a line reflection on the biggest sphere on the bottom left from the inserted rectangle.

References:
https://www.scratchapixel.com/lessons/3d-basic-rendering/phong-shader-BRDF

https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes

https://www.scratchapixel.com/code.php?id=10&origin=/lessons/3d-basic-rendering/ray-tracing-rendering-simple-shapes&src=1

https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/reflect.xhtml

https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel

https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/ligth-and-shadows




