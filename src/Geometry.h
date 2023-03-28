//
// Created by Arnaud Jalbert on 2023-01-31.
//

#ifndef RAYTRACER_GEOMETRY_H
#define RAYTRACER_GEOMETRY_H

#include <string>
#include <ostream>

using std::string;

#include "RGBColor.h"
#include "Ray.h"

#define DEFAULT_REFLECTION (0.05f)
#define DEFAULT_PHONG (1.5f)
#define DEFAULT_COLOR RGBColor(0.5f, 0.5f, 0.5f)

class Geometry {

public:

    // reflection coefficients
    float ambientReflection; // float in range[0,1] → ambient reflection coefficient
    float diffuseReflection; // float in range[0,1] → diffuse reflection coefficient
    float specularReflection; // float in range[0,1] → specular reflection coefficient

    float phongCoefficient; // float in range]1,infinity[ → Phong coefficient

    // color properties
    RGBColor ambientColor; // [3 float] that represents a rgb color → ambient color
    RGBColor diffuseColor; // [3 float] that represents a rgb color → diffuse color
    RGBColor specularColor; // [3 float] that represents a rgb color → specular color
    
    //-------------
    // constructors

    Geometry(float ambientReflection, float diffuseReflection, float specularReflection, float phongCoefficient,
             const RGBColor &ambientColor, const RGBColor &diffuseColor, const RGBColor &specularColor);
    //-------------

    //----------------------
    // operators overloading
    friend std::ostream &operator<<(std::ostream &os, const Geometry &geometry);
    //----------------------

    //------------------
    // utility functions
    static float vectorDistance(Vector3f origin, Vector3f destination );

    virtual Vector3f* intersect(Ray* ray) = 0; // to be overwritten by the inherited geometries
    //------------------

};


#endif //RAYTRACER_GEOMETRY_H
