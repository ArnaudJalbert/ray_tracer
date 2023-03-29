//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "Rectangle.h"

//-------------
// constructors

Rectangle::Rectangle() {

}

Rectangle::Rectangle(Vector3f *p1, Vector3f *p2, Vector3f *p3, Vector3f *p4) {
    this->setP1(p1);
    this->setP2(p2);
    this->setP3(p3);
    this->setP4(p4);
}

Rectangle::Rectangle(float ambientReflection,
                     float diffuseReflection,
                     float specularReflection,
                     float phongCoefficient,
                     const RGBColor &ambientColor,
                     const RGBColor &diffuseColor,
                     const RGBColor &specularColor,
                     Vector3f *p1,
                     Vector3f *p2,
                     Vector3f *p3,
                     Vector3f *p4)
                     : Geometry(ambientReflection,
                               diffuseReflection,
                               specularReflection,
                               phongCoefficient,
                               ambientColor,
                               diffuseColor,
                               specularColor) {

                    this->setP1(p1);
                    this->setP2(p2);
                    this->setP3(p3);
                    this->setP4(p4);

                    triangle1.a = p1;
                    triangle1.b = p2;
                    triangle1.c = p3;

                    triangle2.a = p3;
                    triangle2.b = p4;
                    triangle2.c = p1;
}
//-------------

std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle) {
    os << static_cast<const Geometry &>(rectangle) << endl <<
    " p1: " << endl << *rectangle.p1 << endl <<
    " p2: " << endl << *rectangle.p2 << endl <<
    " p3: " << endl << *rectangle.p3 << endl <<
    " p4: " << endl << *rectangle.p4;
    return os;
}

// returns the point of intersection
Vector3f Rectangle:: findIntersection(struct triangle triangle, Ray *ray){

    Vector3f normal = getNormal(triangle.a, triangle.b, triangle.c);


    float t = getT(&ray->origin, triangle.a, &ray->beam, &normal);


    if ( t >= 0){

        Vector3f p = Vector3f(getP(t, &ray->beam, &ray->origin));

        if(insideTriangle(triangle, &p, &normal))
            return p;

        return Vector3f(INFINITY,INFINITY, INFINITY);
    }

    return Vector3f(INFINITY,INFINITY,INFINITY);
}

Vector3f Rectangle::intersect(Ray *ray) {

    // check first triangle
    Vector3f intersectionPoint = findIntersection(triangle1, ray);

    // check second triangle
    if (intersectionPoint.x() < INFINITY) return intersectionPoint;

    intersectionPoint = findIntersection(triangle2, ray);

    // check second triangle
    if (intersectionPoint.x() < INFINITY) return intersectionPoint;

    return Vector3f(INFINITY,INFINITY,INFINITY);
}
