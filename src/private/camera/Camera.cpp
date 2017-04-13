#include "camera/Camera.h"

const vec3 Camera::DEFAULT_POSITION = vec3(0, 0, 1);
const vec3 Camera::DEFAULT_FOCAL_POINT = vec3(0, 0, 0);
const vec3 Camera::DEFAULT_UP = vec3(0, 1, 0);
const int Camera::DEFAULT_WIDTH = 720;
const int Camera::DEFAULT_HEIGHT = 480;
const float Camera::DEFAULT_FOVY = 90;

Camera::Camera() {
    lookAt(DEFAULT_POSITION, DEFAULT_FOCAL_POINT, DEFAULT_UP);
    setResolution(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setFovy(DEFAULT_FOVY);
}

Camera::Camera(const vec3 position, const vec3 focalPoint) {
    lookAt(position, focalPoint, DEFAULT_UP);
    setResolution(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setFovy(DEFAULT_FOVY);
}

Camera::Camera(const vec3 position, const vec3 focalPoint, const vec3 up) {
    lookAt(position, focalPoint, up);
    setResolution(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setFovy(DEFAULT_FOVY);
}

void Camera::lookAt(const vec3 position, const vec3 focalPoint) {
    setPosition(position);
    setFocalPoint(focalPoint);
    setUp(DEFAULT_UP);
}

void Camera::lookAt(const vec3 position, const vec3 focalPoint, const vec3 up) {
    setPosition(position);
    setFocalPoint(focalPoint);
    setUp(up);
}

void Camera::setPosition(const vec3 position) {
    this->position = position;
}

void Camera::setFocalPoint(const vec3 focalPoint) {
    this->focalPoint = focalPoint;
}

void Camera::setUp(const vec3 up) {
    this->up = up;
}

vec3 Camera::getPosition() const {
    return position;
}

vec3 Camera::getFocalPoint() const {
    return focalPoint;
}

vec3 Camera::getUp() const {
    return up;
}

void Camera::setResolution(const int width, const int height) {
    setWidth(width);
    setHeight(height);
}

void Camera::setWidth(const int width) {
    this->width = width;
}

void Camera::setHeight(const int height) {
    this->height = height;
}

void Camera::setFovy(const float fovy) {
    this->fovy = fovy;
}

Bitmap Camera::render(const Scene & scene) const {
    
    Bitmap bitmap(width, height);
    
    // Setup camera variables
    vec3 w = normalize(focalPoint - position);
    vec3 u = normalize(cross(w, up));
    vec3 v = cross(w, u);
    
    // Cached uniform variables
    float betaMult = -tan(glm::radians(fovy / 2));
    float alphaMult = betaMult * width / height;
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    
    // Iterate through all the rays
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            
            // Then calculate alpha and beta then direction of ray
            float alpha = alphaMult * (halfWidth - i + 0.5f) / halfWidth;
            float beta = betaMult * (j - halfHeight + 0.5f) / halfHeight;
            vec3 dir = normalize(alpha * u + beta * v + w);
            
            Ray ray = Ray(position, dir);
            
            // Set the related pixel color
            bitmap.setPixel(i, j, scene.getRayColor(ray));
        }
    }
    
    // Return the bitmap
    return bitmap;
}
