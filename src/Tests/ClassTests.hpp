//
// Created by Arnaud Jalbert on 2023-02-02.
//

// including all classes
using namespace std;

#include <iostream>
#include <string>

#include "../RGBColor/RGBColor.h"
#include "../Geometry/Geometry.h"
#include "../Geometry/Sphere.h"
#include "../Geometry/Rectangle.h"
#include "../Light/Light.h"

#define FLOAT_0_1 (0.05f)
#define FLOAT_GREATER_1 (1.5f)
#define FLOAT_LESS_1 (-0.5f)

void SphereTest(){
    cout << "------------------" << endl;
    cout << "Sphere Class Test" << endl;
    Sphere sphereTest = Sphere();
    cout << sphereTest << endl;
    cout << "------------------" << endl;
}

void RectangleTest(){
    cout << "------------------" << endl;
    cout << "Rectangle Class Test" << endl;
    Rectangle rectangleTest = Rectangle();
    cout << rectangleTest << endl;
    cout << "------------------" << endl;
}

void LightTest(){
    cout << "------------------" << endl;
    cout << "Light Class Test" << endl;
    Light lightTest = Light();
    cout << lightTest << endl;
    cout << "------------------" << endl;
}


void runTests(){
    cout << "Running Class Tests" << endl;
    SphereTest();
    RectangleTest();
    LightTest();
}