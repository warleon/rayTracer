#include "Canvas.hpp"
#include "Camera.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const glm::vec3& vec) {
    os << "vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

int main() {
    // Create a canvas with dimensions 256x256
    Canvas canvas(256, 256);

    // Set some pixels to different colors
    canvas.setPixel(50, 50, 255, 0, 0, 255);   // Red
    canvas.setPixel(100, 100, 0, 255, 0, 255); // Green
    canvas.setPixel(150, 150, 0, 0, 255, 255); // Blue

    // Export the canvas to a PNG file
    canvas.exportImage("output_canvas.png");

    Ray cameraRay(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Camera facing +Z
    float tiltAngle = 15.0f;                // Example tilt angle 15
    float width = 16.0f;                    // Viewport width
    float height = 9.0f;                    // Viewport height
    float distance = 10.0f;                 // Distance to the viewport

    Camera camera(cameraRay, tiltAngle, width, height, distance);

    // Access the right and up vectors
    glm::vec3 right = camera.getRight();
    glm::vec3 up = camera.getUp();
    glm::vec3 front = camera.getFront();


    std::cout <<"Front vector ="<<front<<std::endl;
    std::cout <<"Right vector ="<<right<<std::endl;
    std::cout <<"Up vector ="<<up<<std::endl;

    std::cout<<glm::dot(right,up)<<std::endl;
    std::cout<<glm::dot(right,front)<<std::endl;
    std::cout<<glm::dot(up,front)<<std::endl;

    return 0;
}
