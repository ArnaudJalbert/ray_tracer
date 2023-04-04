//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "PointLight.h"

PointLight::PointLight(const RGBColor &diffuseIntensity, const RGBColor &specularIntensity, Vector3f centre) : Light(
        diffuseIntensity, specularIntensity, centre) {
    this->centre = centre;
}

std::ostream &operator<<(std::ostream &os, const PointLight &light) {
    os << static_cast<const Light &>(light) << " centre: " << light.centre;
    return os;
}
