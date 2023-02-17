//
// Created by Arnaud Jalbert on 2023-02-02.
//

#include "Camera.h"

//-----------------------------
// constructors and destructors
Camera::Camera() {
    this->setLookat(DEFAULT_LOOKAT);
    this->setUp(DEFAULT_UP);
    this->setPosition(DEFAULT_POSITION);
    this->setFov(DEFAULT_FOV);
}

Camera::Camera(Vector3f *lookat, Vector3f *up, Vector3f *position,
               float fov, int width, int height) {

    this->setLookat(lookat);
    this->setUp(up);
    this->setPosition(position);
    this->setFov(fov);
    this->setAspect(aspect);
    this->resolution.width = width;
    this->resolution.height = height;

}
//-----------------------------

//-------------------
// getters and setters
Vector3f *Camera::getLookat() const {
    return this->lookat;
}

void Camera::setLookat(Vector3f *lookat) {
    this->lookat = lookat;
}

Vector3f *Camera::getUp() const {
    return this->up;
}

void Camera::setUp(Vector3f *up) {
    this->up = up;
}

Vector3f *Camera::getPosition() const {
    return this->position;
}

void Camera::setPosition(Vector3f *position) {
    this->position = position;
}

float Camera::getFov() const {
        return this->fov;
}

void Camera::setFov(float fov) {
    if(checkFOVRange(fov)) {
        this->fov = fov;
    }
    else{
        invalidFOVRange();
    }

}

float Camera::getAspect() const {
    return this->aspect;
}

void Camera::setAspect(float aspect) {
    this->aspect = aspect;
}

Vector3f *Camera::getAlignment() {
    return this->alignment;
}

Vector3f *Camera::getUt() {
    return this->u;
}

Vector3f *Camera::getV() {
    return this->v;
}
//-------------------

//-------
// checks
bool Camera:: checkFOVRange(float value){
    return 0.0f <= value <= 360.0f;
}

void Camera::invalidFOVRange() {
    //TODO handle the exception
}



//-------

//----------------------
// operators overloading
std::ostream &operator<<(std::ostream &os, const Camera &camera) {
    os << endl <<
    "lookat: " << endl << *camera.lookat << endl <<
    " up: " << endl << *camera.up << endl <<
    " position: " << endl << *camera.position <<  endl <<
    " fov: " << endl << camera.fov << endl;
    return os;
}
//----------------------

//------------------
// utility functions
void Camera::updateCameraGeometry() {

    Vector3f test = *this->lookat - *this->position;
    // compute the alignment vector -> From position to lookat
    this->alignment = new Vector3f(*this->lookat - *this->position);
    // the vector needs to be normalized
    this->alignment->normalize();

    // compute u vector and normalize it
    this->u = new Vector3f(this->alignment->cross(*this->up));
    this->u->normalize();

    // compute v vector and normalize it
    this->v = new Vector3f(this->u->cross(*this->alignment));
    this->v->normalize();

    //aspect ratio
    this->aspect = float(this->resolution.width) / float(this->resolution.height);

    // compute the x and y offset
    this->xOffset = (2 * tan( this->fov * 0.5f)) / float(this->resolution.height);
    this->yOffset = (2 * tan( this->fov * 0.5f)) / float(this->resolution.width) * this->aspect;

    cout << "OFFSET x: " << this->xOffset << endl;
    cout << "OFFSET y: " << this->yOffset << endl;

}

Ray* Camera::generateRay(float positionX, float positionY) {

    float xPixelPos = this->position->x() + this->lookat->x() + (this->xOffset * this->u->x());
    float yPixelPos = this->position->y() + this->lookat->y() + (this->yOffset * this->u->y());
    float zPixelPos = this->position->z() -1;

    Vector3f *rayDirection = new Vector3f(xPixelPos,
                                          yPixelPos,
                                          zPixelPos);

    Vector3f *rayOrigin = new Vector3f(this->position->x(),
                                       this->position->y(),
                                       this->position->z());

    // creating a new ray with the right direction
    return new Ray(rayOrigin, rayDirection);
}
//------------------