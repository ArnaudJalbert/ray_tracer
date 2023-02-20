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

Sphere::Sphere(float radius, Vector3f *centre){

    this->setRadius(radius);
    this->setCentre(centre);

}

Sphere::Sphere(float ambientReflection,
               float diffuseReflection,
               float specularReflection,
               float phongCoefficient,
               const RGBColor &ambientColor,
               const RGBColor &diffuseColor,
               const RGBColor &specularColor,
               float radius,
               Vector3f *centre)
               : Geometry(ambientReflection,
                          diffuseReflection,
                          specularReflection,
                          phongCoefficient,
                          ambientColor,
                          diffuseColor,
                          specularColor){

    this->setRadius(radius);
    this->setCentre(centre);

}
//-------------

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
    os << static_cast<const Geometry &>(sphere) << " radius: " << sphere.radius << " centre: " << endl << *sphere.centre;
    return os;
}
//---------------------



float Sphere::intersect(Ray *ray) {

    Vector3f *oc = new Vector3f(*ray->getOrigin() - *this->getCentre());

    float a = ray->getBeam()->dot(*ray->getBeam());

    float b = 2.0f * oc->dot(*ray->getBeam());

    float c = oc->dot(*oc) - this->getRadius()* this->getRadius();

    float discriminant = b*b - 4*a*c;

    if(discriminant > 0){
        return 1;
    }
    else{
        return 0;
    }

}
