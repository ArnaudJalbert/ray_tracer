//
// Created by Arnaud Jalbert on 2023-02-02.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <Eigen/Dense>
#include <iostream>


using Eigen::Vector3f;

using std::cout;
using std::endl;

#define DEFAULT_LOOKAT (new Vector3f(0.0f,0.0f,1.0f))
#define DEFAULT_UP (new Vector3f(0.0f,1.0f,0.0f))
#define DEFAULT_POSITION (new Vector3f(0.0f, 0.0f, 0.0f))
#define DEFAULT_FOV (60.0f)

class Camera {

private:

    Vector3f *lookat; // lookat vector of the camera
    Vector3f *up; // up vector of the camera
    Vector3f *position; // position of the camera
    float fov; // field of view in degrees -> 0 to 360 degrees


public:

    Camera();

    Camera(Vector3f *lookat, Vector3f *up, Vector3f *position, float fov);

    Vector3f *getLookat() const;

    void setLookat(Vector3f *lookat);

    Vector3f *getUp() const;

    void setUp(Vector3f *up);

    Vector3f *getPosition() const;

    void setPosition(Vector3f *position);

    float getFov() const;

    void setFov(float fov);

    static bool checkFOVRange(float value);

    void invalidFOVRange();

    friend std::ostream &operator<<(std::ostream &os, const Camera &camera);


};


#endif //RAYTRACER_CAMERA_H
