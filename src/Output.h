//
// Created by Arnaud Jalbert on 2023-01-31.
//

#ifndef RAYTRACER_OUTPU_H
#define RAYTRACER_OUTPU_H

#include "Camera.h"


class Output {

public:
    // camera of the scene
    Camera* camera;

    // resolution of the image
    struct resolution{
        int width;
        int height;
    } resolution;

    // filename in which to output the results
    string filename;

    bool globalIllum = false;

    bool anitAliasing = false;

    int maxBounces;

    float probTerminate;

    float raysPerPixel[3];

    float n;

    RGBColor ai;

    RGBColor bgColor;

};


#endif //RAYTRACER_OUTPU_H
