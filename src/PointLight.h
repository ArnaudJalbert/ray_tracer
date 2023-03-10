//
// Created by Arnaud Jalbert on 2023-01-31.
//

#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H

#include "Light.h"

class PointLight: public Light {

private:
    Vector3f *centre;

public:

    PointLight(const RGBColor &diffuseIntensity, const RGBColor &specularIntensity, Vector3f *centre);

    Vector3f *getCentre() const{ return this->centre;}

    void setCentre(Vector3f *centre){ this->centre = centre;};

};


#endif //RAYTRACER_POINTLIGHT_H
