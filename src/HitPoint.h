//
// Created by Arnaud Jalbert on 2023-03-10.
//

#ifndef RAYTRACER_HITPOINT_H
#define RAYTRACER_HITPOINT_H

#include <Eigen/Dense>
#include "PointLight.h"

using Eigen::Vector3f;


class HitPoint {

public:

    Ray* ray;
    Vector3f* point;
    Vector3f* normal;
    Geometry* geo;
    PointLight* light;
    bool intersected;

    HitPoint(Ray* ray) : ray(ray) {
        point = nullptr;
        intersected = false;
    }

    void setPoint(Vector3f *point){ this->point = point;};

    void setNormal(Vector3f *normal){ this->normal = normal;};

    void setGeo(Geometry* geo) { this->geo = geo;};

    void setRay(Ray* ray) { this->ray = ray;};



};


#endif //RAYTRACER_HITPOINT_H
