//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "RGBColor.h"

//-------------
// constructors
RGBColor::RGBColor() {
    // black as default
    this->setR(0.0);
    this->setG(0.0);
    this->setB(0.0);
}

RGBColor::RGBColor(float r, float g, float b){

    this->setR(r);
    this->setG(g);
    this->setB(b);
}
//-------------

//--------------------
// setters and getters
float RGBColor::getR() const {
    return r;
}

void RGBColor::setR(float r) {
    if (rgbRange(r)) {
        RGBColor::r = r;
    }
    else{invalidRGBRange();}
}

float RGBColor::getG() const {
    return g;
}

void RGBColor::setG(float g) {
    if (rgbRange(g)) {
        RGBColor::g = g;
    }
    else{invalidRGBRange();}
}

float RGBColor::getB() const {
    return this->b;
}

void RGBColor::setB(float b) {
    if (rgbRange(b)) {
        RGBColor::b = b;
    }
    else{invalidRGBRange();}
}

float * RGBColor::getRGBArray() const {
    static float rgbArray[3];
    rgbArray[0] = getR();
    rgbArray[1] = getG();
    rgbArray[2] = getB();
    return rgbArray;
}
//--------------------

//-------
// checks
bool RGBColor::rgbRange(float value) {
    return 0.0 <= value <= 1.0;
}

void RGBColor::invalidRGBRange() {
    // TODO add exception or behavior to handle the wrong input, do it for all setter and getters
}
//-------

//----------------------
// operators overloading
std::ostream &operator<<(std::ostream &os, const RGBColor &color) {
    os << "r: " << color.r << " g: " << color.g << " b: " << color.b;
    return os;
}

RGBColor operator+(const RGBColor &u, const RGBColor &v){
    return {u.r + v.r, u.g + v.g, u.b + v.b};
};

RGBColor operator+(float t, const RGBColor &v){
    return {t + v.r, t + v.g, t + v.b};
};

RGBColor operator+(const RGBColor &u, float t){
    return t + u;
};

// simple color multiplication
RGBColor operator*(const RGBColor &u, const RGBColor &v) {
    return {u.r * v.r, u.g * v.g, u.b * v.b};
}

// scalar multiplication (float*RGBColor)
RGBColor operator*(float t, const RGBColor &v) {
    return {t*v.r, t*v.g, t*v.b};
}

// inverse (RGBColor * float)
RGBColor operator*(const RGBColor &v, float t) {
    return t*v;
}

//----------------------


void RGBColor::writeColor(std::ostream &out) const{
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * this->r) << ' '
        << static_cast<int>(255.999 * this->g) << ' '
        << static_cast<int>(255.999 * this->b) << '\n';
}