#include "Canvas.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <iostream>
#include <stdexcept>

Canvas::Canvas(int width, int height) : width(width), height(height), rgbaMatrix(width * height * 4, 255) {
    // Initialize the matrix with default values (white and fully opaque)
}

void Canvas::setPixel(int x, int y,color_t pixel) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Pixel coordinates out of bounds.");
    }
    
    int index = getIndex(x, y);
    rgbaMatrix[index]     = pixel.r; // Red
    rgbaMatrix[index + 1] = pixel.g; // Green
    rgbaMatrix[index + 2] = pixel.b; // Blue
    rgbaMatrix[index + 3] = pixel.a; // Alpha
}

void Canvas::exportImage(const std::string& fileName) const {
    if (stbi_write_png(fileName.c_str(), width, height, 4, rgbaMatrix.data(), width * 4)) {
        std::cout << "Image saved successfully to " << fileName << std::endl;
    } else {
        std::cerr << "Failed to save the image!" << std::endl;
    }
}

int Canvas::getIndex(int x, int y) const {
    return (y * width + x) * 4; // Each pixel has 4 components (RGBA)
}

glm::vec2 Canvas::getNormalizedCoordinates(int x, int y) const {
        // Transform pixel coordinates to normalized coordinates
        float hw = (width / 2.0f),hh=(height / 2.0f);
        float normalizedX = (x - hw) / hw;
        float normalizedY = (hh - y) / hh;
        return glm::vec2(normalizedX, normalizedY);
    }