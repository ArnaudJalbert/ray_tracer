//
// Created by Arnaud Jalbert on 2023-01-31.
//

#ifndef RAYTRACER_AREALIGHT_H
#define RAYTRACER_AREALIGHT_H

#include "Light.h"
#include "PointLight.h"
#include <vector>

using std::vector;

class AreaLight: public Light{

private:

    Vector3f* p1;
    Vector3f* p2;
    Vector3f* p3;
    Vector3f* p4;

public:

    int n;

    AreaLight(const RGBColor &diffuseIntensity, const RGBColor &specularIntensity, Vector3f *p1, Vector3f *p2,
              Vector3f *p3, Vector3f *p4);

    Vector3f *getP1() const{return this->p1;};

    void setP1(Vector3f *p1){ this->p1 = p1;};

    Vector3f *getP2() const{return this->p2;};

    void setP2(Vector3f *p2){ this->p2 = p2;};

    Vector3f *getP3() const{return this->p3;};

    void setP3(Vector3f *p3){ this->p3 = p3;};

    Vector3f *getP4() const{return this->p4;};

    void setP4(Vector3f *p4){ this->p4 = p4;};

    vector<PointLight> getPointLights();
};


#endif //RAYTRACER_AREALIGHT_H
