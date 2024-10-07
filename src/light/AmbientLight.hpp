#pragma once
#include "Light.hpp"
class AmbientLight : public Light {
public:
    AmbientLight(const glm::vec3& intensity);

    glm::vec3 getIlluminationAt(const glm::vec3& point, const glm::vec3& normal) const override;
};
