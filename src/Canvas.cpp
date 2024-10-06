#include "Canvas.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <iostream>
#include <stdexcept>

Canvas::Canvas(int width, int height) : width(width), height(height), rgbaMatrix(width * height * 4, 255) {
    // Initialize the matrix with default values (white and fully opaque)
}

void Canvas::setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Pixel coordinates out of bounds.");
    }
    
    int index = getIndex(x, y);
    rgbaMatrix[index]     = r; // Red
    rgbaMatrix[index + 1] = g; // Green
    rgbaMatrix[index + 2] = b; // Blue
    rgbaMatrix[index + 3] = a; // Alpha
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
