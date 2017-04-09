#include "object/Plane.h"

bool Plane::updateIntersect(Ray & ray, Intersection & intersection) {
    
    // If the direction is parallel to the plane, then return false
    if (ray.getDirection()[getAxis()] == 0) {
        return false;
    }
    
    // Else
    float dist = ray.getOrigin()[getAxis()];
    float t = dist / -ray.getDirection()[getAxis()];
    
    if (t >= 0) {
        return intersection.update(t, ray.getOrigin() + t * ray.getDirection(), NORMALS[orientation]);
    }
    else {
        return false;
    }
}

Plane::Plane() : Object(), Orientable() {
    // Do nothing
}

Plane::Plane(int orientation) : Object(), Orientable(orientation) {
    // Do nothing
}