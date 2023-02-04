//
// Created by Arnaud Jalbert on 2023-01-26.
//

#include <iostream>
#include <fstream>
#include <Eigen/Dense>

#include "RayTracer.h"
#include "RGBColor/RGBColor.h"
#include "Ray/Ray.h"
#include "Geometry/Sphere.h"

using std::cout;
using std::endl;
using std::ofstream;
using std::cerr;
using std::flush;

using Eigen::Vector3f;

#define DEFAULT_WIDTH 256
#define DEFAULT_HEIGHT 256

// 16:9 ratio
#define TEST_WIDTH 1920
#define TEST_HEIGHT 1080
#define TEST_ASPECT_RATIO (float(TEST_WIDTH)/float(TEST_HEIGHT))

RayTracer::RayTracer(nlohmann::json j) {
    this->json = j;
}

bool hitSphere(Sphere sphere, Ray ray){
    Vector3f oc = ray.getOrigin() - sphere.getCentre();
    float a = ray.getDirection().dot(ray.getDirection());
    auto b = 2.0f * oc.dot(ray.getDirection());
    auto c = oc.dot(oc) - sphere.getRadius()*sphere.getRadius();
    auto discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}


RGBColor rayColor(Ray & ray, Sphere & sphere){
    if(hitSphere(sphere, ray))
        return RGBColor(1,0,0);
    Vector3f unitDirection = ray.getDirection().normalized();
    auto t = 0.5f*(unitDirection.y()+1.0f);
    return (1.0f-t) * RGBColor(1.0f,1.0f,1.0f) + (t * RGBColor(0.5f, 0.7f, 1.0f));
}

void graphicsHelloWorld(){

    // ppm file creation
    ofstream helloWorldlFile;
    helloWorldlFile.open("HelloWorld.ppm");

    // ppm parameters
    helloWorldlFile << "P3\n" << DEFAULT_WIDTH << ' ' << DEFAULT_HEIGHT << "\n255\n";

    // writing the pixels
    for(int y = 0; y < DEFAULT_HEIGHT; ++y){

        // progress
        cerr << "Remaining Scanlines: " << DEFAULT_HEIGHT-y << "\n" << flush;

        for (int x = 0; x < DEFAULT_WIDTH; ++x) {

            // computing the color
            RGBColor pixel = RGBColor(float(x) / (DEFAULT_WIDTH-1), float(y)/ (DEFAULT_HEIGHT-1), 0.25f);

            // writing it ti the PPM file
            pixel.writeColor(helloWorldlFile);

        }
    }

    helloWorldlFile.close();

}

void sendRaysInScene(){

    //ppm file
    ofstream shootRay;
    shootRay.open("ShootRay.ppm");

    // camera
    auto viewport_height = 2.0f;
    auto viewport_width = TEST_ASPECT_RATIO * viewport_height;
    auto focal_length = 1.0f;

    auto origin = Vector3f (0, 0, 0);
    auto horizontal = Vector3f(viewport_width, 0, 0);
    auto vertical = Vector3f(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vector3f (0, 0, focal_length);

    // Render
    shootRay << "P3\n" << TEST_WIDTH << " " << TEST_HEIGHT << "\n255\n";

    // sphere
    Sphere sphere = Sphere(0.5f, Vector3f(0.5f,0,-1));

    for (int j = TEST_HEIGHT-1; j >= 0; --j) {

        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < TEST_WIDTH; ++i) {
            auto u = float(i) / (TEST_WIDTH-1);
            auto v = float(j) / (TEST_HEIGHT-1);
            Ray ray = Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            RGBColor pixel_color = rayColor(ray, sphere);
            pixel_color.writeColor(shootRay);
        }
    }

    shootRay.close();

}



int RayTracer::run() {
    cout << "In run() method of RayTracer!" << endl;

    graphicsHelloWorld();

    sendRaysInScene();


    return 1;
}
