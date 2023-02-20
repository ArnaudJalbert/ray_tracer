//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "Rectangle.h"

//-------------
// constructors

Rectangle::Rectangle() {
    this->setP1(DEFAULT_P1);
    this->setP2(DEFAULT_P2);
    this->setP3(DEFAULT_P3);
    this->setP4(DEFAULT_P4);
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

float Rectangle::intersect(Ray *ray) {

}
