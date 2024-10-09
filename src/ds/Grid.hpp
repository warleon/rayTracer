#pragma once

#include <glm/glm.hpp>
#include <optional>
#include <vector>

#include "GridCellIterator.hpp"

template <typename T>
class Grid {
  typedef std::vector<T> bucket_t;
  glm::vec3 minCorner, maxCorner;  // Grid corners (world space)
  glm::ivec3 resolution;           // Resolution in x, y, z (number of cells)
  std::vector<std::vector<std::vector<bucket_t>>>
      data;  // 1D array storing grid cell data

  // Setters
  void setMinCorner(const glm::vec3& corner);
  void setMaxCorner(const glm::vec3& corner);
  void setResolution(const glm::ivec3& res);

 public:
  Grid(const glm::vec3& minCorner, const glm::vec3& maxCorner,
       const glm::ivec3& resolution);
  Grid();

  // Getters
  glm::vec3 getMinCorner() const;
  glm::vec3 getMaxCorner() const;
  glm::ivec3 getResolution() const;

  void reset(const glm::vec3& min, const glm::vec3& max, const glm::ivec3& res);

  // Function to convert a point in world space to grid coordinates
  glm::ivec3 worldToGrid(const glm::vec3& point) const;

  // Function to convert grid coordinates back to world space
  glm::vec3 gridToWorld(const glm::ivec3& gridPos) const;

  // Get the size of a grid cell
  glm::vec3 getCellSize() const;

  // Function to access grid cell data by 3D grid position
  bucket_t& operator()(int x, int y, int z);
  bucket_t& operator()(const glm::vec3& point);
  const bucket_t& operator()(int x, int y, int z) const;
  const bucket_t& operator()(const glm::vec3& point) const;

  // Begin iterator (initialize with ray and grid)
  GridCellIterator<T> begin(const Ray& ray) const;

  // End iterator (use default or null state to mark the end)
  GridCellIterator<T> end() const;

  bool isInside(const glm::ivec3& cell) const;

  std::optional<float> testRayHit(const Ray& ray);
};

#include "Grid.ipp"