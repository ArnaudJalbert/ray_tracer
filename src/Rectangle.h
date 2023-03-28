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

struct triangle{
    Vector3f a;
    Vector3f b;
    Vector3f c;
};



// Rectangle is a type of geometry
class Rectangle: public Geometry{

public:

    Vector3f p1; // coordinates of point #1
    Vector3f p2; // coordinates of point #2
    Vector3f p3; // coordinates of point #3
    Vector3f p4; // coordinates of point #4

    struct triangle triangle1;
    struct triangle triangle2;

public:

    //-------------
    // constructors
    Rectangle();

    Rectangle(Vector3f p1, Vector3f p2, Vector3f p3, Vector3f p4);

    Rectangle(float ambientReflection, float diffuseReflection, float specularReflection, float phongCoefficient,
              const RGBColor &ambientColor, const RGBColor &diffuseColor, const RGBColor &specularColor,
              Vector3f p1, Vector3f p2, Vector3f p3, Vector3f p4);

    //-------------

    //---------------------
    // operator overloading

    friend std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle);

    //---------------------

    //------------------
    // utility functions

    // returns the normal of point a
    static Vector3f getNormal(Vector3f *a, Vector3f *b, Vector3f *c){

        Vector3f A = Vector3f(*b - *a);
        Vector3f B = Vector3f(*c - *a);

        Vector3f normal = A.cross(B);
        normal.normalize();

        return normal;

    }

    // finds value t for which the ray intersects with point p in "p = t * rayDirection"
    static float getT(Vector3f *p0, Vector3f *a, Vector3f *rayBeam, Vector3f *normal){

        float t;

        Vector3f pointVector = Vector3f(*a - *p0);

        float pointDot = pointVector.dot(*normal);

        float rayDot = rayBeam->dot(*normal);

        // TODO find out how to handle that case, for now simply return nothing
        if (rayDot == 0){
            return -1;
        }

        t =  pointDot/rayDot;

        return t;

    }

    static Vector3f getP(float t, Vector3f *rayBeam, Vector3f *origin){

        Vector3f p = Vector3f(*origin + *rayBeam * t);

        return p;
    }

    static int sign(Vector3f *x, Vector3f *y, Vector3f *p, Vector3f *normal){

        Vector3f xy = *y - *x;

        Vector3f xp = *p - *x;

        Vector3f crossXyp = xy.cross(xp);

        float sign = crossXyp.dot(*normal);

        if(sign >= 0.0f) return 1;
        else return -1;
    }

    static bool insideTriangle(struct triangle triangle, Vector3f* p, Vector3f *normal){

        Vector3f sbcNormal = getNormal(&triangle.b, &triangle.a, &triangle.c);
        int sbc = sign(&triangle.b, &triangle.c, p, normal);

        Vector3f scaNormal = getNormal(&triangle.c, &triangle.a, &triangle.b);
        int sca = sign(&triangle.c, &triangle.a, p, normal);

        Vector3f sabNormal = getNormal(&triangle.a, &triangle.c, &triangle.b);
        int sab = sign(&triangle.a, &triangle.b, p, normal);

        return sbc == 1 && sca == 1 && sab == 1;
    }

    static Vector3f* findIntersection(struct triangle triangle, Ray *ray);

    Vector3f* intersect(Ray* ray) override;
    //------------------

};


#endif //RAYTRACER_RECTANGLE_H
