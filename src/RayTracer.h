//
// Created by Arnaud Jalbert on 2023-01-26.
//

#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include <iostream>
#include <fstream>
#include <vector>

#include <Eigen/Dense>
#include <vector>

#include "json.hpp"

// color include
#include "RGBColor/RGBColor.h"

// ray include
#include "Ray/Ray.h"

// geometry includes
#include "Geometry/Sphere.h"
#include "Geometry/Rectangle.h"

// lights includes
#include "Light/PointLight.h"
#include "Light/AreaLight.h"

// camera includes
#include "Camera/Camera.h"



using std::cout;
using std::endl;
using std::cerr;
using std::flush;

using std::string;
using std::ofstream;

using std::vector;

using Eigen::Vector3f;

#define DEFAULT_WIDTH 256
#define DEFAULT_HEIGHT 256

// 16:9 ratio
#define TEST_WIDTH 1920
#define TEST_HEIGHT 1080
#define TEST_ASPECT_RATIO (float(TEST_WIDTH)/float(TEST_HEIGHT))

class RayTracer {

private:

    nlohmann::json json;

    //--------
    // elements of the scenes

    // vectors of geometry pointers

    // rectangles
    vector<Rectangle*> rectangles;

    // spheres
    vector<Sphere*> spheres;

    // array of light objects -> point or area
    Light* lights;

    // camera of the scene
    Camera* camera;

    // resolution of the image
    struct resolution {
        int x;
        int y;
    };

    //--------
    // methods

    // parse the items in the json object
    void parseItems();

    // create the object
    void createObjects(const string& objectType);

    // creates the geometry objects
    void createGeometryObjects();
    //--------

public:

    // constructor called in main
    explicit RayTracer(nlohmann::json j);

    // method called in main
    // it's the only method called in main so everything should start from here
    int run();


};


#endif //RAYTRACER_RAYTRACER_H
