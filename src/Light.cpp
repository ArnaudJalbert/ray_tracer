//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "Light.h"

//-------------
// constructors
Light::Light() {

    this->setDiffuseIntensity(DEFAULT_LIGHT_INTENSITY);
    this->setSpecularIntensity(DEFAULT_LIGHT_INTENSITY);

}

Light::Light(const RGBColor &diffuseIntensity, const RGBColor &specularIntensity){

    this->setDiffuseIntensity(diffuseIntensity);
    this->setSpecularIntensity(specularIntensity);

}
//-------------

//--------------------
// setters and getters
const RGBColor &Light::getDiffuseIntensity() const {
    return diffuseIntensity;
}

void Light::setDiffuseIntensity(const RGBColor &diffuseIntensity) {
    this->diffuseIntensity = diffuseIntensity;
}

const RGBColor &Light::getSpecularIntensity() const {
    return specularIntensity;
}

void Light::setSpecularIntensity(const RGBColor &specularIntensity) {
    this->specularIntensity = specularIntensity;
}
//--------------------

//----------------------
// operators overloading
std::ostream &operator<<(std::ostream &os, const Light &light) {
    os << "diffuseIntensity: " << light.diffuseIntensity << " specularIntensity: " << light.specularIntensity;
    return os;
}
//----------------------

