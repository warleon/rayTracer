#include "OBJLoader.hpp"

#include <utility>

#include "BareTriangle.hpp"
void OBJLoader::load(const std::string& filename, Mesh* mesh) {
  std::vector<glm::vec3> vertices;
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open the file " << filename << std::endl;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;

    // Parse vertex data
    if (prefix == "v") {
      glm::vec3 vertex;
      iss >> vertex.x >> vertex.y >> vertex.z;
      vertices.push_back(vertex);
    }
    // Parse face data
    else if (prefix == "f") {
      std::vector<glm::vec3> faceVertices;
      int index;
      while (iss >> index) {
        // OBJ indices are 1-based; convert to 0-based
        faceVertices.push_back(vertices[index - 1]);
      }

      // Create triangles from the face vertices
      if (faceVertices.size() >= 3) {
        for (size_t i = 1; i < faceVertices.size() - 1; ++i) {
          mesh->getTriangles().emplace_back(std::make_shared<BareTriangle>(
              faceVertices[0], faceVertices[i], faceVertices[i + 1]));
        }
      }
    }
  }
  mesh->initGrid();
}