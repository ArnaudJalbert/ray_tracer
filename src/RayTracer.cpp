//
// Created by Arnaud Jalbert on 2023-01-26.
//

#include <iostream>
#include <fstream>

#include "RayTracer.h"
#include "RGBColor/RGBColor.h"

using std::cout;
using std::endl;
using std::ofstream;
using std::cerr;
using std::flush;

RayTracer::RayTracer(nlohmann::json j) {
    this->json = j;
}

int graphicsHelloWorld(){

    // resolution of the image
    const int width = 256;
    const int height = 256;

    // ppm file creation
    ofstream helloWorldlFile;
    helloWorldlFile.open("HelloWorld.ppm");

    // ppm parameters
    helloWorldlFile << "P3\n" << width << ' ' << height << "\n255\n";

    // writing
    for(int y = 0; y < height; ++y){
        // progress
        cerr << "Remaining Scanlines: " << height-y << "\n" << flush;
        for (int x = 0; x < width; ++x) {

            RGBColor pixel = RGBColor(float(x) / (width-1), float(y)/ (height-1), 0.25f);

            pixel.writeColor(helloWorldlFile);

        }
    }

    helloWorldlFile.close();

}

int RayTracer::run() {
    cout << "In run() method of RayTracer!" << endl;

    graphicsHelloWorld();

    return 1;
}
