#include "object/InstanceObject.h"

bool InstanceObject::updateIntersect(Ray & ray, Intersection & intersection) {
    return object->intersect(ray, intersection);
}

InstanceObject::InstanceObject(Object & object) : Object() {
    setObject(object);
}

Object & InstanceObject::getObject() {
    return *object;
}

void InstanceObject::setObject(Object & object) {
    this->object = &object;
}