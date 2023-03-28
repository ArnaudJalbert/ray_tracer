//
// Created by Arnaud Jalbert on 2023-01-31.
//

#ifndef RAYTRACER_RGBCOLOR_H
#define RAYTRACER_RGBCOLOR_H


#include <ostream>
#include <string>

using std::string;

class RGBColor {
public:

    // 3 float values that represent a RBG color
    // all values are in range [0,1]
    float r; // red
    float g; // green
    float b; // blue

    //-------------
    // constructors
    RGBColor();

    RGBColor(float r, float g, float b);
    //-------------

    //----------
    // destructor
    /**
     * Noting to delete for now
     */
    virtual ~RGBColor() = default;
    //----------

    //-------
    // checks
    static bool rgbRange(float value);

    void invalidRGBRange();
    //-------

    //----------------------
    // operators overloading
    friend std::ostream &operator<<(std::ostream &os, const RGBColor &color);

    friend RGBColor operator+(const RGBColor &u, const RGBColor &v);

    friend RGBColor operator+(float t, const RGBColor &v);

    friend RGBColor operator+(const RGBColor &u, float t);

    friend RGBColor operator*(const RGBColor &u, const RGBColor &v);

    friend RGBColor operator*(float t, const RGBColor &v);

    friend RGBColor operator*(const RGBColor &v, float t);
    //----------------------

    //------------------
    // utility functions
    void writeColor(std::ostream &out);
    //------------------
};


#endif //RAYTRACER_RGBCOLOR_H
