//
// Created by Arnaud Jalbert on 2023-02-03.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <Eigen/Dense>
#include <iostream>

#include "RGBColor.h"


using std::cout;
using std::endl;

using Eigen::Vector3f;


class Ray {

public:

    Vector3f origin; // origin of the ray
    Vector3f direction; // direction of the ray
    Vector3f beam; // unit vector of the beam of the ray

    Ray();

    Ray(Vector3f origin, Vector3f direction);

    Vector3f getOrigin() {return origin;};

    Vector3f getDirection() {return direction;};

    Vector3f getBeam() {return beam;};

    friend std::ostream &operator<<(std::ostream &os, const Ray &ray);


};


#endif //RAYTRACER_RAY_H
