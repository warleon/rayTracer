#pragma once
#include <glm/glm.hpp>

class Light {
protected:
    glm::vec3 intensity;  // RGB intensity values for each color channel

public:
    Light(const glm::vec3& intensity) : intensity(intensity) {}

    // Abstract method to calculate the illumination at a given point with a given normal
    virtual glm::vec3 getIlluminationAt(const glm::vec3& point, const glm::vec3& normal) const = 0;

    virtual ~Light() = default;
};

