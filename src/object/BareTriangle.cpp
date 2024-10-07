#include "BareTriangle.hpp"
BareTriangle::BareTriangle(const glm::vec3& v0, const glm::vec3& v1,
                           const glm::vec3& v2) {
  normal =
      glm::normalize(glm::cross(v1 - v0, v2 - v0));  // Precompute the normal
  vertices = {v0, v1, v2};
}
std::array<glm::vec3, 3>& BareTriangle::getVertices() { return vertices; }

std::optional<float> BareTriangle::testRayHit(const Ray& ray) const {
  glm::vec3 origin = ray.getOrigin(), direction = ray.getDirection();

  // Calculate the edges of the triangle
  glm::vec3 edge1 = vertices[1] - vertices[0];
  glm::vec3 edge2 = vertices[2] - vertices[0];

  // Calculate the determinant
  glm::vec3 h = glm::cross(direction, edge2);
  float a = glm::dot(edge1, h);

  // If a is near zero, the ray is parallel to the triangle
  if (std::fabs(a) < 1e-8) {
    return std::nullopt;  // No intersection
  }

  float f = 1.0f / a;
  glm::vec3 s = origin - vertices[0];
  float u = f * glm::dot(s, h);

  // Check the u parameter
  if (u < 0.0f || u > 1.0f) {
    return std::nullopt;  // No intersection
  }

  glm::vec3 q = glm::cross(s, edge1);
  float v = f * glm::dot(direction, q);

  // Check the v parameter
  if (v < 0.0f || u + v > 1.0f) {
    return std::nullopt;  // No intersection
  }

  // Calculate the intersection point
  float t = f * glm::dot(edge2, q);

  // Return the distance to the intersection point if valid
  if (t > 1e-8) {
    return t;  // Intersection occurred
  } else {
    return std::nullopt;  // Intersection is behind the ray origin
  }
}

// Get the normal vector at any point on the triangle surface
glm::vec3 BareTriangle::getNormalAt(const glm::vec3& point) const {
  return normal;
}