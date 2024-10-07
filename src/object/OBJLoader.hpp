#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include "Mesh.hpp"

class OBJLoader {
public:
    void load(const std::string& filename, Mesh& mesh);
};
