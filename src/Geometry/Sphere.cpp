//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "Sphere.h"

//-------------
// constructors
Sphere::Sphere() {

    this->setRadius(DEFAULT_RADIUS);
    this->setCentre(DEFAULT_CENTRE);

}

Sphere::Sphere(float radius, const Vector3f &centre){

    this->setRadius(radius);
    this->setCentre(centre);

}

Sphere::Sphere(float ambientReflection, float diffuseReflection, float specularReflection, float phongCoefficient, const RGBColor &ambientColor, const RGBColor &diffuseColor, const RGBColor &specularColor, float radius, const Vector3f &centre) : Geometry(ambientReflection, diffuseReflection, specularReflection, phongCoefficient, ambientColor, diffuseColor, specularColor){

    this->setRadius(radius);
    this->setCentre(centre);

}
//-------------

//--------------------
// getters and setters
float Sphere::getRadius() const {

    return radius;
}

void Sphere::setRadius(float radius) {
    if(checkRadius(radius)) {
        this->radius = radius;
    }
    else{
        invalidRadiusSize();
    }
}

const Vector3f &Sphere::getCentre() const {
    return centre;
}

void Sphere::setCentre(const Vector3f &centre) {
    this->centre = centre;
}
//--------------------

//-------
// checks
bool Sphere::checkRadius(float radius){
    return radius > 0.0f;
}

void Sphere::invalidRadiusSize() {
    // TODO add exception or behavior to handle the wrong input for Radius
}
//-------

//---------------------
// operator overloading
std::ostream &operator<<(std::ostream &os, const Sphere &sphere) {
    os << static_cast<const Geometry &>(sphere) << " radius: " << sphere.radius << " centre: " << endl << sphere.centre;
    return os;
}
//---------------------
