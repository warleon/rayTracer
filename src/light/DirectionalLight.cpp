#include "DirectionalLight.hpp"
DirectionalLight::DirectionalLight(const glm::vec3& intensity, const glm::vec3& direction)
    : Light(intensity), direction(glm::normalize(direction)) {}

glm::vec3 DirectionalLight::getIlluminationAt(const glm::vec3& point, const glm::vec3& normal) const {
    float diffuseFactor = glm::max(glm::dot(normal, -direction), 0.0f);  // Light coming from opposite direction
    return diffuseFactor * intensity;
}
