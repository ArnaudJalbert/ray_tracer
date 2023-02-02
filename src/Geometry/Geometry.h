//
// Created by Arnaud Jalbert on 2023-01-31.
//

#ifndef RAYTRACER_GEOMETRY_H
#define RAYTRACER_GEOMETRY_H

#include <string>
#include <ostream>

using std::string;

#include "../RGBColor/RGBColor.h"

#define DEFAULT_REFLECTION (0.05f)
#define DEFAULT_PHONG (1.5f)
#define DEFAULT_COLOR RGBColor(0.5f, 0.5f, 0.5f)

class Geometry {


private:

    // reflection coefficients
    float ambientReflection; // float in range[0,1] → ambient reflection coefficient
    float diffuseReflection; // float in range[0,1] → diffuse reflection coefficient
    float specularReflection; // float in range[0,1] → specular reflection coefficient

    float phongCoefficient; // float in range]1,infinity[ → Phong coefficient

    // color properties
    RGBColor ambientColor; // [3 float] that represents a rgb color → ambient color
    RGBColor diffuseColor; // [3 float] that represents a rgb color → diffuse color
    RGBColor specularColor; // [3 float] that represents a rgb color → specular color

public:

    //-------------
    // constructors
    Geometry();

    Geometry(float ambientReflection, float diffuseReflection, float specularReflection, float phongCoefficient, const RGBColor &ambientColor, const RGBColor &diffuseColor, const RGBColor &specularColor);
    //-------------

    //--------------------
    // setters and getters
    float getAmbientReflection() const;

    void setAmbientReflection(float ambientReflection);

    float getDiffuseReflection() const;

    void setDiffuseReflection(float diffuseReflection);

    float getSpecularReflection() const;

    void setSpecularReflection(float specularReflection);

    float getPhongCoefficient() const;

    void setPhongCoefficient(float phongCoefficient);

    const RGBColor &getAmbientColor() const;

    void setAmbientColor(const RGBColor &ambientColor);

    const RGBColor &getDiffuseColor() const;

    void setDiffuseColor(const RGBColor &diffuseColor);

    const RGBColor &getSpecularColor() const;

    void setSpecularColor(const RGBColor &specularColor);
    //--------------------

    //-------
    // checks
    static bool reflectionCheck(float value);

    void invalidReflectionRange();

    static bool phongCheck(float value);

    void invalidPhongRange();
    //-------

    //----------------------
    // operators overloading
    friend std::ostream &operator<<(std::ostream &os, const Geometry &geometry);
    //----------------------


};


#endif //RAYTRACER_GEOMETRY_H
