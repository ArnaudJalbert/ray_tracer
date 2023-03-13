//
// Created by Arnaud Jalbert on 2023-03-10.
//

#ifndef RAYTRACER_HITPOINT_H
#define RAYTRACER_HITPOINT_H

#include <Eigen/Dense>
#include "PointLight.h"

using Eigen::Vector3f;


class HitPoint {

private:
    Vector3f* point = nullptr;
    Vector3f* normal;
    Geometry* geo;
    PointLight* light;
    Ray* ray;

public:

    HitPoint(Vector3f *point, Vector3f *normal, PointLight *light, Ray* ray) : point(point), normal(normal), light(light), ray(ray) {}

    Vector3f *getPoint() const{return point;};

    void setPoint(Vector3f *point){ this->point = point;};

    Vector3f *getNormal() const{return normal;};

    void setNormal(Vector3f *normal){ this->normal = normal;};

    PointLight *getLight() const{return light;};

    void setLight(PointLight *light){this->light = light;};

    Geometry* getGeo() const {return geo;};

    void setGeo(Geometry* geo) { this->geo = geo;};

    Ray* getRay() const {return ray;};

    void setRay(Ray* ray) { this->ray = ray;};



};


#endif //RAYTRACER_HITPOINT_H
