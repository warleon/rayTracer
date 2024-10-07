#pragma once
#include <glm/glm.hpp>
#include <Ray.hpp>

template <typename T>
class Grid;

template <typename T>
class GridCellIterator {
private:
    Grid<T>* grid;  // Pointer to the Grid being iterated over
    Ray ray;              // The ray used for traversal
    glm::ivec3 currentCell; // Current cell coordinates

public:
    GridCellIterator(Grid<T>* grid, const Ray& ray);
        

    // Initialize the iterator and find the starting cell
    void initialize();
    glm::ivec3 getNextCellAlongRay();

    GridCellIterator<T>& operator++();
    std::vector<T>& operator*();
    std::vector<T>* operator->();
    bool operator!=(const GridCellIterator<T>& other) const;
};
#include "GridCellIterator.ipp"
