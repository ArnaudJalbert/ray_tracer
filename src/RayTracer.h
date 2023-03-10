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
#include "RGBColor.h"

// ray include
#include "Ray.h"

// geometry includes
#include "Sphere.h"
#include "Rectangle.h"
#include "HitPoint.h"

// lights includes
#include "PointLight.h"
#include "AreaLight.h"

// camera includes
#include "Camera.h"

#define HALF_VECTOR Vector3f(0.5f, 0.5f, 0.5f)



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
#define TEST_WIDTH 500
#define TEST_HEIGHT 500
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

    // vectors of light objects
    // area lights
    vector<AreaLight*> areaLights;

    // point lights
    vector<PointLight*> pointLights;

    // camera of the scene
    Camera* camera;

    // resolution of the image
    struct resolution{
        int width;
        int height;
    } resolution;

    // filename in which to output the results
    string filename;

    //-------------
    // JSON parsing

    // parse the items in the json object
    void parseItems();

    // create the object
    void createObjects(const string& objectType);

    // creates the geometry objects
    void createGeometryObjects();

    // create the light objects
    void createLightObjects();

    // create the output parameters
    void createOutputParameters();
    //-------------

    //-----------------
    // render the scene
    bool distanceTest(Vector3f* point, Vector3f* closest, Vector3f* origin);

    RGBColor shading(HitPoint* point);


    HitPoint intersectSpheres(Ray ray, Vector3f* closest);

    Vector3f* intersectRectangle(Ray ray, Vector3f* closest);

    HitPoint* intersectGeometry(Ray ray, Vector3f* closest);

    bool render();
    //-----------------


public:

    // constructor called in main
    explicit RayTracer(nlohmann::json j);

    // method called in main
    // it's the only method called in main so everything should start from here
    int run();


};


#endif //RAYTRACER_RAYTRACER_H
