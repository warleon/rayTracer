#pragma once
#include "Light.hpp"

class DirectionalLight : public Light {
private:
    glm::vec3 direction;  // Direction of the light (normalized vector)

public:
    DirectionalLight(const glm::vec3& intensity, const glm::vec3& direction);

    glm::vec3 getIlluminationAt(const glm::vec3& point, const glm::vec3& normal) const;
};
