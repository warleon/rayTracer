#pragma once
#include <vector>
#include "BareTriangle.hpp"
#include "Object.hpp"
#include <ds/Grid.hpp>

class Mesh: public Object {

    std::vector<BareTriangle> triangles;
    Grid<BareTriangle*> grid;

public:
    Mesh(material_t mat);
    void setTriangles(std::vector<BareTriangle>&& newTriangles);
    std::vector<BareTriangle>& getTriangles();
    void initGrid();

    std::optional<float> testRayHit(const Ray& ray) const override;

    glm::vec3 getNormalAt(const glm::vec3& point) const override;
    bool isPointInTriangle(const glm::vec3& point, const BareTriangle& triangle);
};