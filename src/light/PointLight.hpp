#pragma once
#include "Light.hpp"
class PointLight : public Light {
private:
    glm::vec3 position;  // Position of the point light in space

public:
    PointLight(const glm::vec3& intensity, const glm::vec3& position);

    glm::vec3 getIlluminationAt(const glm::vec3& point, const glm::vec3& normal) const override;
};
