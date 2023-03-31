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

    vector<float> xList;
    xList.push_back(p1->x());
    xList.push_back(p2->x());
    xList.push_back(p3->x());
    xList.push_back(p4->x());

    vector<float> yList;
    yList.push_back(p1->y());
    yList.push_back(p2->y());
    yList.push_back(p3->y());
    yList.push_back(p4->y());

    vector<float> zList;
    zList.push_back(p1->z());
    zList.push_back(p2->z());
    zList.push_back(p3->z());
    zList.push_back(p4->z());

    auto xMin = std::min_element(xList.begin(), xList.end());
    auto yMin = std::min_element(yList.begin(), yList.end());
    auto zMin = std::min_element(zList.begin(), zList.end());

    auto xMax = std::max_element(xList.begin(), xList.end());
    auto yMax = std::max_element(yList.begin(), yList.end());
    auto zMax = std::min_element(zList.begin(), zList.end());

    float xStep = *xMax - *xMin;
    float yStep = *yMax - *zMin;
    float zStep = *zMax - *zMin;

    for (int j = 0; j < 5; ++j) {
        for (int l = 0; l < 5; ++l) {
            for (int k = 0; k < 5; ++k) {
                float x_center = *xMin + (j + 0.5f) * xStep;
                float y_center = *yMin + (l + 0.5f) * yStep;
                float z_center = *zMin + (k + 0.5f) * zStep;
                PointLight light = PointLight(this->getDiffuseIntensity(), this->getSpecularIntensity(), Vector3f(x_center, y_center, z_center));
                pointLights.push_back(light);
            }
        }
    }

    return pointLights;
}

//float x = (this->p1->x() + this->p2->x()) / divider;
//float y = (this->p1->y() + this->p2->y()) / divider;
//float z = (this->p1->z() + this->p2->z()) / divider;
//// Find the midpoint of the line connecting p1 and p2
//Vector3f midPoint12 = Vector3f(x, y, z);
//PointLight light12 = PointLight(this->getDiffuseIntensity(), this->getSpecularIntensity(), midPoint12);
//pointLights.push_back(light12);
//
//
//x = (this->p1->x() + this->p3->x()) / divider;
//y = (this->p1->y() + this->p3->y()) / divider;
//z = (this->p1->z() + this->p3->z()) / divider;
//// Find the midpoint of the line connecting p2 and p3
//Vector3f midPoint13 = Vector3f(x, y, z);
//PointLight light13 = PointLight(this->getDiffuseIntensity(), this->getSpecularIntensity(), midPoint13);
//pointLights.push_back(light13);
//
//x = (this->p1->x() + this->p4->x()) / divider;
//y = (this->p1->y() + this->p4->y()) / divider;
//z = (this->p1->z() + this->p4->z()) / divider;
//// Find the midpoint of the line connecting p3 and p4
//Vector3f midPoint14 = Vector3f(x, y, z);
////    cout << midPoint14 << endl;
//PointLight light14 = PointLight(this->getDiffuseIntensity(), this->getSpecularIntensity(), midPoint14);
//pointLights.push_back(light14);
//
//x = (this->p4->x() + this->p1->x()) / divider;
//y = (this->p4->y() + this->p1->y()) / divider;
//z = (this->p4->z() + this->p1->z()) / divider;
//// Find the midpoint of the line connecting p4 and p1
//Vector3f midPoint41 = Vector3f(x, y, z);
//PointLight light41 = PointLight(this->getDiffuseIntensity(), this->getSpecularIntensity(), midPoint41);
//pointLights.push_back(light41);