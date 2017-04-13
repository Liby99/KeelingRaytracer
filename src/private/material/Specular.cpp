#include "material/Specular.h"
#include "scene/Scene.h"

const Color Specular::DEFAULT_SPECULAR = Color(1, 1, 1);
const float Specular::DEFAULT_SHININESS = 20;

Color Specular::getShadingColor(const Scene & scene, const Intersection & intersection) const {
    Color color;
    #pragma omp parallel for
    for (int i = 0; i < scene.lightAmount(); i++) {
        
        // Store the temporary light
        Light & light = scene.getLight(i);
        
        // Get the brightness
        float brightness = light.getBrightness(scene, intersection);
        if (brightness == 0) {
            continue;
        }
        
        // Then calculate the color
        Color lc = light.getColor() * brightness;
        vec3 halfAngle = normalize(light.getToLightDirection(intersection) - intersection.getRay().getDirection());
        Color blinn = specular * pow(max(dot(intersection.getNormal(), halfAngle), 0.0f), shininess);
        color += lc * blinn;
    }
    return color;
}

Specular::Specular() : Material() {
    setSpecular(DEFAULT_SPECULAR);
    setShininess(DEFAULT_SHININESS);
}

Specular::Specular(const Color specular) : Material() {
    setSpecular(specular);
    setShininess(DEFAULT_SHININESS);
}

Specular::Specular(const Color specular, const float shininess) : Material() {
    setSpecular(specular);
    setShininess(shininess);
}

Color Specular::getSpecular() const {
    return specular;
}

void Specular::setSpecular(const Color specular) {
    this->specular = specular;
}

float Specular::getShininess() const {
    return shininess;
}

void Specular::setShininess(const float shininess) {
    this->shininess = shininess;
}
