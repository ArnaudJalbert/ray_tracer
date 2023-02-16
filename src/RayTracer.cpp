//
// Created by Arnaud Jalbert on 2023-01-26.
//

#include "RayTracer.h"

RayTracer::RayTracer(nlohmann::json j) {

    this->json = j;

    this->parseItems();

}

int RayTracer::run() {


    return 1;
}

void RayTracer::parseItems() {

    // iterating over the items in the json objects
    for(const auto& item : this->json.items()){

        // getting the item's name -> {"geometry", "light", "output"}
        const string& itemName = item.key();

        // creating the right object type
        this->createObjects(itemName);
    }
}

void RayTracer::createObjects(const string& objectType) {

    if(objectType == "geometry"){
        this->createGeometryObjects();

        // TESTING
//        cout << "RECTANGLES" << endl;
//        for(auto e: this->rectangles)
//            cout << *e << endl;
//
//        cout << "SPHERES" << endl;
//        for(auto e: this->spheres)
//            cout << *e << endl;
        // END OF TESTING
    }
    if(objectType == "geometry"){

    }
}

void RayTracer::createGeometryObjects() {

    // retrieving the array of geometries
    auto geometryArray = this->json["geometry"];

    // iterating over all the objects in the geometry array
    for(auto geometry: geometryArray){

        // these elements are common to the sphere and the rectangle

        // reflection values
        float ambientReflection = geometry["ka"];
        float diffuseReflection = geometry["kd"];
        float specularReflection = geometry["ks"];

        // color values
        RGBColor ambientColor(geometry["ac"][0],
                              geometry["ac"][1],
                              geometry["ac"][2]);

        RGBColor diffuseColor(geometry["dc"][0],
                              geometry["dc"][1],
                              geometry["dc"][2]);

        RGBColor specularColor(geometry["sc"][0],
                               geometry["sc"][1],
                               geometry["sc"][2]) ;

        // phong coefficient
        float phongCoefficient = geometry["pc"];


        if(geometry["type"] == "sphere"){

            // creating the four points
            Vector3f* centre = new Vector3f(geometry["centre"][0],
                                            geometry["centre"][1],
                                            geometry["centre"][2]);

            // getting the radius
            float radius = geometry["radius"];

            Sphere* sphere = new Sphere(ambientReflection,
                                        diffuseReflection,
                                        specularReflection,
                                        phongCoefficient,
                                        ambientColor,
                                        diffuseColor,
                                        specularColor,
                                        radius, centre);

            // adding the sphere to the list
            this->spheres.push_back(sphere);
        }

        if(geometry["type"] == "rectangle"){

            // creating the four points
            Vector3f* p1 = new Vector3f(geometry["p1"][0],
                                        geometry["p1"][1],
                                        geometry["p1"][2]);

            Vector3f* p2 = new Vector3f(geometry["p2"][0],
                                        geometry["p2"][1],
                                        geometry["p2"][2]);

            Vector3f* p3 = new Vector3f(geometry["p3"][0],
                                        geometry["p3"][1],
                                        geometry["p3"][2]);

            Vector3f* p4 = new Vector3f(geometry["p4"][0],
                                        geometry["p4"][1],
                                        geometry["p4"][2]);

            // creating the object
            Rectangle* rectangle = new Rectangle(ambientReflection,
                                                 diffuseReflection,
                                                 specularReflection,
                                                 phongCoefficient,
                                                 ambientColor,
                                                 diffuseColor,
                                                 specularColor,
                                                 p1, p2, p3, p4);

            // adding the rectangle to the list
            this->rectangles.push_back(rectangle);

        }
    }
}


// TEMPORARY -> FOR DEVELOPPEMENT

bool hitSphere(Sphere sphere, Ray ray){
    Vector3f oc = ray.getOrigin() - *sphere.getCentre();
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
    Sphere sphere = Sphere(0.5f, new Vector3f(0.5f,0,-1));

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