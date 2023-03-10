//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "AreaLight.h"

AreaLight::AreaLight(const RGBColor &diffuseIntensity, const RGBColor &specularIntensity, Vector3f *p1, Vector3f *p2,
                     Vector3f *p3, Vector3f *p4) : Light(diffuseIntensity, specularIntensity), p1(p1), p2(p2), p3(p3),
                                                   p4(p4) {}

