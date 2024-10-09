#pragma once
#include <Ray.hpp>
#include <array>
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>
#include <optional>

class BareTriangle {
  std::array<glm::vec3, 3> vertices;
  glm::vec3 normal;  // normal of the triangle
 public:
  BareTriangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);
  // BareTriangle(const BareTriangle& triangle);
  ~BareTriangle() {}

  std::optional<float> testRayHit(const Ray& ray) const;

  glm::vec3 getNormalAt(const glm::vec3& point) const;

  std::array<glm::vec3, 3>& getVertices();
};
