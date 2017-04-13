#ifndef OBJECT_H
#define OBJECT_H

#include "util/Transform.h"
#include "util/Ray.h"
#include "util/Intersection.h"
#include "material/Material.h"

#include <vector>

class Object {
protected:
    
    const static vec3 DEFAULT_POSITION;
    const static vec3 DEFAULT_SCALER;
    const static vec3 DEFAULT_ROTATION;
    
    // Materials
    vector<Material *> materials;
    
    // Transform properties
    vec3 position;
    vec3 scaler;
    vec3 rotation;
    
    virtual bool updateIntersect(const Ray & ray, Intersection & intersection) const;
    
public:
    
    // Constructor
    Object();
    
    // Material Related
    int materialAmount() const;
    Material & getMaterial(int i) const;
    void addMaterial(Material & material);
    
    // Basic Getter
    vec3 getRotation() const;
    vec3 getScale() const;
    vec3 getPosition() const;
    
    // Rotate Transformation
    void setRotate(const vec3 rotation);
    void rotate(const vec3 rotation);
    void rotateX(const float degX);
    void rotateY(const float degY);
    void rotateZ(const float degZ);
    
    // Translate Transformation
    void setTranslate(const vec3 rotation);
    void translate(const vec3 position);
    void translateX(const float x);
    void translateY(const float y);
    void translateZ(const float z);
    
    // Scale Transformation
    void setScale(const vec3 scaler);
    void scale(const vec3 scaler);
    void scaleX(const float scaleX);
    void scaleY(const float scaleY);
    void scaleZ(const float scaleZ);
    
    // Get transformation helper method
    mat4 getTransformMatrix() const;
    
    // Virtaul intersect method
    bool intersect(const Ray & ray, Intersection & intersection) const;
};

#endif
