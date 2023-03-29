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
void Camera::initCameraGeometry() {

    // normalize lookat and up vector
    this->lookat->normalize();
    this->up->normalize();

    // aspect ratio
    this->aspectRatio = float(this->resolution.width) / float(this->resolution.height);

    // centre of the projection plane
    this->a = new Vector3f(*this->position + (*this->lookat * PLANE_DISTANCE));

    // find u vector and normalize it
    this->u = new Vector3f(this->lookat->cross(*this->up));
    this->u->normalize();

    // find v vector and normalize it
    this->v = new Vector3f(this->u->cross(*this->lookat));
    this->v->normalize();

    // find alpha
    this->alpha = float(tan((this->fov * 0.5 )* (M_PI/180)));

    // find the size of one pixel
    this->s = 2 * this->alpha / float(this->resolution.height);

    // find the top centre of projection plane
    this->b = new Vector3f(*this->a + this->alpha * *this->v);

    // find the top left corner of the projection plane
    this->c = new Vector3f(*this->b - (*this->u * (this->s * float(this->resolution.width)/2)));

}

Ray Camera::generateRay(int positionX, int positionY) {

    // width offset
    Vector3f xOffset = (*this->u * (float(positionX) * this->s + this->s/2));

    // height offset
    Vector3f yOffset = (*this->v * (float(positionY) * this->s + this->s/2));

    // direction of the ray
    Vector3f *rayDirection = new Vector3f(*this->c + xOffset - yOffset);

    // origin of the ray
    Vector3f *rayOrigin = new Vector3f(*this->position);

    return {rayOrigin, rayDirection};

}

Ray Camera::generateRay(int positionX, int positionY, float grids, int xPlacement, int yPlacement) {

    // new delta
    float newDelta = this->s/grids;

    // width offset
    Vector3f xOffset = (*this->u * (float(positionX) * this->s + newDelta/2 * float(xPlacement)));

    // height offset
    Vector3f yOffset = (*this->v * (float(positionY) * this->s + newDelta/2 * float(yPlacement)));

    // direction of the ray
    Vector3f *rayDirection = new Vector3f(*this->c + xOffset - yOffset);

    // origin of the ray
    Vector3f *rayOrigin = new Vector3f(*this->position);

    return {rayOrigin, rayDirection};

}

Ray Camera::generateRay(int positionX, int positionY, float grids, int xPlacement, int yPlacement, float randomNumX, float randomNumY) {

    // new delta
    float newDelta = this->s/grids;

    // width offset
    Vector3f xOffset = (*this->u * (float(positionX) * this->s + (newDelta * randomNumX) * float(xPlacement)));

    // height offset
    Vector3f yOffset = (*this->v * (float(positionY) * this->s + (newDelta * randomNumY) * float(yPlacement)));

    // direction of the ray
    Vector3f *rayDirection = new Vector3f(*this->c + xOffset - yOffset);

    // origin of the ray
    Vector3f *rayOrigin = new Vector3f(*this->position);

    return {rayOrigin, rayDirection};

}

void Camera::cameraGeometryInfo() {

    cout << "lookat normalized" << endl << *this->lookat << endl;

    cout << "up normalized" << endl << *this->up << endl;

    cout << "Aspect Ratio:" << endl << this->aspectRatio << endl;

    cout << "a: " << endl << *this->a << endl;

    cout << "u:" << endl << *this->u << endl;

    cout << "v:" << endl << *this->v << endl;

    cout << "alpha:" << endl << this->alpha << endl;

    cout << "s: " << endl << this->s << endl;

    cout << "b: " << endl << *this->b << endl;

    cout << "c:" << endl << *this->c << endl;

}
//------------------