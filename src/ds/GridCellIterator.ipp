#include <cassert>

#include "GridCellIterator.hpp"
template <typename T>
GridCellIterator<T>::GridCellIterator(Grid<T>* grid, const Ray& ray)
    : grid(grid), ray(ray), currentCell(0) {
  initialize();
}

// Initialize the iterator and find the starting cell
template <typename T>
void GridCellIterator<T>::initialize() {
  if (!grid) return;

  std::optional<float> intersection = grid->testRayHit(ray);
  if (intersection) {
    currentCell = grid->worldToGrid(ray.getOrigin() +
                                    intersection.value() * ray.getDirection());
  } else {
    // If the ray does not intersect the grid, set to the end state
    grid = nullptr;
  }
}

template <typename T>
glm::ivec3 GridCellIterator<T>::getNextCellAlongRay() {
  // Initialize variables for ray traversal along the grid
  glm::vec3 origin = ray.getOrigin();
  glm::vec3 rayDirection = ray.getDirection();
  glm::vec3 cellSize = grid->getCellSize();  // Assuming you have a method that
                                             // gives the grid cell size
  glm::ivec3 nextCell = currentCell;

  // Compute the parametric t values at which the ray crosses the next cell
  // boundary
  glm::vec3 tMax /*, tDelta*/;

  for (int i = 0; i < 3; i++) {
    // Calculate the step direction for each axis
    if (rayDirection[i] > 0) {
      tMax[i] = ((nextCell[i] + 1) * cellSize[i] - origin[i]) / rayDirection[i];
      // tDelta[i] = cellSize[i] / rayDirection[i];
    } else if (rayDirection[i] < 0) {
      tMax[i] = (nextCell[i] * cellSize[i] - origin[i]) / rayDirection[i];
      // tDelta[i] = cellSize[i] / -rayDirection[i];
    } else {
      tMax[i] =
          std::numeric_limits<float>::max();  // Ray is parallel to this axis
      // tDelta[i] = std::numeric_limits<float>::max();
    }
  }

  // Move to the next cell along the axis where tMax is smallest
  if (tMax.x < tMax.y && tMax.x < tMax.z) {
    nextCell.x += (rayDirection.x > 0) ? 1 : -1;
  } else if (tMax.y < tMax.z) {
    nextCell.y += (rayDirection.y > 0) ? 1 : -1;
  } else {
    nextCell.z += (rayDirection.z > 0) ? 1 : -1;
  }

  return nextCell;
}

// Increment to the next cell based on the ray's direction
template <typename T>
GridCellIterator<T>& GridCellIterator<T>::operator++(int) {
  if (!grid) return *this;
  auto next = getNextCellAlongRay();
  if (grid->isInside(next))
    currentCell = next;
  else {
    grid = nullptr;
    currentCell = glm::ivec3(0);
  }
  return *this;
}

template <typename T>
std::vector<T>& GridCellIterator<T>::operator*() {
  assert(grid);
  return grid->operator()(currentCell.x, currentCell.y, currentCell.z);
}

template <typename T>
std::vector<T>* GridCellIterator<T>::operator->() {
  assert(grid);
  return &(grid->operator()(currentCell.x, currentCell.y, currentCell.z));
}

// Comparison operators for iterator (used in range-based loops)
template <typename T>
bool GridCellIterator<T>::operator!=(const GridCellIterator<T>& other) const {
  return grid != other.grid || currentCell != other.currentCell;
}