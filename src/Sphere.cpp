//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "Sphere.h"

//-------------
// constructors
Sphere::Sphere(float ambientReflection,
               float diffuseReflection,
               float specularReflection,
               float phongCoefficient,
               const RGBColor &ambientColor,
               const RGBColor &diffuseColor,
               const RGBColor &specularColor,
               float radius,
               Vector3f centre)
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

//---------------------
// operator overloading
std::ostream &operator<<(std::ostream &os, const Sphere &sphere) {
    os << static_cast<const Geometry &>(sphere) << " radius: " << sphere.radius << " centre: " << endl << sphere.centre;
    return os;
}
//---------------------

Vector3f* Sphere::intersect(Ray *ray) {

    Vector3f sphereCentre = Vector3f(ray->origin - this->centre);

    // a -> v.v t^2
    float a = ray->beam.dot(ray->beam);

    // b -> p0 - c * t
    float b = 2.0f * sphereCentre.dot(ray->beam);

    // c -> p0-c.p0-c - r^2
    float c = sphereCentre.dot(sphereCentre) - this->radius * this->radius;

    // b^2 - 4ac
    float discriminant = (b * b) - (4 * a * c);

    // no solution
    if(discriminant <= 0){
        return nullptr;
    }

    // sqrt(b^2-4ac)
    discriminant = sqrt(discriminant);

    // -b + sqrt(b^2-4ac) / 2a
    float t1 = (-b + discriminant) / (2*a);

    // -b - sqrt(b^2-4ac) / 2a
    float t2 = (-b - discriminant) / (2*a);

    // point 1
    Vector3f* point1 = new Vector3f( ray->origin + (ray->beam * t1));

    // point 2
    Vector3f* point2 = new Vector3f( ray->origin + (ray->beam * t2));

    // distance from the points to the camera
    float p1Dist = vectorDistance(ray->origin, *point1);

    float p2Dist = vectorDistance(ray->origin, *point2);

    // we return the closest point
    if(p1Dist <= p2Dist) {
        return point1;
    }

    return point2;

}
