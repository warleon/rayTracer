#include "AmbientLight.hpp"
AmbientLight::AmbientLight(const glm::vec3& intensity) : Light(intensity) {}

glm::vec3 AmbientLight::getIlluminationAt(const glm::vec3& point, const glm::vec3& normal) const {
    return intensity;  // Ambient light doesn't depend on position or normal, returns constant intensity
}