#include "Mesh.hpp"

#include <cassert>
#include <limits>
Mesh::Mesh(material_t mat) : Object(material) {}
// void Mesh::setTriangles(std::vector<BareTriangle>&& newTriangles){
//     triangles = newTriangles;
//     initGrid();
// }

std::vector<std::shared_ptr<BareTriangle>>& Mesh::getTriangles() {
  return triangles;
}

void Mesh::initGrid() {
  glm::vec3 minCorner(std::numeric_limits<float>::max()),
      maxCorner(std::numeric_limits<float>::min()), diff;
  for (auto& triangle : triangles) {
    glm::vec3 minBox(std::numeric_limits<float>::max()),
        maxBox(std::numeric_limits<float>::min());
    for (const auto& vertex : triangle->getVertices()) {
      minCorner = glm::min(minCorner, vertex);
      maxCorner = glm::max(maxCorner, vertex);
      minBox = glm::min(minBox, vertex);
      maxBox = glm::max(maxBox, vertex);
    }
    diff = (diff + maxBox - minBox) / 2.0f;
  }
  glm::ivec3 res = (maxCorner - minCorner) / (diff);
  grid.reset(minCorner, maxCorner, res);
  for (auto& triangle : triangles) {
    addTriangleToGrid(triangle);
  }
}

void Mesh::addTriangleToGrid(std::shared_ptr<BareTriangle>& t) {
  glm::vec3 minBox(std::numeric_limits<float>::max()),
      maxBox(std::numeric_limits<float>::min());
  for (const auto& vertex : t->getVertices()) {
    minBox = glm::min(minBox, vertex);
    maxBox = glm::max(maxBox, vertex);
  }
  glm::ivec3 startIndex = grid.worldToGrid(minBox);
  glm::ivec3 endIndex = grid.worldToGrid(maxBox);

  // incorrect method
  for (int x = startIndex.x; x <= endIndex.x; ++x) {
    for (int y = startIndex.y; y <= endIndex.y; ++y) {
      for (int z = startIndex.z; z <= endIndex.z; ++z) {
        grid(glm::ivec3(x, y, z)).emplace_back(t);
      }
    }
  }
}

std::optional<float> Mesh::testRayHit(const Ray& ray) const {
  for (auto it = grid.begin(ray); it != grid.end(); it++) {
    for (const auto& triangle : *it) {
      auto t = triangle->testRayHit(ray);
      if (t) return t;
    }
  }
  return std::nullopt;
}

glm::vec3 Mesh::getNormalAt(const glm::vec3& point) const {
  glm::ivec3 index = grid.worldToGrid(point);
  for (const auto& triangle : grid(index)) {
    if (isPointInTriangle(point, *triangle))
      return triangle->getNormalAt(point);
  }
  return glm::vec3(0.0f);
}

bool Mesh::isPointInTriangle(const glm::vec3& point,
                             BareTriangle& triangle) const {
  const auto& vertices = triangle.getVertices();
  glm::vec3 v0 = (vertices[1]) - (vertices[0]);  // Edge AB
  glm::vec3 v1 = (vertices[2]) - (vertices[0]);  // Edge AC
  glm::vec3 v2 = point - (vertices[0]);          // Vector AP

  // Compute dot products
  float dot00 = glm::dot(v0, v0);
  float dot01 = glm::dot(v0, v1);
  float dot02 = glm::dot(v0, v2);
  float dot11 = glm::dot(v1, v1);
  float dot12 = glm::dot(v1, v2);

  // Compute barycentric coordinates
  float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
  float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
  float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

  // Check if point is in triangle
  return (u >= 0) && (v >= 0) && (u + v <= 1);
}