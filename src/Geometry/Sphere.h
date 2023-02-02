//
// Created by Arnaud Jalbert on 2023-01-31.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include <Eigen/Dense>
#include <iostream>

#include "Geometry.h"

using std::cout;
using std::endl;
using Eigen::Vector3f;

#define DEFAULT_RADIUS (1.0f)
#define DEFAULT_CENTRE (Vector3f(1.0f, 1.0f, 1.0f))

// Sphere is a type of geometry
class Sphere : public Geometry{

private:

    float radius; // size of the radius of the sphere
    Vector3f centre; // centre of the sphere in 3d space

public:

    //-------------
    // constructors
    Sphere();

    Sphere(float radius, const Vector3f &centre);

    Sphere(float ambientReflection, float diffuseReflection, float specularReflection, float phongCoefficient,
           const RGBColor &ambientColor, const RGBColor &diffuseColor, const RGBColor &specularColor, float radius,
           const Vector3f &centre);
    //-------------

    //--------------------
    // getters and setters
    float getRadius() const;

    void setRadius(float radius);

    const Vector3f &getCentre() const;

    void setCentre(const Vector3f &centre);
    //--------------------

    //-------
    // checks
    static bool checkRadius(float radius);

    void invalidRadiusSize();
    //-------

    //---------------------
    // operator overloading
    friend std::ostream &operator<<(std::ostream &os, const Sphere &sphere);
    //---------------------


};


#endif //RAYTRACER_SPHERE_H
