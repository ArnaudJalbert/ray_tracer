//
// Created by Arnaud Jalbert on 2023-01-26.
//

#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

// namespaces
using namespace std;

// C++ libraries includes

// system and local libraries include
#include "json.hpp"

class RayTracer {

public:

    // constructor called in main
    explicit RayTracer(nlohmann::json j);

    // method called in main
    // it's the only method called in main so everything should start from here
    int run();

private:
    nlohmann::json json;
};


#endif //RAYTRACER_RAYTRACER_H
