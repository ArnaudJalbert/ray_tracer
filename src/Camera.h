//
// Created by Arnaud Jalbert on 2023-02-02.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <Eigen/Dense>
#include <iostream>
#include <math.h>
#include <random>

#include "Ray.h"

using Eigen::Vector3f;

using std::cout;
using std::endl;

#define PLANE_DISTANCE (1.0f)

class Camera {

public:

    Vector3f *lookat; // lookat vector of the camera
    Vector3f *up; // up vector of the camera
    Vector3f *position; // position of the camera

    struct resolution{
        int width;
        int height;
    } resolution; // resolution of the image

    float fov; // field of view in degrees -> 0 to 360 degrees

    float aspectRatio; // aspectRatio ratio of the screen

    Vector3f *a; // centre of the projection plane
    Vector3f *b; // top centre of projection plane
    Vector3f *c; // top left of the projection plane
    Vector3f *u; // unit vector that gives the direction of the width
    Vector3f *v; // unit vector that gives the direction of the wheight

    float alpha; // height of half the projection plane
    float s; // size of a pixel

    Camera();

    Camera(Vector3f *lookat, Vector3f *up, Vector3f *position,
           float fov, int width, int height);

    virtual ~Camera();

    //-------------------
    // getters and setters
    Vector3f *getLookat() const;

    void setLookat(Vector3f *lookat);

    Vector3f *getUp() const;

    void setUp(Vector3f *up);

    Vector3f *getPosition() const;

    void setPosition(Vector3f *position);

    float getFov() const;

    void setFov(float fov);

    //-------------------

    //-------
    // checks

    static bool checkFOVRange(float value);

    void invalidFOVRange();

    //-------

    //----------------------
    // operators overloading

    friend std::ostream &operator<<(std::ostream &os, const Camera &camera);

    //----------------------

    //------------------
    // utility functions

    // update the camera geometry
    void initCameraGeometry();

    // prints all camera geometry info
    void cameraGeometryInfo();

    // generates a ray from the camera given an (x,y) pixel position
    Ray generateRay(int positionX, int positionY);

    // generates a ray from the camera given an (x,y) pixel position with sampling value
    Ray generateRay(int positionX, int positionY, float grids, int xPlacement, int yPlacemen);

    // generates a ray from the camera given an (x,y) pixel position with sampling value
    Ray generateRay(int positionX, int positionY, float grids, int xPlacement, int yPlacement, float randomNumX, float randomNumY);

    //------------------


};


#endif //RAYTRACER_CAMERA_H
