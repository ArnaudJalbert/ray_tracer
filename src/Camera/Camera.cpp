//
// Created by Arnaud Jalbert on 2023-02-02.
//

#include "Camera.h"

Camera::Camera() {
    this->setLookat(DEFAULT_LOOKAT);
    this->setUp(DEFAULT_UP);
    this->setPosition(DEFAULT_POSITION);
    this->setFov(DEFAULT_FOV);
}

Camera::Camera(Vector3f *lookat, Vector3f *up, Vector3f *position, float fov){
    this->setLookat(lookat);
    this->setUp(up);
    this->setPosition(position);
    this->setFov(fov);
}

Vector3f *Camera::getLookat() const {
    return lookat;
}

void Camera::setLookat(Vector3f *lookat) {
    Camera::lookat = lookat;
}

Vector3f *Camera::getUp() const {
    return up;
}

void Camera::setUp(Vector3f *up) {
    Camera::up = up;
}

Vector3f *Camera::getPosition() const {
    return position;
}

void Camera::setPosition(Vector3f *position) {
    Camera::position = position;
}

float Camera::getFov() const {
        return fov;
}

void Camera::setFov(float fov) {
    if(checkFOVRange(fov)) {
        Camera::fov = fov;
    }
    else{
        invalidFOVRange();
    }

}

bool Camera:: checkFOVRange(float value){
    return 0.0f <= value <= 360.0f;
}

void Camera::invalidFOVRange() {
    //TODO handle the exception
}

std::ostream &operator<<(std::ostream &os, const Camera &camera) {
    os << endl <<
    "lookat: " << endl << *camera.lookat << endl <<
    " up: " << endl << *camera.up << endl <<
    " position: " << endl << *camera.position <<  endl <<
    " fov: " << endl << camera.fov << endl;
    return os;
}
