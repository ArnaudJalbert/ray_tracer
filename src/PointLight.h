//
// Created by Arnaud Jalbert on 2023-01-31.
//

#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H

#include <ostream>
#include "Light.h"

class PointLight: public Light {

public:
    Vector3f centre;

    PointLight(const RGBColor &diffuseIntensity, const RGBColor &specularIntensity, Vector3f centre);


    friend std::ostream &operator<<(std::ostream &os, const PointLight &light);
};


#endif //RAYTRACER_POINTLIGHT_H
