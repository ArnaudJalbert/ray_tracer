//
// Created by Arnaud Jalbert on 2023-02-02.
//

#include "Camera.h"

Camera::Camera() {
    this->setLookat(DEFAULT_LOOKAT);
    this->setUp(DEFAULT_UP);
    this->setPosition(DEFAULT_POSITION);
    this->setFov(60.0);
}

Camera::Camera(const Vector3f &lookat, const Vector3f &up, const Vector3f &position, float fov){
    this->setLookat(lookat);
    this->setUp(up);
    this->setPosition(position);
    this->setFov(fov);
}

const Vector3f &Camera::getLookat() const {
    return lookat;
}

void Camera::setLookat(const Vector3f &lookat) {
    Camera::lookat = lookat;
}

const Vector3f &Camera::getUp() const {
    return up;
}

void Camera::setUp(const Vector3f &up) {
    Camera::up = up;
}

const Vector3f &Camera::getPosition() const {
    return position;
}

void Camera::setPosition(const Vector3f &position) {
    Camera::position = position;
}

float Camera::getFov() const {
    if(checkFOVRange()) {
        return fov;
    }
    else{}
}

void Camera::setFov(float fov) {
    Camera::fov = fov;
}

bool Camera:: checkFOVRange(float value){
    return 0.0f <= value <= 360.0f;
}

void Camera::invalidFOVRange() {
    //TODO handle the exception
}

std::ostream &operator<<(std::ostream &os, const Camera &camera) {
    os << "lookat: " << camera.lookat << " up: " << camera.up << " position: " << camera.position << " fov: "
       << camera.fov;
    return os;
}
