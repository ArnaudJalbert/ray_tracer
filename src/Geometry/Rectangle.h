//
// Created by Arnaud Jalbert on 2023-01-31.
//

#ifndef RAYTRACER_RECTANGLE_H
#define RAYTRACER_RECTANGLE_H

#include <Eigen/Dense>
#include <iostream>

#include "Geometry.h"

using std::cout;
using std::endl;
using Eigen::Vector3f;

#define DEFAULT_P1 (new Vector3f(-1.0f, 1.0f, 1.0f))
#define DEFAULT_P2 (new Vector3f(-1.0f, 2.0f, 1.0f))
#define DEFAULT_P3 (new Vector3f(1.0f, 2.0f, 1.0f))
#define DEFAULT_P4 (new Vector3f(1.0f, 1.0f, 1.0f))


// Rectangle is a type of geometry
class Rectangle: public Geometry{

private:

    Vector3f* p1; // coordinates of point #1
    Vector3f* p2; // coordinates of point #2
    Vector3f* p3; // coordinates of point #3
    Vector3f* p4; // coordinates of point #4

public:

    //-------------
    // constructors
    Rectangle();

    Rectangle(Vector3f *p1, Vector3f *p2, Vector3f *p3, Vector3f *p4);

    Rectangle(float ambientReflection, float diffuseReflection, float specularReflection, float phongCoefficient,
              const RGBColor &ambientColor, const RGBColor &diffuseColor, const RGBColor &specularColor,
              Vector3f *p1, Vector3f *p2, Vector3f *p3, Vector3f *p4);

    //-------------

    //--------------------
    // getters and setters

    void setP1(Vector3f *p1){ this->p1 = p1; };

    void setP2(Vector3f *p2){ this->p2 = p2; };

    void setP3(Vector3f *p3){ this->p3 = p3; };

    void setP4(Vector3f *p4){ this->p4 = p4; };

    Vector3f *getP1() const{ return p1; };

    Vector3f *getP2() const{ return p2; };

    Vector3f *getP3() const{ return p3; };

    Vector3f *getP4() const{ return p4; };

    //--------------------

    //---------------------
    // operator overloading

    friend std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle);

    //---------------------

    //------------------
    // utility functions
    float intersect(Ray* ray) override;
    //------------------

};


#endif //RAYTRACER_RECTANGLE_H
