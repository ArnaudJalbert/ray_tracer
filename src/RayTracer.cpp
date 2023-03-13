//
// Created by Arnaud Jalbert on 2023-01-26.
//

#include "RayTracer.h"

RayTracer::RayTracer(nlohmann::json j) {

    this->json = j;

    this->parseItems();

}

int RayTracer::run() {

    this->camera->initCameraGeometry();

    this->render();

    return 1;
}

//------------
// JSON parsing
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
    }
    if(objectType == "light"){
        this->createLightObjects();
    }
    if (objectType == "output"){
        this->createOutputParameters();
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

            cout <<  *sphere << endl;
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

void RayTracer::createLightObjects() {

    // retrieving the array of lights
    auto lightArray = this->json["light"];

    for(auto light: lightArray){

        // these elements are common to the area light and point light

        // intensity values
        RGBColor diffuseIntensity(light["id"][0],
                                  light["id"][1],
                                  light["id"][2]);

        RGBColor specularIntensity(light["is"][0],
                                   light["is"][1],
                                   light["is"][2]);

        if(light["type"] == "area"){

            // creating the four points
            Vector3f* p1 = new Vector3f(light["p1"][0],
                                        light["p1"][1],
                                        light["p1"][2]);

            Vector3f* p2 = new Vector3f(light["p2"][0],
                                        light["p2"][1],
                                        light["p2"][2]);

            Vector3f* p3 = new Vector3f(light["p3"][0],
                                        light["p3"][1],
                                        light["p3"][2]);

            Vector3f* p4 = new Vector3f(light["p4"][0],
                                        light["p4"][1],
                                        light["p4"][2]);

            // creating the object
            // TODO put the right instantiation here when light is implemented
            AreaLight* areaLight = new AreaLight(diffuseIntensity, specularIntensity, p1, p2, p3, p4);

            // adding the object to the list
            this->areaLights.push_back(areaLight);
        }

        if(light["type"] == "point"){

            // creating the centre
            Vector3f* centre = new Vector3f(light["centre"][0],
                                            light["centre"][1],
                                            light["centre"][2]);

            // creating the object
            PointLight* pointLight = new PointLight(diffuseIntensity, specularIntensity, centre);

            // adding the object to the list
            this->pointLights.push_back(pointLight);
        }
    }


}

void RayTracer::createOutputParameters() {

    // retrieving the array of lights
    auto outputArray = this->json["output"];

    for(auto output: outputArray){

        // ray tracer parameters
        this->filename = output["filename"];
        this->resolution.width = output["size"][0];
        this->resolution.height = output["size"][1];

        // camera parameters
        Vector3f *lookat = new Vector3f(output["lookat"][0],
                                        output["lookat"][1],
                                        output["lookat"][2]);

        Vector3f *up = new Vector3f(output["up"][0],
                                    output["up"][1],
                                    output["up"][2]);

        Vector3f *position = new Vector3f(output["centre"][0],
                                          output["centre"][1],
                                          output["centre"][2]);

        float fov = output["fov"];

        Camera *camera = new Camera(lookat, up, position,
                                    fov, this->resolution.width, this->resolution.height);

        this->camera = camera;

    }
}
//------------

//-----------------
// render the scene
bool RayTracer::distanceTest(Vector3f* point, HitPoint* closest, Vector3f* origin){

    // check that it intersected
    if (point == nullptr) return false;

    // make sure that the closest point is initialized
    if (closest->getPoint() == nullptr) closest->setPoint(point);

    // check if z is closer
    if (Geometry::vectorDistance(origin, point)
        <= Geometry::vectorDistance(origin, closest->getPoint())){

        // the point is closer
        return true;
    }

    // the point is further than the actual closest point
    return false;
}

void RayTracer::shading(HitPoint* hitPoint, RGBColor* color) {

    // geometry properties
    Geometry* geo = hitPoint->getGeo();

    // light properties
    PointLight* pointLight = hitPoint->getLight();

    // ray properties
    Ray* ray = hitPoint->getRay();

    // normal of the point
    Vector3f N = *hitPoint->getNormal();

    RGBColor diffuse = RGBColor(0,0,0);

    RGBColor specular = RGBColor(0,0,0);

    for(auto light: pointLights){

        // light direction
        Vector3f L = *pointLight->getCentre() - *hitPoint->getPoint();
        L.normalize();

        // reflected ray
        Vector3f R = (2 * (N.dot(L))) * N - L;
        R.normalize();

        // vector to viewer
        Vector3f V = - Vector3f(-ray->getBeam()->x(), ray->getBeam()->y(), ray->getBeam()->z());
        V.normalize();

        float diffuseCoefficient = fmax(0.0f, N.dot(L));

        diffuse = diffuse + (diffuseCoefficient * pointLight->getDiffuseIntensity() * geo->getDiffuseColor());

        float specularCoefficient = fmax(R.dot(L), 0.0f);

        specularCoefficient = pow(specularCoefficient, geo->getPhongCoefficient());

        specular = specular + (specularCoefficient * pointLight->getSpecularIntensity() * geo->getSpecularColor());
    }

    for(auto light: areaLights){

        // light direction
        Vector3f L = *pointLight->getCentre() - *hitPoint->getPoint();
        L.normalize();

        // reflected ray
        Vector3f R = (2 * (N.dot(L))) * N - L;
        R.normalize();

        // vector to viewer
        Vector3f V = - Vector3f(-ray->getBeam()->x(), ray->getBeam()->y(), ray->getBeam()->z());
        V.normalize();

        float diffuseCoefficient = fmax(0.0f, N.dot(L));

        diffuse = diffuse + (diffuseCoefficient * pointLight->getDiffuseIntensity() * geo->getDiffuseColor());

        float specularCoefficient = fmax(R.dot(L), 0.0f);

        specularCoefficient = pow(specularCoefficient, geo->getPhongCoefficient());

        specular = specular + (specularCoefficient * pointLight->getSpecularIntensity() * geo->getSpecularColor());
    }


    // ambient lighting
    RGBColor ambient = geo->getAmbientReflection() * geo->getAmbientColor();

    *color = ambient+diffuse+specular;

}

bool RayTracer::intersectSpheres(Ray ray, HitPoint *closest) {

    // check if we intersected something
    bool intersected = false;

    // checking intersection with spheres
    for(auto sphere: this->spheres){
        // finding the point of intersection
        Vector3f* point = sphere->intersect(&ray);

        // if the object is the actual closest to the camera then we calculate the shading
        if(distanceTest(point, closest, ray.getOrigin())) {

            intersected = true;

            closest->setPoint(point);

            closest->setGeo(sphere);

            // getting the normal of the point
            Vector3f* normal = new Vector3f(*point - *sphere->getCentre());
            normal->normalize();

            closest->setNormal(normal);

        }

    }

    return intersected;

}

bool RayTracer::intersectRectangle(Ray ray, HitPoint *closest) {

    bool intersected = false;

    // checking intersection with rectangles
    for(auto rectangle: this->rectangles){

        Vector3f* point = rectangle->intersect(&ray);

        if(distanceTest(point, closest, camera->getPosition())) {

            intersected = true;

            closest->setPoint(point);

            closest->setGeo(rectangle);

            Vector3f *normal = new Vector3f(Rectangle::getNormal(rectangle->getP1(),
                                                                 rectangle->getP2(),
                                                                 rectangle->getP3()));

            closest->setNormal(normal);

        }
    }

    return intersected;
}

bool RayTracer::intersectGeometry(Ray ray, HitPoint *closest) {

    bool intersectedSphere = intersectSpheres(ray, closest);

    bool intersectedRectangle = intersectRectangle(ray, closest);

    return intersectedRectangle || intersectedSphere;

}

bool RayTracer::render() {

    // resolution of the image
    int width = this->resolution.width;
    int height = this->resolution.height;

    // ppm file creation
    ofstream outputFile;
    outputFile.open(this->filename);

    // ppm parameters
    outputFile << "P3\n" << width << ' ' << height << "\n255\n";

    // iterating over all the pixels
    for(int y = 0; y < height ; y++){
        for(int x = 0; x < width; x++){

            // generating the ray
            Ray ray = this->camera->generateRay(x,y);

            // default color
            RGBColor *color = new RGBColor(2, 2, 2);

            // this is the closest point to the camera for all intersection
            HitPoint *hitPoint = new HitPoint(nullptr, nullptr, nullptr, &ray);

            bool intersected = intersectGeometry(ray, hitPoint);

            if(intersected) {

                hitPoint->setLight(pointLights[0]);

                shading(hitPoint, color);
            }

            color->writeColor(outputFile);

        }
    }

    outputFile.close();

}
