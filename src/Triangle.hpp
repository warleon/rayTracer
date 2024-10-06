#pragma once
#include <glm/glm.hpp>
#include <optional>
#include <cmath>
#include "Object.hpp"

class Triangle : public Object {
public:
    Triangle(const color_t& color,const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);

    std::optional<float> testRayHit(const Ray& ray) const override;
private:
    glm::vec3 vertex0; // First vertex of the triangle
    glm::vec3 vertex1; // Second vertex of the triangle
    glm::vec3 vertex2; // Third vertex of the triangle
};
