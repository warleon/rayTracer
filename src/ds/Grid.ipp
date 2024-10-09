#include <algorithm>
#include <cassert>
#include <iostream>

#include "Grid.hpp"
template <typename T>
Grid<T>::Grid(const glm::vec3& minCorner, const glm::vec3& maxCorner,
              const glm::ivec3& resolution)
    : minCorner(minCorner), maxCorner(maxCorner), resolution(resolution) {
  data.resize(resolution.x,
              std::vector<std::vector<bucket_t>>(
                  resolution.y, std::vector<bucket_t>(resolution.z)));
}

template <typename T>
Grid<T>::Grid() : minCorner(0.0f), maxCorner(0.0f), resolution(0) {}

// Getters
template <typename T>
glm::vec3 Grid<T>::getMinCorner() const {
  return minCorner;
}
template <typename T>
glm::vec3 Grid<T>::getMaxCorner() const {
  return maxCorner;
}
template <typename T>
glm::ivec3 Grid<T>::getResolution() const {
  return resolution;
}

// Setters
template <typename T>
void Grid<T>::setMinCorner(const glm::vec3& corner) {
  minCorner = corner;
}
template <typename T>
void Grid<T>::setMaxCorner(const glm::vec3& corner) {
  maxCorner = corner;
}
template <typename T>
void Grid<T>::setResolution(const glm::ivec3& res) {
  resolution = res;
}

template <typename T>
inline void Grid<T>::reset(const glm::vec3& min, const glm::vec3& max,
                           const glm::ivec3& res) {
  setMinCorner(min);
  setMaxCorner(max);
  setResolution(res);

  data.resize(resolution.x,
              std::vector<std::vector<bucket_t>>(
                  resolution.y, std::vector<bucket_t>(resolution.z)));
}

// Function to convert a point in world space to grid coordinates
template <typename T>
glm::ivec3 Grid<T>::worldToGrid(const glm::vec3& point) const {
  glm::vec3 relPoint = (point - minCorner) / (maxCorner - minCorner);
  return glm::clamp(glm::ivec3(relPoint * glm::vec3(resolution)), glm::ivec3(0),
                    resolution - 1);
}

// Function to convert grid coordinates back to world space
template <typename T>
glm::vec3 Grid<T>::gridToWorld(const glm::ivec3& gridPos) const {
  glm::vec3 gridRel = glm::vec3(gridPos) / glm::vec3(resolution);
  return minCorner + gridRel * (maxCorner - minCorner);
}

// Get the size of a grid cell
template <typename T>
glm::vec3 Grid<T>::getCellSize() const {
  return (maxCorner - minCorner) / glm::vec3(resolution);
}

// Function to access grid cell data by 3D grid position
template <typename T>
typename Grid<T>::bucket_t& Grid<T>::operator()(const glm::vec3& point) {
  glm::ivec3 index = worldToGrid(point);
  return this->operator()(index.x, index.y, index.z);
}

template <typename T>
typename Grid<T>::bucket_t& Grid<T>::operator()(int x, int y, int z) {
  return data[x][y][z];
}

// Function to access grid cell data by 3D grid position
template <typename T>
const typename Grid<T>::bucket_t& Grid<T>::operator()(
    const glm::vec3& point) const {
  return this->operator()(worldToGrid(point));
}

template <typename T>
const typename Grid<T>::bucket_t& Grid<T>::operator()(int x, int y,
                                                      int z) const {
  return data[x][y][z];
}

// Begin iterator (initialize with ray and grid)
template <typename T>
GridCellIterator<T> Grid<T>::begin(const Ray& ray) const {
  Grid<T>* g = const_cast<Grid<T>*>(this);
  return GridCellIterator<T>(g, ray);
}

// End iterator (use default or null state to mark the end)
template <typename T>
GridCellIterator<T> Grid<T>::end() const {
  return GridCellIterator<T>(nullptr, Ray());  // null pointer or empty iterator
}

template <typename T>
bool Grid<T>::isInside(const glm::ivec3& cell) const {
  return cell.x >= 0 && cell.x < resolution.x && cell.y >= 0 &&
         cell.y < resolution.y && cell.z >= 0 && cell.z < resolution.z;
}

template <typename T>
std::optional<float> Grid<T>::testRayHit(const Ray& ray) {
  auto origin = ray.getOrigin(), direction = ray.getDirection();
  // Initialize tMin and tMax with extreme values
  float tMin = (minCorner.x - origin.x) / direction.x;
  float tMax = (maxCorner.x - origin.x) / direction.x;

  // Ensure tMin is less than tMax
  if (tMin > tMax) std::swap(tMin, tMax);

  // For each axis (Y and Z), find the intersection values and update tMin and
  // tMax
  for (int i = 1; i < 3; i++) {
    float t1 = (minCorner[i] - origin[i]) / direction[i];
    float t2 = (maxCorner[i] - origin[i]) / direction[i];

    if (t1 > t2) std::swap(t1, t2);

    // Update tMin and tMax
    tMin = std::max(tMin, t1);
    tMax = std::min(tMax, t2);

    // If tMin is greater than tMax, there is no intersection
    if (tMin > tMax) return std::nullopt;
  }

  // If tMax is negative, the box is behind the ray, no intersection
  if (tMax < 0) return std::nullopt;

  // Return tMin (entry point) or tMax (exit point), depending on which is
  // positive
  return tMin > 0 ? std::optional<float>(tMin) : std::optional<float>(tMax);
}