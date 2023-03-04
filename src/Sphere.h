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
#define DEFAULT_CENTRE (new Vector3f(1.0f, 1.0f, 1.0f))

// Sphere is a type of geometry
class Sphere : public Geometry{

private:

    float radius; // size of the radius of the sphere
    Vector3f *centre; // centre of the sphere in 3d space

public:

    //-------------
    // constructors
    Sphere();

    Sphere(float radius, Vector3f *centre);

    Sphere(float ambientReflection, float diffuseReflection, float specularReflection, float phongCoefficient,
           const RGBColor &ambientColor, const RGBColor &diffuseColor, const RGBColor &specularColor, float radius,
           Vector3f *centre);
    //-------------

    //--------------------
    // getters and setters
    float getRadius() const{ return radius;};

    Vector3f *getCentre() const{ return centre;};

    void setRadius(float radius){
        if(checkRadius(radius))
            this->radius = radius;
        else
            invalidRadiusSize();
    };

    void setCentre(Vector3f *centre){ this->centre = centre;};
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

    //------------------
    // utility functions
    Vector3f* intersect(Ray* ray) override;
    //------------------


};


#endif //RAYTRACER_SPHERE_H
