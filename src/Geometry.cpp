//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "Geometry.h"



//-------------
// constructors

Geometry::Geometry(float ambientReflection, float diffuseReflection, float specularReflection, float phongCoefficient,const RGBColor &ambientColor, const RGBColor &diffuseColor, const RGBColor &specularColor) {

    this->ambientReflection = ambientReflection;
    this->diffuseReflection = diffuseReflection;
    this->specularReflection = specularReflection;
    this->phongCoefficient = phongCoefficient;
    this->ambientColor = ambientColor;
    this->diffuseColor = diffuseColor;
    this->specularColor = specularColor;
}
//-------------

//----------------------
// operators overloading

std::ostream &operator<<(std::ostream &os, const Geometry &geometry) {
    os << "ambientReflection: " << geometry.ambientReflection << " diffuseReflection: " << geometry.diffuseReflection
       << " specularReflection: " << geometry.specularReflection << " phongCoefficient: " << geometry.phongCoefficient
       << " ambientColor: " << geometry.ambientColor << " diffuseColor: " << geometry.diffuseColor << " specularColor: "
       << geometry.specularColor;
    return os;
}

//----------------------

//------------------
// utility functions

float Geometry::vectorDistance(Vector3f origin, Vector3f destination){

    float x = destination.x() - origin.x();
    x = x * x;

    float y = destination.y() - origin.y();
    y = y * y;

    float z = destination.z() - origin.z();
    z = z * z;

    float xyz = x + y + z;

    float d = sqrt(xyz );

    return d;

}

//------------------
