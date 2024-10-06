#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Color.hpp"


class Canvas {
public:
    // Constructor to initialize the canvas with a given width and height
    Canvas(int width, int height);

    // Function to update a pixel at (x, y) with an RGBA value
    void setPixel(int x, int y, color_t color);

    // Function to export the canvas as an image file
    void exportImage(const std::string& fileName) const;

    // Getters for width and height
    int getWidth() const { return width; }
    int getHeight() const { return height; }

   glm::vec2 getNormalizedCoordinates(int x, int y) const;

private:
    int width;
    int height;
    std::vector<unsigned char> rgbaMatrix; // RGBA matrix storage

    // Helper function to get the index in the matrix for a given (x, y) coordinate
    int getIndex(int x, int y) const;
};
