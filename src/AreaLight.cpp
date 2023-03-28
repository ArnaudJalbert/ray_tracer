//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "AreaLight.h"

AreaLight::AreaLight(const RGBColor &diffuseIntensity, const RGBColor &specularIntensity, Vector3f p1, Vector3f p2,
                     Vector3f p3, Vector3f p4){

    this->diffuseIntensity = diffuseIntensity;
    this->diffuseIntensity = specularIntensity;

    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;

    Vector3f* areaCentre = new Vector3f(( p1 + p2 + p3 + p4)/4);

    this->centre = areaCentre;

}

