//
// Created by Arnaud Jalbert on 2023-01-26.
//

#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include <iostream>

#include "json.hpp"

using std::cout;
using std::endl;

class RayTracer {

private:

    nlohmann::json json;

public:

    // constructor called in main
    explicit RayTracer(nlohmann::json j);

    // method called in main
    // it's the only method called in main so everything should start from here
    int run();


};


#endif //RAYTRACER_RAYTRACER_H
