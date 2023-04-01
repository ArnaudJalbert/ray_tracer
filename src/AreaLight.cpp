//
// Created by Arnaud Jalbert on 2023-01-31.
//

#include "AreaLight.h"
#include <random>

AreaLight::AreaLight(const RGBColor &diffuseIntensity, const RGBColor &specularIntensity, Vector3f *p1, Vector3f *p2,
                     Vector3f *p3, Vector3f *p4){

    this->setDiffuseIntensity(diffuseIntensity);
    this->setSpecularIntensity(specularIntensity);

    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;

    Vector3f centre = Vector3f((*p1+*p2+*p3+*p4)/4);

    this->areaCentre = centre;

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
    float yStep = *yMax - *yMin;
    float zStep = *zMax - *zMin;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    for (int j = 0; j < n; ++j) {
        for (int l = 0; l < n; ++l) {
            for (int k = 0; k < n; ++k) {
                float x_center = *xMin + dis(gen) * xStep;
                float y_center = *yMin + dis(gen) * yStep;
                float z_center = *zMin + dis(gen) * zStep;
                PointLight light = PointLight(this->getDiffuseIntensity(), this->getSpecularIntensity(), Vector3f(x_center, y_center, z_center));
//                cout << light << endl;
                pointLights.push_back(light);
            }
        }
    }

    return pointLights;
}
