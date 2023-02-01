//
// Created by Arnaud Jalbert on 2023-01-26.
//

#include <iostream>

#include "RayTracer.h"

RayTracer::RayTracer(nlohmann::json j) {
    this->json = j;
}

int RayTracer::run() {
    cout << "In run() method of RayTracer!" << endl;
    return 1;
}
