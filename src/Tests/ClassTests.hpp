//
// Created by Arnaud Jalbert on 2023-02-02.
//

// including all classes
using namespace std;

#include <iostream>
#include <string>

#include "../Geometry/Geometry.h"
#include "../RGBColor/RGBColor.h"
#include "../Geometry/Sphere.h"

#define FLOAT_0_1 (0.05f)
#define FLOAT_GREATER_1 (1.5f)
#define FLOAT_LESS_1 (-0.5f)


void GeometryTest(){
    cout << "-------------------" << endl;
    cout << "Geometry Class Test" << endl;
    Geometry geoTest = Geometry();
    cout << geoTest << endl;
    cout << "-------------------" << endl;
}

void SphereTest(){
    cout << "------------------" << endl;
    cout << "Sphere Class Test" << endl;
    Sphere sphereTest = Sphere();
    cout << sphereTest << endl;
    cout << "------------------" << endl;
}


void runTests(){
    cout << "Running Class Tests" << endl;
    GeometryTest();
    SphereTest();
}