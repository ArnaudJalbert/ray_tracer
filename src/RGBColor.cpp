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

float RGBColor::getFinalR(){

    float finalR;

    if (this->r > 1.0f) finalR = 1.0f;
    else if (this->r < 0.0f) finalR = 0.0f;
    else finalR = r;

    return finalR;
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

float RGBColor::getFinalG(){

    float finalG;

    if (this->g > 1.0f) finalG = 1.0f;
    else if (this->g < 0.0f) finalG = 0.0f;
    else finalG = g;

    return finalG;
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

float RGBColor::getFinalB(){

    float finalB;

    if (this->b > 1.0f) finalB = 1.0f;
    else if (this->b < 0.0f) finalB = 0.0f;
    else finalB = b;

    return finalB;
}

void RGBColor::setB(float b) {
    if (rgbRange(b)) {
        RGBColor::b = b;
    }
    else{invalidRGBRange();}
}

void RGBColor::setRGB(float r, float g, float b) { this->r = r; this->g = g; this->b = b;}

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


void RGBColor::writeColor(std::ostream &out){
    // Write the translated [0,255] value of each color component.

    if (this->r > 1.0f) this->r = 1.0f;
    if (this->g > 1.0f) this->g = 1.0f;
    if (this->b > 1.0f) this->b = 1.0f;

    out << static_cast<int>(255.999 * this->r) << ' '
        << static_cast<int>(255.999 * this->g) << ' '
        << static_cast<int>(255.999 * this->b) << '\n';
}

