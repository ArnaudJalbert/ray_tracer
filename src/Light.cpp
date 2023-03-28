//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "Light.h"

//-------------
// constructors

Light::Light(){}

//-------------


//----------------------
// operators overloading
std::ostream &operator<<(std::ostream &os, const Light &light) {
    os << "diffuseIntensity: " << light.diffuseIntensity << " specularIntensity: " << light.specularIntensity;
    return os;
}

//----------------------

