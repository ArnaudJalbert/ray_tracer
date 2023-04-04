//
// Created by Arnaud Jalbert on 2023-01-26.
//

#include "RayTracer.h"

RayTracer::RayTracer(nlohmann::json j) {

    this->json = j;

    this->parseItems();

}

void RayTracer::run() {

    for(auto output: outputs){
        currentOutput = output;
        currentOutput->camera->initCameraGeometry();

        this->render();
    }

    for(auto rectangle: rectangles){
        delete rectangle;
    }

    for(auto areaLight: areaLights){
        delete areaLight;
    }

    for (auto output: outputs){
        delete output;
    }

    for(auto pointLight: pointLights){
        delete pointLight;
    }

    for(auto sphere: spheres){
        delete sphere;
    }

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
            Vector3f centre = Vector3f(geometry["centre"][0],
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

        try{
            if (!light["use"])
                continue;
        }catch(...){}

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
            AreaLight* areaLight = new AreaLight(diffuseIntensity, specularIntensity, p1, p2, p3, p4);

            try{
                areaLight->n = light["n"];
            }catch(...){areaLight->n = 8;}

            // adding the object to the list
            this->areaLights.push_back(areaLight);
        }

        if(light["type"] == "point"){

            // creating the centre
            Vector3f centre = Vector3f(light["centre"][0],
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
        // file outputs
        newOutput->filename = output["filename"];

        // resolution
        newOutput->resolution.width = output["size"][0];
        newOutput->resolution.height = output["size"][1];

        // background color
        newOutput->bgColor = RGBColor(output["bkc"][0],
                                     output["bkc"][1],
                                     output["bkc"][2]);



        // ambient intensity
        // optional parameters
        try {
            newOutput->globalIllum = output["globalillum"];
        } catch(...) { newOutput->globalIllum = false;}

        try {
            newOutput->maxBounces = output["maxbounces"];
        } catch(...) { newOutput->maxBounces = 3;}

        try {
            newOutput->probTerminate = output["probterminate"];
        } catch(...) { newOutput->probTerminate = 0.33;}

        try {
            newOutput->raysPerPixel[0] = output["raysperpixel"][0];
            newOutput->raysPerPixel[1] = output["raysperpixel"][0];
            newOutput->raysPerPixel[2] = output["raysperpixel"][0];
        } catch(...) {
            newOutput->raysPerPixel[0] = 10;
            newOutput->raysPerPixel[1] = 10;
            newOutput->raysPerPixel[2] = 1;}

        try {
            newOutput->raysPerPixel[2] = output["raysperpixel"][1];
        } catch(...) {newOutput->raysPerPixel[2] = 1;}

        try {
            float temp = newOutput->raysPerPixel[2];
            newOutput->raysPerPixel[2] = output["raysperpixel"][2];
            newOutput->raysPerPixel[1] = temp;
        } catch(...) {}

        try {
           newOutput->anitAliasing = output["antialiasing"];
        } catch(...) { newOutput->anitAliasing = false;}

        try{
            newOutput->ai = RGBColor(output["ai"][0],output["ai"][1],output["ai"][2]);
        } catch (...){newOutput->ai = RGBColor(1,1,1);}

        try{
            newOutput->n = output["n"];
        } catch (...){newOutput->n = 10;}

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
bool RayTracer::distanceTest(Vector3f point, HitPoint* closest, Vector3f* origin){

    // check that it intersected
    if (point.x() >= INFINITY) return false;

    // make sure that the closest point is initialized
    if (closest->point.x() == INFINITY){closest->point = point;}

    // check if z is closer
    if (Geometry::vectorDistance(*origin, point)
        <= Geometry::vectorDistance(*origin, closest->point)){
        // the point is closer
        return true;
    }

    // the point is further than the actual closest point
    return false;
}

void RayTracer::localIllumination(HitPoint* hitPoint, RGBColor* color) {

    // geometry properties
    Geometry* geo = hitPoint->geo;

    // ray properties
    Ray* ray = hitPoint->ray;

    // normal of the point
    Vector3f N = hitPoint->normal;

    RGBColor diffuse = RGBColor(0,0,0);

    RGBColor specular = RGBColor(0,0,0);

    // point lights
    for(auto light: pointLights){

        float shadowAttenuation = 1.0f;
        float specularAttenuation = 1.0f;

        // light direction
        Vector3f L = light->centre - hitPoint->point;
        L.normalize();

        // vector to viewer
        Vector3f V = - Vector3f(hitPoint->ray->beam.x(), hitPoint->ray->beam.y(), hitPoint->ray->beam.z());
        V.normalize();

        Vector3f H = (L + V);
        H.normalize();

        // checking shadows
        Ray lightDirection = Ray(hitPoint->point + (hitPoint->normal * 0.01), light->centre);
        HitPoint shadowHit = HitPoint(&lightDirection);
        intersectGeometry(&shadowHit);

        if (shadowHit.intersected && shadowHit.geo != geo){
            if ((shadowHit.point - hitPoint->point).norm()+0.100 < (light->centre - hitPoint->point).norm()) {
                shadowAttenuation = 0.0f;
                specularAttenuation = 0.0f;
            }
        }

        float diffuseCoefficient = fmax(0.0f, N.dot(L));

        diffuse = diffuse + (diffuseCoefficient * light->getDiffuseIntensity() * geo->getDiffuseColor() * shadowAttenuation);

        float specularCoefficient = fmax(N.dot(H), 0.0f);

        specularCoefficient = pow(specularCoefficient, geo->getPhongCoefficient());

        specular = specular + (specularCoefficient * light->getSpecularIntensity() * geo->getSpecularColor() * specularAttenuation);

    }

    // area lights
    for(auto light: areaLights){
        RGBColor diffuseSum = RGBColor(0,0,0);
        RGBColor specularSum = RGBColor(0,0,0);

        vector<PointLight> separateLights = light->getPointLights();

        float size = float(separateLights.size());

        for (int i = 0; i < size; i++) {

            float shadowAttenuation = 1.0f;
            float specularAttenuation = 1.0f;

            // light direction
            Vector3f L = light->areaCentre - hitPoint->point;
            L.normalize();

            // vector to viewer
            Vector3f V = - Vector3f(hitPoint->ray->beam.x(), hitPoint->ray->beam.y(), hitPoint->ray->beam.z());
            V.normalize();

            Vector3f H = (L + V);
            H.normalize();

            // checking shadows
            Ray lightDirection = Ray(hitPoint->point + (hitPoint->normal * 0.01), separateLights[i].centre);
            HitPoint shadowHit = HitPoint(&lightDirection);
            shadowHit.intersected = false;
            intersectGeometry(&shadowHit);

            if (shadowHit.intersected && shadowHit.geo != geo){
                if ((shadowHit.point - hitPoint->point).norm()+0.100 < (separateLights[i].centre - hitPoint->point).norm()) {
                    shadowAttenuation = 0.1;
                    specularAttenuation = 0.0f;
                }
            }
            float diffuseCoefficient = fmax(0.0f, N.dot(L));

            diffuseSum = diffuseSum + (((diffuseCoefficient * separateLights[i].getDiffuseIntensity() * geo->getDiffuseColor())) *shadowAttenuation);

            float specularCoefficient = fmax(N.dot(H), 0.0f);

            specularCoefficient = pow(specularCoefficient, geo->getPhongCoefficient());

            specularSum = specularSum + (specularCoefficient * separateLights[i].getSpecularIntensity() * geo->getSpecularColor() * specularAttenuation);

        }

        diffuse = (diffuseSum*(1.0f/size)) + diffuse;
        specular = (specularSum*(1.0f/size)) + specular;

    }


    // ambient lighting
    RGBColor ambient = geo->getAmbientReflection() * geo->getAmbientColor() * currentOutput->ai;


    *color = ambient + diffuse + specular;

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

        Vector3f randomRay = randomPoint;
        randomRay.normalize();

        // checking if it is in the hemisphere
        if (randomRay.dot(hitPoint->normal) > 0) {
            return randomPoint;
        }
        else
            return -randomPoint;
    }
}

bool RayTracer::globalIllumination(Ray *ray, RGBColor *color) {

    HitPoint hitPoint = HitPoint(ray);

    RGBColor sumColor = RGBColor();

    int bounces = 0;

    Vector3f direction;

    Vector3f origin;

    Vector3f firstPoint;

    // looping until we reach the max number of bounces or the prob of termination
    for(int i = 0; i < currentOutput->maxBounces; i++){

        // random number
        static std::default_random_engine e;
        static std::uniform_real_distribution<> dis(0, 1);// range -1 - 1

        // check probability
        if (bounces >= 2 && float(dis(e)) > currentOutput->probTerminate) break;

        // intersecting with the geometries
        intersectGeometry(&hitPoint);

        // check if we intersected
        if (hitPoint.intersected){

            // keeping track of the bounces
            bounces++;

            float  attenuation = 0.4;

            sumColor = sumColor + hitPoint.geo->getDiffuseColor() * attenuation;

            Vector3f unitPoint = randomUnitPoint(&hitPoint);

            float hitPointX = hitPoint.point.x();
            float hitPointY = hitPoint.point.y();
            float hitPointZ = hitPoint.point.z();

            direction = Vector3f(hitPointX + float(unitPoint.x()), hitPointY + unitPoint.y(), hitPointZ + unitPoint.z());

            origin = Vector3f(hitPointX, hitPointY, hitPointZ);

            hitPoint.intersected = false;

            Ray newRay = Ray(origin, direction);

            hitPoint.ray = &newRay;

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
            Vector3f L = light->centre - hitPoint.point;
            L.normalize();

            if (inShadowGlobal(hitPoint.point, light->centre, hitPoint.normal)){
                sumColor = sumColor + RGBColor(0,0,0);
            }else {
                // diffuse coefficient
                float diffuseCoefficient = fmax(0.0f, hitPoint.normal.dot(L));

                sumColor = sumColor +
                           (diffuseCoefficient * light->getDiffuseIntensity() * hitPoint.geo->getDiffuseColor());
            }
        }

        // we go to the light(s)
        for (auto light: areaLights) {

            // light direction
            Vector3f L = light->areaCentre - hitPoint.point;
            L.normalize();

            if (inShadowGlobal(hitPoint.point, light->areaCentre, hitPoint.normal)){
                sumColor = sumColor + RGBColor(0,0,0);
            }else {
                // diffuse coefficient
                float diffuseCoefficient = fmax(0.0f, hitPoint.normal.dot(L));

                sumColor = sumColor +
                           (diffuseCoefficient * light->getDiffuseIntensity() * hitPoint.geo->getDiffuseColor());
            }

        }

        // sum up the colors and add the lighting
        *color = sumColor * (1.0f / float(bounces));

        return true;
    }



}

bool RayTracer::inShadow(Vector3f point, Vector3f lightPosition, Vector3f normal){

    Vector3f origin = point + normal * 0.01;

    Ray shadowRay = Ray(point, lightPosition);

    HitPoint shadowIntersection = HitPoint(&shadowRay);

    intersectGeometry(&shadowIntersection);

    if ( shadowIntersection.intersected && Geometry::vectorDistance(point, lightPosition)-0.001 <= Geometry::vectorDistance(shadowIntersection.point, lightPosition)) {
        return false;
    }

    return shadowIntersection.intersected;
}

bool RayTracer::inShadowGlobal(Vector3f point, Vector3f lightPosition, Vector3f normal){

    Vector3f origin = point + normal * 0.1;

    Ray shadowRay = Ray(origin, lightPosition);

    HitPoint shadowIntersection = HitPoint(&shadowRay);

    intersectGeometry(&shadowIntersection);

    if ( shadowIntersection.intersected && Geometry::vectorDistance(origin, lightPosition)-0.001 < Geometry::vectorDistance(origin, shadowIntersection.point)) {
        return false;
    }

    return shadowIntersection.intersected;
}

HitPoint* RayTracer::intersectSpheres(HitPoint *closest) {

    // checking intersection with spheres
    for(auto sphere: this->spheres){
        // finding the point of intersection
        Vector3f point = sphere->intersect(closest->ray);

        // if the object is the actual closest to the camera then we calculate the shading
        if(distanceTest(point, closest, &closest->ray->origin)) {

            closest->intersected = true;

            closest->point = point;

            closest->geo = sphere;

            // getting the normal of the point
            Vector3f normal = Vector3f(point - sphere->getCentre());
            normal.normalize();

            closest->normal = normal;

        };
    }

    return closest;

}

HitPoint* RayTracer::intersectRectangle(HitPoint *closest) {

    // checking intersection with rectangles
    for(auto rectangle: this->rectangles){

        Vector3f point = rectangle->intersect(closest->ray);

        if(distanceTest(point, closest, currentOutput->camera->getPosition())) {

            closest->intersected = true;

            closest->point = point;

            closest->geo = rectangle;

            Vector3f normal = Vector3f(Rectangle::getNormal(rectangle->getP1(),
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

    vector<double> buffer;

    // iterating over all the pixels
    for(int y = 0; y < height ; y++){
        for(int x = 0; x < width; x++){

            // default color
            RGBColor color = RGBColor(currentOutput->bgColor.getR(), currentOutput->bgColor.getG(), currentOutput->bgColor.getB());

            // total number of ray sample done
            int totalSamples = 0;

            // to sum the color
            RGBColor sumColor = RGBColor();

            if (currentOutput->globalIllum) {

                color = RGBColor(0.5,0.5,0.5);

                // iterating over the samples in the pixel
                for (int i = 0; i < currentOutput->raysPerPixel[0]; i++) {
                    for (int j = 0; j < currentOutput->raysPerPixel[1]; j++) {
                        for (int l = 0; l < currentOutput->raysPerPixel[2]; ++l) {

                            srand(time(0));
                            float randomNumX = float(rand())/RAND_MAX;
                            srand(randomNumX);
                            float randomNumY = float(rand())/RAND_MAX;

                            // generating a new ray
                            Ray ray = Ray(currentOutput->camera->generateRay(x, y, currentOutput->raysPerPixel[0], i+1, j+1, randomNumX, randomNumY));
                            if (globalIllumination(&ray, &color)) {
                                sumColor = sumColor + color;
                                totalSamples++;
                            }
                        }
                    }
                }

                if (totalSamples<=0)color = RGBColor(currentOutput->bgColor.getR(), currentOutput->bgColor.getG(), currentOutput->bgColor.getB());

            }
            else {

                if (currentOutput->anitAliasing){
                    // iterating over the samples in the pixel
                    for (int i = 0; i < currentOutput->n; i++) {
                        for (int j = 0; j < currentOutput->n; j++) {

                            for (int l = 0; l <currentOutput->n; ++l) {

                                srand(time(0));
                                float randomNumX = float(rand())/RAND_MAX;
                                srand(randomNumX);
                                float randomNumY = float(rand())/RAND_MAX;

                                // generating a new ray
                                Ray ray = currentOutput->camera->generateRay(x, y, currentOutput->n, i+1, j+1, randomNumX, randomNumY);

                                // this is the closest point to the camera for all intersection
                                HitPoint hitPoint = HitPoint(&ray);

                                intersectGeometry(&hitPoint);

                                if (hitPoint.intersected) {
                                    localIllumination(&hitPoint, &color);

                                    sumColor = sumColor + color;

                                    totalSamples++;

                                }
                            }
                        }
                    }

                } else {
                    // generating the ray
                    Ray ray = Ray(currentOutput->camera->generateRay(x, y));

                    // this is the closest point to the camera for all intersection
                    HitPoint hitPoint = HitPoint(&ray);

                    intersectGeometry(&hitPoint);

                    if (hitPoint.intersected) {

                        localIllumination(&hitPoint, &color);

                    }
                }
            }

            // averaging the color if there are many samples
            if (totalSamples > 1 )
                color = sumColor * (1.0f/float(totalSamples));

            buffer.push_back(color.getFinalR());
            buffer.push_back(color.getFinalG());
            buffer.push_back(color.getFinalB());

        }

    }

    save_ppm(currentOutput->filename,buffer, currentOutput->resolution.width, currentOutput->resolution.height);

}

