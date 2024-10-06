#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include "Triangle.hpp" // Include the Triangle class

class OBJLoader {
public:
    void load(const std::string& filename, const color_t& color, std::vector<Object*>& triangles);
};
