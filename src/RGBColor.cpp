//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "RGBColor.h"

//-------------
// constructors
RGBColor::RGBColor() {
    // black as default
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

RGBColor::RGBColor(float r, float g, float b){

    this->r = r;
    this->g = g;
    this->b = b;
}
//-------------

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


void RGBColor::writeColor(std::ostream &out){
    // Write the translated [0,255] value of each color component.

    if (this->r > 1.0f) this->r = 1.0f;
    if (this->g > 1.0f) this->g = 1.0f;
    if (this->b > 1.0f) this->b = 1.0f;

    out << static_cast<int>(255.999 * this->r) << ' '
        << static_cast<int>(255.999 * this->g) << ' '
        << static_cast<int>(255.999 * this->b) << '\n';
}

