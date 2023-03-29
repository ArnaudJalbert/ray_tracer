//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "AreaLight.h"

AreaLight::AreaLight(const RGBColor &diffuseIntensity, const RGBColor &specularIntensity, Vector3f *p1, Vector3f *p2,
                     Vector3f *p3, Vector3f *p4){

    this->setDiffuseIntensity(diffuseIntensity);
    this->setSpecularIntensity(specularIntensity);

    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;

    Vector3f centre = Vector3f((*p1+*p2+*p3+*p4)/4);

    this->setCentre(centre);

}

vector <PointLight> AreaLight::getPointLights() {

    vector<PointLight> pointLights;

    // Find the midpoint of the line connecting p1 and p2
    Vector3f midPoint12 = Vector3f();
    midPoint12.x() = (this->p1->x() + this->p2->x()) / 2;
    midPoint12.y() = (this->p1->y() + this->p2->y()) / 2;
    midPoint12.z() = (this->p1->z() + this->p2->z()) / 2;
    PointLight light12 = PointLight(this->getDiffuseIntensity(), this->getSpecularIntensity(), midPoint12);
    pointLights.push_back(light12);

    // Find the midpoint of the line connecting p2 and p3
    Vector3f midPoint13 = Vector3f();
    midPoint13.x() = (this->p1->x() + this->p3->x()) / 2;
    midPoint13.y() = (this->p1->y() + this->p3->y()) / 2;
    midPoint13.z() = (this->p1->z() + this->p3->z()) / 2;
    PointLight light13 = PointLight(this->getDiffuseIntensity(), this->getSpecularIntensity(), midPoint13);
    pointLights.push_back(light13);

    // Find the midpoint of the line connecting p3 and p4
    Vector3f midPoint14 = Vector3f();
    midPoint14.x() = (this->p1->x() + this->p4->x()) / 2;
    midPoint14.y() = (this->p1->y() + this->p4->y()) / 2;
    midPoint14.z() = (this->p1->z() + this->p4->z()) / 2;
    PointLight light14 = PointLight(this->getDiffuseIntensity(), this->getSpecularIntensity(), midPoint14);
    pointLights.push_back(light14);

    // Find the midpoint of the line connecting p4 and p1
    Vector3f midPoint41 = Vector3f();
    midPoint41.x() = (this->p4->x() + this->p1->x()) / 2;
    midPoint41.y() = (this->p4->y() + this->p1->y()) / 2;
    midPoint41.z() = (this->p4->z() + this->p1->z()) / 2;
    PointLight light41 = PointLight(this->getDiffuseIntensity(), this->getSpecularIntensity(), midPoint41);
    pointLights.push_back(light41);

    return pointLights;
}

