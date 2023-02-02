//
// Created by Arnaud Jalbert on 2023-01-31.
//

#ifndef RAYTRACER_RGBCOLOR_H
#define RAYTRACER_RGBCOLOR_H


#include <ostream>

class RGBColor {

private:
    // 3 float values that represent a RBG color
    // all values are in range [0,1]
    float r; // red
    float g; // green
    float b; // blue

public:

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

    //--------------------
    // setters and getters
    float getR() const;

    void setR(float r);

    float getG() const;

    void setG(float g);

    float getB() const;

    void setB(float b);


    /**
     * @return static float array in the format [R,G,B]
     */
    float * getRGBArray() const;
    //--------------------

    //-------
    // checks
    static bool rgbRange(float value);

    void invalidRGBRange();
    //-------

    //----------------------
    // operators overloading
    friend std::ostream &operator<<(std::ostream &os, const RGBColor &color);
    //----------------------



};


#endif //RAYTRACER_RGBCOLOR_H
