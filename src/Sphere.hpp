#pragma once
#include "Object.hpp"


class Sphere : public Object {
public:
    Sphere(const color_t& color, const glm::vec3& center, float radius);

    std::optional<float> testRayHit(const Ray& ray) const override;

private:
    glm::vec3 center; // Center of the sphere
    float radius;     // Radius of the sphere
};
