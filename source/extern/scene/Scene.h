#ifndef SCENE_H
#define SCENE_H

#include "util/Color.h"
#include "util/Ray.h"
#include "util/Intersection.h"
#include "object/Object.h"
#include "material/Material.h"
#include "light/Light.h"

class Scene {
protected:
    
    // Global Variables
    Color background;
    Engine * engine;
    vector<Object *> objects;
    vector<Light *> lights;
    
public:
    
    // Constructor and Destructors
    Scene();
    
    Engine & getEngine();
    void setEngine(Engine & engine);
    
    // Background
    Color getBackgroundColor();
    void setBackgroundColor(Color color);
    
    // Light related getter and setter
    unsigned int lightAmount();
    Light & getLight(int i);
    void addLight(Light & light);
    
    // Object related getter and setter
    unsigned int objectAmount();
    Object & getObject(int i);
    void addObject(Object & object);
    
    // Intersection
    bool getIntersection(Ray & ray, Intersection & intersection);
    Color getIntersectionColor(Intersection & intersection);
    Color getRayColor(Ray & ray);
};

#endif