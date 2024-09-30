#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <vector>
#include <iostream>

void export_rgba_matrix_as_image(const std::vector<unsigned char>& rgba_matrix, int width, int height, const std::string& file_name) {
    // Check if the matrix size matches the width * height * 4 (RGBA)
    if (rgba_matrix.size() != width * height * 4) {
        std::cerr << "Invalid RGBA matrix size. Expected " << width * height * 4 << " but got " << rgba_matrix.size() << std::endl;
        return;
    }

    // Save the image as a PNG file
    if (stbi_write_png(file_name.c_str(), width, height, 4, rgba_matrix.data(), width * 4)) {
        std::cout << "Image saved successfully to " << file_name << std::endl;
    } else {
        std::cerr << "Failed to save the image!" << std::endl;
    }
}

int main() {
    // Example usage

    // Define image dimensions
    int width = 256;
    int height = 256;

    // Create a simple RGBA matrix (solid red color)
    std::vector<unsigned char> rgba_matrix(width * height * 4);

    for (int i = 0; i < width * height; ++i) {
        rgba_matrix[i * 4 + 0] = 255; // R
        rgba_matrix[i * 4 + 1] = 0;   // G
        rgba_matrix[i * 4 + 2] = 0;   // B
        rgba_matrix[i * 4 + 3] = 255; // A
    }

    // Export the RGBA matrix as a PNG image
    export_rgba_matrix_as_image(rgba_matrix, width, height, "output_image.png");

    return 0;
}
