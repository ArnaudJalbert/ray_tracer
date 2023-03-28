//
// Created by Arnaud Jalbert on 2023-02-03.
//

#include "Ray.h"



Ray::Ray(Vector3f *origin, Vector3f *direction){

    // setting the origin and direction
    this->origin = origin;
    this->direction = direction;

    // calculating the beam of the ray
    this->beam = new Vector3f(*this->direction - *this->origin);
    this->beam->normalize();

}


std::ostream &operator<<(std::ostream &os, const Ray &ray) {
    os << "origin: " << ray.origin << endl <<
    " direction: " << ray.direction << endl <<
    "beam: " << ray.beam << endl;
    return os;
}

Ray::Ray() {}

