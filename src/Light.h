//
// Created by Arnaud Jalbert on 2023-01-31.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include <iostream>

#include "RGBColor.h"

using std::cout;
using std::endl;

#define DEFAULT_LIGHT_INTENSITY (RGBColor(1.0, 1.0, 1.0))

class Light {

private:

    RGBColor diffuseIntensity; // intensity of the diffuse light
    RGBColor specularIntensity; // intensity of the specular light

public:

    //-------------
    // constructors
    Light();

    Light(const RGBColor &diffuseIntensity, const RGBColor &specularIntensity);
    //-------------

    //--------------------
    // setters and getters
    const RGBColor &getDiffuseIntensity() const;

    void setDiffuseIntensity(const RGBColor &diffuseIntensity);

    const RGBColor &getSpecularIntensity() const;

    void setSpecularIntensity(const RGBColor &specularIntensity);
    //--------------------

    //----------------------
    // operators overloading
    friend std::ostream &operator<<(std::ostream &os, const Light &light);
    //----------------------


};


#endif //RAYTRACER_LIGHT_H
