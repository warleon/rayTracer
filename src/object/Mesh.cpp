#include "Mesh.hpp"
#include <limits>
Mesh::Mesh(material_t mat):Object(material){}
void Mesh::setTriangles(std::vector<BareTriangle>&& newTriangles){
    triangles = newTriangles;
    initGrid();
}

std::vector<BareTriangle>& Mesh::getTriangles(){
    return triangles;
}

Mesh::initGrid(){
    glm::vec3 minCorner(std::numeric_limits<float>::max()),maxCorner(std::numeric_limits<float>::min()),maxDiff(0);
    for(const auto& tirangle : triangles){
        glm::vec3 minBox(std::numeric_limits<float>::max()),maxBox(std::numeric_limits<float>::min());
        for(const auto& vertex : triangle.vertices){
            minCorner = glm::min(minCorner,*vertex)
            maxCorner = glm::max(maxCorner,*vertex)
            minBox = glm::min(minBox,*vertex)
            maxBox = glm::max(maxBox,*vertex)
        }
        maxDiff = glm::max(maxDiff,maxBox - minBox)
    }
    glm::ivec3 res = (maxCorner-minCorner)/(maxDiff*1.2f);
    grid.setMinCorner(minCorner);
    grid.setMaxCorner(maxCorner);
    grid.setResolution(res)
    for(size_t i=0;i<triangles.size();i++){
        addTriangleToGrid(i);
    }
}

Mesh::addTriangleToGrid(size_t t){
    glm::vec3 minBox(std::numeric_limits<float>::max()),maxBox(std::numeric_limits<float>::min());
    for(const auto& vertex : triangles[t].vertices){
        minBox = glm::min(minBox,*vertex)
        maxBox = glm::max(maxBox,*vertex)
    }
    glm::ivec3 minIndex = grid.worldToGrid(minBox);
    glm::ivec3 maxIndex = grid.worldToGrid(maxBox);

    //incorrect method
    for (int x = startIndex.x; x <= endIndex.x; ++x) {
        for (int y = startIndex.y; y <= endIndex.y; ++y) {
            for (int z = startIndex.z; z <= endIndex.z; ++z) {
                grid[glm::ivec3(x, y, z)].push_back(&triangles[t]);
            }
        }
    }

}

std::optional<float> Mesh::testRayHit(const Ray& ray) const {
    for(auto it = grid.begin(ray);it!=grid.end();it++){
        for(const auto& triangle:*it){
            auto t = triangle->testRayHit(ray);
            if(t)return t;
        }
    }
    return std::nullopt;
}

glm::vec3 Mesh::getNormalAt(const glm::vec3& point) const {
    glm::ivec3 index = grid.worldToGrid(point);
    for(const auto& triangle:grid[index]){
        if(isPointInTriangle(point,*triangle))
            return triangle->getNormalAt(point);
    }
    return glm::vec3(0.0f);
}

bool Mesh::isPointInTriangle(const glm::vec3& point, const BareTriangle& triangle) {
    glm::vec3 v0 = (*triangle.vertices[1]) - (*triangle.vertices[0]); // Edge AB
    glm::vec3 v1 = (*triangle.vertices[2]) - (*triangle.vertices[0]); // Edge AC
    glm::vec3 v2 = point - (*triangle.vertices[0]);     // Vector AP

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