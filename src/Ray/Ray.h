//
// Created by Arnaud Jalbert on 2023-02-03.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <Eigen/Dense>
#include <ostream>

#include "RGBColor/RGBColor.h"

using Eigen::Vector3f;

#define DEFAULT_ORIGIN (Vector3f(0,0,0))
#define DEFAULT_DIRECTION (Vector3f(0,0,1))


class Ray {

private:

    Vector3f origin; // origin of the ray
    Vector3f direction; // direction of the ray

public:

    Ray();

    Ray(const Vector3f &origin, const Vector3f &direction);

    const Vector3f &getOrigin() const;

    void setOrigin(const Vector3f &origin);

    const Vector3f &getDirection() const;

    void setDirection(const Vector3f &direction);

    friend std::ostream &operator<<(std::ostream &os, const Ray &ray);

    // function  𝐏(𝑡)=𝐀+𝑡𝐛
    Vector3f at(double t);


};


#endif //RAYTRACER_RAY_H
