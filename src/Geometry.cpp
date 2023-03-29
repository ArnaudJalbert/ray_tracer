//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "Geometry.h"



//-------------
// constructors
Geometry::Geometry() {

    this->setAmbientReflection(DEFAULT_REFLECTION);
    this->setDiffuseReflection(DEFAULT_REFLECTION);
    this->setSpecularReflection(DEFAULT_REFLECTION);
    this->setPhongCoefficient(DEFAULT_PHONG);
    this->setAmbientColor(DEFAULT_COLOR);
    this->setDiffuseColor(DEFAULT_COLOR);
    this->setSpecularColor(DEFAULT_COLOR);

}

Geometry::Geometry(float ambientReflection, float diffuseReflection, float specularReflection, float phongCoefficient,const RGBColor &ambientColor, const RGBColor &diffuseColor, const RGBColor &specularColor) {

    this->setAmbientReflection(ambientReflection);
    this->setDiffuseReflection(diffuseReflection);
    this->setSpecularReflection(specularReflection);
    this->setPhongCoefficient(phongCoefficient);
    this->setAmbientColor(ambientColor);
    this->setDiffuseColor(diffuseColor);
    this->setSpecularColor(specularColor);
}
//-------------

//--------------------
// setters and getters

float Geometry::getAmbientReflection() const {
    return ambientReflection;
}

void Geometry::setAmbientReflection(float ambientReflection) {
    if(reflectionCheck(ambientReflection)){
        this->ambientReflection = ambientReflection;
    }
    else{invalidReflectionRange();}
}

float Geometry::getDiffuseReflection() const {
    return this->diffuseReflection;
}

void Geometry::setDiffuseReflection(float diffuseReflection) {
    if(reflectionCheck(diffuseReflection)) {
        this->diffuseReflection = diffuseReflection;
    }
    else{invalidReflectionRange();}
}

float Geometry::getSpecularReflection() const {
    return this->specularReflection;
}

void Geometry::setSpecularReflection(float specularReflection) {
    if(reflectionCheck(specularReflection)) {
        this->specularReflection = specularReflection;
    }
    else{invalidReflectionRange();}
}

float Geometry::getPhongCoefficient() const {
    return this->phongCoefficient;
}

void Geometry::setPhongCoefficient(float phongCoefficient) {
    if(phongCheck(phongCoefficient)) {
        this->phongCoefficient = phongCoefficient;
    }
    else{invalidPhongRange();}
}

const RGBColor &Geometry::getAmbientColor() const {
    return this->ambientColor;
}

void Geometry::setAmbientColor(const RGBColor &ambientColor) {
    this->ambientColor = ambientColor;
}

const RGBColor &Geometry::getDiffuseColor() const {
    return this->diffuseColor;
}

void Geometry::setDiffuseColor(const RGBColor &diffuseColor) {
    this->diffuseColor = diffuseColor;
}

const RGBColor &Geometry::getSpecularColor() const {
    return this->specularColor;
}

void Geometry::setSpecularColor(const RGBColor &specularColor) {
    this->specularColor = specularColor;
}

//--------------------

//-------
// checks

bool Geometry::reflectionCheck(float value) {
    return 0.0f <= value <= 1.0f;
}

void Geometry::invalidReflectionRange(){
    // TODO add exception or behavior to handle the wrong input, do it for all setter and getters
}

bool Geometry::phongCheck(float value){
    return value > 1;
}

void Geometry::invalidPhongRange() {
    // TODO add exception or behavior to handle the wrong input, do it for all setter and getters
}

//-------

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

float Geometry::vectorDistance( Vector3f origin, Vector3f destination){

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
