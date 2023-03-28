//
// Created by Arnaud Jalbert on 2023-01-31.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include <iostream>
#include <memory>

#include "RGBColor.h"
#include "Ray.h"
#include "Geometry.h"


using std::cout;
using std::endl;

#define DEFAULT_LIGHT_INTENSITY (RGBColor(1.0, 1.0, 1.0))

class Light {

public:

    RGBColor diffuseIntensity; // intensity of the diffuse light
    RGBColor specularIntensity; // intensity of the specular light

    //-------------
    // constructors
    Light();
    //-------------

    //----------------------
    // operators overloading
    friend std::ostream &operator<<(std::ostream &os, const Light &light);
    //----------------------


};


#endif //RAYTRACER_LIGHT_H
