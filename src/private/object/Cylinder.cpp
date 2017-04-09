#include "object/Cylinder.h"

const float Cylinder::DEFAULT_HEIGHT = 1.0f;
const float Cylinder::DEFAULT_RADIUS = 0.5f;

bool Cylinder::higher(float h) {
    return h > height / 2;
}

bool Cylinder::lower(float h) {
    return h < -height / 2;
}

bool Cylinder::inHeight(float h) {
    return !higher(h) && !lower(h);
}

bool Cylinder::updateIntersect(Ray & ray, Intersection & intersection) {
    
    // Prepare the basic parameters
    int axis = getAxis();
    float halfHeight = height / 2;
    vec3 p0 = ray.getOrigin();
    vec3 p1 = ray.getDirection();
    p0[axis] = 0;
    p1[axis] = 0;
    
    // Calculate t
    float t;
    bool hit = false;
    float a = dot(p1, p1);
    float b = 2.0f * dot(p1, p0);
    float c = dot(p0, p0) - radius * radius;
    float t1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
    float t2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
    
    if (t1 > 0 && t2 > 0) {
        
        if (t1 > t2) swap(t1, t2);
        
        vec3 pos1 = ray.getOrigin() + t1 * ray.getDirection();
        vec3 pos2 = ray.getOrigin() + t2 * ray.getDirection();
        
        vec3 pos;
        vec3 normal;
        
        // Check which surface is the ray intersecting
        if (inHeight(pos1[axis])) {
            
            // Intersecting the side
            t = t1;
            pos = pos1;
            normal = pos1;
            normal[axis] = 0;
        }
        else if (higher(pos1[axis]) && !higher(pos2[axis])) {
            
            // Intersecting the top side
            float dist = pos1[axis] - halfHeight;
            t = dist / -ray.getDirection()[axis];
            pos = ray.getOrigin() + t * ray.getDirection();
            normal = NORMALS[axis * 2];
        }
        else if (lower(pos1[axis]) && !lower(pos2[axis])) {
            
            // Intersecting the bottom side
            float dist = pos1[axis] - halfHeight;
            t = dist / -ray.getDirection()[axis];
            pos = ray.getOrigin() + t * ray.getDirection();
            normal = NORMALS[axis * 2 + 1];
        }
        else {
            
            // No Intersection
            return false;
        }
        
        if (intersection.needUpdate(t)) {
            
            // Set the intersection
            intersection.setHit(true);
            intersection.setT(t);
            intersection.setPosition(pos);
            intersection.setNormal(normal);
            return true;
        }
        
        // Not updating intersection, return false
        return false;
    }
    else if (t1 * t2 < 0) {
        
        //
        t = max(t1, t2);
        vec3 pos = ray.getOrigin() + t * ray.getDirection();
        
        //
        if (inHeight(pos[axis]) && intersection.needUpdate(t)) {
            
            // Set the intersection
            intersection.setHit(true);
            intersection.setT(t);
            intersection.setPosition(pos);
            pos[axis] = 0;
            intersection.setNormal(pos);
            
            return true;
        }
        else {
            return false;
        }
    }
    
    return false;
}

Cylinder::Cylinder() : Object(), Orientable() {
    setHeight(DEFAULT_HEIGHT);
    setRadius(DEFAULT_RADIUS);
}

Cylinder::Cylinder(float height, float radius) : Object(), Orientable() {
    setHeight(height);
    setRadius(radius);
}

Cylinder::Cylinder(int orientation) : Object(), Orientable(orientation) {
    setHeight(DEFAULT_HEIGHT);
    setRadius(DEFAULT_RADIUS);
}

Cylinder::Cylinder(int orientation, float height, float radius) : Object(), Orientable(orientation) {
    setHeight(height);
    setRadius(radius);
}

float Cylinder::getHeight() {
    return height;
}

void Cylinder::setHeight(float height) {
    this->height = height;
}

float Cylinder::getRadius() {
    return radius;
}

void Cylinder::setRadius(float radius) {
    this->radius = radius;
}
