//
// Created by Arnaud Jalbert on 2023-02-03.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <Eigen/Dense>
#include <iostream>

#include "RGBColor/RGBColor.h"


using std::cout;
using std::endl;

using Eigen::Vector3f;


class Ray {

private:

    Vector3f *origin; // origin of the ray
    Vector3f *direction; // direction of the ray
    Vector3f *beam; // unit vector of the beam of the ray

public:

    Ray();

    Ray(Vector3f *origin, Vector3f *direction);

    const Vector3f *getOrigin() const{return origin;};

    const Vector3f *getDirection() const{return direction;};

    const Vector3f *getBeam() const{return beam;};

    friend std::ostream &operator<<(std::ostream &os, const Ray &ray);


};


#endif //RAYTRACER_RAY_H
