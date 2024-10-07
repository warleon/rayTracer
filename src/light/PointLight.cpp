#include "PointLight.hpp"
PointLight::PointLight(const glm::vec3& intensity, const glm::vec3& position)
    : Light(intensity), position(position) {}

glm::vec3 PointLight::getIlluminationAt(const glm::vec3& point, const glm::vec3& normal) const {
    glm::vec3 lightDir = glm::normalize(position - point);  // Direction from point to light
    float diffuseFactor = glm::max(glm::dot(normal, lightDir), 0.0f);
    return diffuseFactor * intensity;  // Illumination based on diffuse lighting model
}
