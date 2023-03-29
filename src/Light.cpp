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


//----------------------
// operators overloading
std::ostream &operator<<(std::ostream &os, const Light &light) {
    os << "diffuseIntensity: " << light.diffuseIntensity << " specularIntensity: " << light.specularIntensity;
    return os;
}

Light::Light(const RGBColor &diffuseIntensity, const RGBColor &specularIntensity, Vector3f centre) : diffuseIntensity(
        diffuseIntensity), specularIntensity(specularIntensity), centre(centre) {}
//----------------------

