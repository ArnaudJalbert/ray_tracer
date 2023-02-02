//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "Rectangle.h"

Rectangle::Rectangle() {
    this->setP1(DEFAULT_P1);
    this->setP2(DEFAULT_P2);
    this->setP3(DEFAULT_P3);
    this->setP4(DEFAULT_P4);
}

Rectangle::Rectangle(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3, const Vector3f &p4) {
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
                     const Vector3f &p1,
                     const Vector3f &p2,
                     const Vector3f &p3,
                     const Vector3f &p4)
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

const Vector3f &Rectangle::getP1() const {
    return p1;
}

void Rectangle::setP1(const Vector3f &p1) {
    Rectangle::p1 = p1;
}

const Vector3f &Rectangle::getP2() const {
    return p2;
}

void Rectangle::setP2(const Vector3f &p2) {
    Rectangle::p2 = p2;
}

const Vector3f &Rectangle::getP3() const {
    return p3;
}

void Rectangle::setP3(const Vector3f &p3) {
    Rectangle::p3 = p3;
}

const Vector3f &Rectangle::getP4() const {
    return p4;
}

void Rectangle::setP4(const Vector3f &p4) {
    Rectangle::p4 = p4;
}

std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle) {
    os << static_cast<const Geometry &>(rectangle) << endl <<
    " p1: " << endl << rectangle.p1 << endl <<
    " p2: " << endl << rectangle.p2 << endl <<
    " p3: " << endl << rectangle.p3 << endl <<
    " p4: " << endl << rectangle.p4;
    return os;
}
