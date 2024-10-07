#pragma once
#include <glm/glm.hpp>
#include <optional>
#include <cmath>
#include <array>

class BareTriangle {
    glm::vec3 vertex0; // First vertex of the triangle
    glm::vec3 vertex1; // Second vertex of the triangle
    glm::vec3 vertex2; // Third vertex of the triangle
    glm::vec3 normal; // normal of the triangle
public:
    BareTriangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);

    std::optional<float> testRayHit(const Ray& ray) const;

    glm::vec3 getNormalAt(const glm::vec3& point) const;

    std::array<glm::vec3*,3> vertices={&vertex0,&vertex1,&vertex2};
};
