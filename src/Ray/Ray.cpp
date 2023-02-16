//
// Created by Arnaud Jalbert on 2023-02-03.
//

#include "Ray.h"

Ray::Ray() {

    this->setDirection(DEFAULT_DIRECTION);
    this->setOrigin(DEFAULT_ORIGIN);

}

Ray::Ray(const Vector3f &origin, const Vector3f &direction){

    this->setOrigin(origin);
    this->setDirection(direction);

}

const Vector3f &Ray::getOrigin() const {
    return origin;
}

void Ray::setOrigin(const Vector3f &origin) {
    this->origin = origin;
}

const Vector3f &Ray::getDirection() const {
    return direction;
}

void Ray::setDirection(const Vector3f &direction) {
    this->direction = direction;
}

std::ostream &operator<<(std::ostream &os, const Ray &ray) {
    os << "origin: " << ray.origin << " direction: " << ray.direction;
    return os;
}

Vector3f Ray::at(double  t){
    return this->origin + this->direction * t;
}

