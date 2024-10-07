#pragma once
#include <ds/Grid.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "BareTriangle.hpp"
#include "Object.hpp"

class Mesh : public Object {
  std::vector<std::shared_ptr<BareTriangle>> triangles;
  Grid<std::shared_ptr<BareTriangle>> grid;

 public:
  Mesh(material_t mat);
  ~Mesh() { std::cout << "DELETING MESH" << std::endl; }
  // void setTriangles(std::vector<BareTriangle>&& newTriangles);
  std::vector<std::shared_ptr<BareTriangle>>& getTriangles();
  void initGrid();

  std::optional<float> testRayHit(const Ray& ray) const override;

  glm::vec3 getNormalAt(const glm::vec3& point) const override;
  bool isPointInTriangle(const glm::vec3& point, BareTriangle& triangle) const;
  void addTriangleToGrid(std::shared_ptr<BareTriangle>& t);
};