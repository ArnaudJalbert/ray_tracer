//
// Created by Arnaud Jalbert on 2023-01-26.
//

#include "RayTracer.h"

RayTracer::RayTracer(nlohmann::json j) {

    this->json = j;

    this->parseItems();

}

int RayTracer::run() {

    for(auto output: outputs){
        currentOutput = output;
        currentOutput->camera->initCameraGeometry();

        this->render();
    }


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

    // retrieving the array of outputs
    auto outputArray = this->json["output"];

    for(auto output: outputArray){

        Output* newOutput = new Output();

        // ray tracer parameters
        newOutput->filename = output["filename"];
        newOutput->resolution.width = output["size"][0];
        newOutput->resolution.height = output["size"][1];
        newOutput->bgColor = RGBColor(output["bkc"][0],
                                 output["bkc"][1],
                                 output["bkc"][2]);
        // optional parameters
        try {
            newOutput->globalIllum = output["globalillum"];
        } catch(...) { cout << "No global illumination" << endl;}

        try {
            newOutput->maxBounces = output["maxbounces"];
        } catch(...) { cout << "No max bounces" << endl;}

        try {
            newOutput->probTerminate = output["probterminate"];
        } catch(...) { cout << "No probterminate" << endl;}

        try {
            newOutput->raysPerPixel[0] = output["raysperpixel"][0];
            newOutput->raysPerPixel[1] = output["raysperpixel"][1];
        } catch(...) { cout << "No raysperpixel" << endl;}


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
                                    fov, newOutput->resolution.width, newOutput->resolution.height);

        newOutput->camera = camera;

        outputs.push_back(newOutput);

    }
}
//------------

//-----------------
// render the scene
bool RayTracer::distanceTest(Vector3f* point, HitPoint* closest, Vector3f* origin){

    // check that it intersected
    if (point == nullptr) return false;

    // make sure that the closest point is initialized
    if (closest->point == nullptr) closest->point = point;

    // check if z is closer
    if (Geometry::vectorDistance(origin, point)
        <= Geometry::vectorDistance(origin, closest->point)){

        // the point is closer
        return true;
    }

    // the point is further than the actual closest point
    return false;
}

float RayTracer::randomFloat(float base, float offset){

    std::default_random_engine e;
    std::uniform_real_distribution<> dis(-1,1); // range -1 - 1

    float num = base * float(dis(e)) + offset;


    return num;
}

void RayTracer::localIllumination(HitPoint* hitPoint, RGBColor* color) {

    // geometry properties
    Geometry* geo = hitPoint->geo;

    // ray properties
    Ray* ray = hitPoint->ray;

    // normal of the point
    Vector3f N = *hitPoint->normal;

    RGBColor diffuse = RGBColor(0,0,0);

    RGBColor specular = RGBColor(0,0,0);

    bool shadow = false;

    // point lights
    for(auto light: pointLights){

        // light direction
        Vector3f L = *light->getCentre() - *hitPoint->point;
        L.normalize();

        // reflected ray
        Vector3f R = (2 * (N.dot(L))) * N - L;
        R.normalize();

        // vector to viewer
        Vector3f V = - Vector3f(hitPoint->point->x(), hitPoint->point->y(), hitPoint->point->z());
        V.normalize();

        Vector3f H = L + V;
        H.normalize();

        float diffuseCoefficient = fmax(0.0f, N.dot(L));

        diffuse = diffuse + (diffuseCoefficient * light->getDiffuseIntensity() * geo->getDiffuseColor());

        float specularCoefficient = fmax(N.dot(H), 0.0f);

        specularCoefficient = pow(specularCoefficient, geo->getPhongCoefficient());

        specular = specular + (specularCoefficient * light->getSpecularIntensity() * geo->getSpecularColor());

        // check if it's in shadow

        if (inShadow(hitPoint, light->getCentre()))
            shadow = true;

    }

    // area lights
    for(auto light: areaLights){

        // light direction
        Vector3f L = *light->getCentre() - *hitPoint->point;
        L.normalize();

        // reflected ray
        Vector3f R = (2 * (N.dot(L))) * N - L;
        R.normalize();

        // vector to viewer
        Vector3f V = - Vector3f(-ray->getBeam()->x(), ray->getBeam()->y(), ray->getBeam()->z());
        V.normalize();

        Vector3f H = (V + L);

        float diffuseCoefficient = fmax(0.0f, N.dot(L));

        diffuse = diffuse + (diffuseCoefficient * light->getDiffuseIntensity() * geo->getDiffuseColor());

        float specularCoefficient = fmax(R.dot(H), 0.0f);

        specularCoefficient = pow(specularCoefficient, geo->getPhongCoefficient());

        specular = specular + (specularCoefficient * light->getSpecularIntensity() * geo->getSpecularColor());

        if (inShadow(hitPoint, light->getCentre()))
            shadow = true;

    }


    // ambient lighting
    RGBColor ambient = geo->getAmbientReflection() * geo->getAmbientColor();

    *color = ambient+diffuse+specular;

    if (shadow)
        *color = *color * 0.5;

}

Vector3f RayTracer::randomUnitPoint(HitPoint* hitPoint){

    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(-1, 1);// range -1 - 1

    while (true){

        // random point
        Vector3f randomPoint = Vector3f(float(dis(e)),
                                        float(dis(e)),
                                        float(dis(e)));

        // checking if it is in the unit sphere
        if (randomPoint.norm() >= 1) continue;

        // checking if it is in the hemisphere
        if (randomPoint.dot(*hitPoint->normal) <= 0) continue;

        return randomPoint;
    }
}

bool RayTracer::globalIllumination(Ray *ray, RGBColor *color) {

    HitPoint hitPoint = HitPoint(ray);

    RGBColor sumColor;

    int bounces = 0;

    // looping until we reach the max number of bounces
    for(int i = 0; i < maxBounces; i++){

        static std::default_random_engine e;
        static std::uniform_real_distribution<> dis(0, 1);// range -1 - 1

        if (bounces >= 1 && float(dis(e)) > probTerminate) break;


        // intersecting with the geometries
        intersectGeometry(&hitPoint);

        // check if we intersected
        if (hitPoint.intersected){

            // keeping track of the bounces
            bounces++;

            float attenuation = hitPoint.ray->beam->dot(*hitPoint.normal);

            attenuation = fmax(attenuation, 0.0);

            // compute the brdf
            sumColor = sumColor + (hitPoint.geo->diffuseColor * hitPoint.geo->diffuseReflection * attenuation);

            // computing the next ray
            Vector3f unitPoint = randomUnitPoint(&hitPoint);

            Vector3f direction = *hitPoint.point + unitPoint;

            delete hitPoint.ray;

            hitPoint.ray =  new Ray(hitPoint.point, &direction);


        }else{
            return false;
        }

    }

    // if there is no bounces then we assign the bg color
    if (bounces == 0){
        return false;
    }
    else{

        // we go to the light(s)
        for (auto light: pointLights) {

            // light direction
            Vector3f L = *light->getCentre() - *hitPoint.point;
            L.normalize();

            // diffuse coefficient
            float diffuseCoefficient = fmax(0.0f, hitPoint.normal->dot(L));


            sumColor = sumColor + (diffuseCoefficient * light->getDiffuseIntensity() * hitPoint.geo->getDiffuseColor());

        }

        // we go to the light(s)
        for (auto light: areaLights) {

            // light direction
            Vector3f L = *light->getCentre() - *hitPoint.point;
            L.normalize();

            // diffuse coefficient
            float diffuseCoefficient = fmax(0.0f, hitPoint.normal->dot(L));


            sumColor = sumColor + (diffuseCoefficient * light->getDiffuseIntensity() * hitPoint.geo->getDiffuseColor());

        }

        // sum up the colors and add the lighting
        *color = sumColor*(1.0f/float(bounces));

        return true;
    }



}

bool RayTracer::inShadow(HitPoint* hitPoint, Vector3f *lightPosition){

    Vector3f epsilonPoint = *hitPoint->normal * 0.001 + *hitPoint->point;

    Vector3f rayToLight = *lightPosition - epsilonPoint;

    Ray shadowRay = Ray(&epsilonPoint, &rayToLight);

    HitPoint shadowIntersection = HitPoint(&shadowRay);

    intersectGeometry(&shadowIntersection);

    return shadowIntersection.intersected;
}

HitPoint* RayTracer::intersectSpheres(HitPoint *closest) {

    // checking intersection with spheres
    for(auto sphere: this->spheres){
        // finding the point of intersection
        Vector3f* point = sphere->intersect(closest->ray);

        // if the object is the actual closest to the camera then we calculate the shading
        if(distanceTest(point, closest, closest->ray->getOrigin())) {

            closest->intersected = true;

            closest->point = point;

            closest->geo = sphere;

            // getting the normal of the point
            Vector3f *normal = new Vector3f(*point - *sphere->getCentre());
            normal->normalize();

            closest->normal = normal;

        }

    }

    return closest;

}

HitPoint* RayTracer::intersectRectangle(HitPoint *closest) {

    // checking intersection with rectangles
    for(auto rectangle: this->rectangles){

        Vector3f* point = rectangle->intersect(closest->ray);

        if(distanceTest(point, closest, currentOutput->camera->getPosition())) {

            closest->intersected = true;

            closest->point = point;

            closest->geo = rectangle;

            Vector3f *normal = new Vector3f(Rectangle::getNormal(rectangle->getP1(),
                                                            rectangle->getP2(),
                                                            rectangle->getP3()));

            closest->normal = normal;

        }
    }

    return closest;
}

HitPoint* RayTracer::intersectGeometry(HitPoint *closest) {

    intersectSpheres(closest);

    intersectRectangle(closest);

    return closest;

}

bool RayTracer::render() {

    // resolution of the image
    int width = currentOutput->resolution.width;
    int height =currentOutput->resolution.height;

    // ppm file creation
    ofstream outputFile;
    outputFile.open(currentOutput->filename);

    // ppm parameters
    outputFile << "P3\n" << width << ' ' << height << "\n255\n";

    // iterating over all the pixels
    for(int y = 0; y < height ; y++){
//        cout << y << endl;
        for(int x = 0; x < width; x++){

            // default color
            RGBColor *color = new RGBColor(currentOutput->bgColor.getR(), currentOutput->bgColor.getG(), currentOutput->bgColor.getB());

            // total number of ray sample done
            int totalSamples = 0;

            // generating the ray

            if (globalIllum) {

                Ray *ray = new Ray(this->camera->generateRay(x, y));

                if (globalIllumination(ray, color)) {
                    totalSamples++;
                }

            } else {

                // generating the ray
                Ray *ray = new Ray(currentOutput->camera->generateRay(x, y));

                // this is the closest point to the camera for all intersection
                HitPoint *hitPoint = new HitPoint(ray);

                intersectGeometry(hitPoint);

                if (hitPoint->intersected) {

                    localIllumination(hitPoint, color);

                }


                delete ray;

                delete hitPoint;
            }

            // averaging the color
            if (totalSamples > 0 )
                *color = *color * (1.0f/float(totalSamples));

            // writing color to the file
            color->writeColor(outputFile);

            delete color;

        }

    }

    outputFile.close();

}
