//
// Created by Arnaud Jalbert on 2023-02-03.
//

#include "Ray.h"

Ray::Ray(Vector3f *origin, Vector3f *direction){

    // setting the origin and
    this->origin = origin;
    this->direction = direction;

    this->beam = new Vector3f(*this->direction - *this->origin);

}


std::ostream &operator<<(std::ostream &os, const Ray &ray) {
    os << "origin: " << *ray.origin << " direction: " << *ray.direction;
    return os;
}

