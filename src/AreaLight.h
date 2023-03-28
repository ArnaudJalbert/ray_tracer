//
// Created by Arnaud Jalbert on 2023-01-31.
//

#ifndef RAYTRACER_AREALIGHT_H
#define RAYTRACER_AREALIGHT_H

#include "Light.h"

class AreaLight: public Light{

public:
    Vector3f p1;
    Vector3f p2;
    Vector3f p3;
    Vector3f p4;
    // temp
    Vector3f* centre;

    AreaLight(const RGBColor &diffuseIntensity, const RGBColor &specularIntensity,
              Vector3f p1, Vector3f p2, Vector3f p3, Vector3f p4);


};


#endif //RAYTRACER_AREALIGHT_H
