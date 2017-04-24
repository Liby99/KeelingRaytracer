#include "util/BoundingBox.h"
#include "object/Object.h"

BoundingBox::BoundingBox() {
    initiated = false;
}

BoundingBox::BoundingBox(vec3 minCorner, vec3 maxCorner) {
    setMinCorner(minCorner);
    setMaxCorner(maxCorner);
    initiated = true;
}

BoundingBox::BoundingBox(Object * obj) {
    extend(*obj);
}

float BoundingBox::getWidth() {
    return maxCorner.x - minCorner.x;
}

float BoundingBox::getHeight() {
    return maxCorner.y - minCorner.y;
}

float BoundingBox::getLength() {
    return maxCorner.z - minCorner.z;
}

vec3 BoundingBox::getSize() {
    return vec3(getWidth(), getHeight(), getLength());
}

vec3 BoundingBox::getMinCorner() {
    return minCorner;
}

vec3 BoundingBox::getMaxCorner() {
    return maxCorner;
}

vector<vec3> BoundingBox::getBoundingVertices() {
    vector<vec3> vertices;
    vertices.push_back(vec3(minCorner.x, minCorner.y, minCorner.z));
    vertices.push_back(vec3(minCorner.x, minCorner.y, maxCorner.z));
    vertices.push_back(vec3(minCorner.x, maxCorner.y, minCorner.z));
    vertices.push_back(vec3(minCorner.x, maxCorner.y, maxCorner.z));
    vertices.push_back(vec3(maxCorner.x, minCorner.y, minCorner.z));
    vertices.push_back(vec3(maxCorner.x, minCorner.y, maxCorner.z));
    vertices.push_back(vec3(maxCorner.x, maxCorner.y, minCorner.z));
    vertices.push_back(vec3(maxCorner.x, maxCorner.y, maxCorner.z));
    return vertices;
}

void BoundingBox::setMinCorner(vec3 minCorner) {
    this->minCorner = minCorner;
}

void BoundingBox::setMaxCorner(vec3 maxCorner) {
    this->maxCorner = maxCorner;
}

void BoundingBox::extend(Object & object) {
    extend(object.getBoundingBox());
}

void BoundingBox::extend(BoundingBox box) {
    setMinCorner(initiated ? minVec(minCorner, box.minCorner) : box.minCorner);
    setMaxCorner(initiated ? maxVec(maxCorner, box.maxCorner) : box.maxCorner);
    initiated = true;
}

bool BoundingBox::intersect(vec3 vec) {
    return vec.x > minCorner.x && vec.y > minCorner.y && vec.z > minCorner.z &&
           vec.x < maxCorner.x && vec.y < maxCorner.y && vec.z < maxCorner.z;
}

bool BoundingBox::intersect(Ray & ray) {
    float t = 0;
    return intersect(ray, t);
}

bool BoundingBox::intersect(Ray & ray, float & t) {
    float t1[3], t2[3], tmin, tmax;
    for (int i = 0; i < 3; ++i) {
        t1[i] = ((minCorner[i] - ray.getOrigin()[i]) / ray.getDirection()[i]);
        t2[i] = ((maxCorner[i] - ray.getOrigin()[i]) / ray.getDirection()[i]);
    }
    tmin = max(min(t1[0], t2[0]), min(t1[1], t2[1]), min(t1[2], t2[2]));
    tmax = min(max(t1[0], t2[0]), max(t1[1], t2[1]), max(t1[2], t2[2]));
    if (tmin <= tmax) {
        t = tmin;
        return true;
    }
    return false;
}

bool BoundingBox::intersect(Object & object) {
    return intersect(object.getBoundingBox());
}

bool BoundingBox::intersect(BoundingBox box) {
    vec3 nmin = maxVec(minCorner, box.minCorner);
    vec3 nmax = minVec(maxCorner, box.maxCorner);
    vec3 diagnal = nmax - nmin;
    return diagnal.x > 0 && diagnal.y > 0 && diagnal.z > 0;
}

void BoundingBox::combine(BoundingBox & box) {
    setMinCorner(minVec(minCorner, box.minCorner));
    setMaxCorner(maxVec(maxCorner, box.maxCorner));
}

BoundingBox BoundingBox::combine(BoundingBox & b1, BoundingBox & b2) {
    return BoundingBox(minVec(b1.minCorner, b2.minCorner),
                       maxVec(b1.maxCorner, b2.maxCorner));
}
