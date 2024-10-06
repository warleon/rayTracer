#include "Renderer.hpp"
// Constructor that takes a Canvas and Camera
Renderer::Renderer(const Canvas& canvas, const Camera& camera)
    : canvas(canvas), camera(camera) {}

// Method to add an object to the renderer
void Renderer::addObject(Object* object) {
    objects.push_back(object);
}

// Method to render the scene
void Renderer::render() {
    for (int y = 0; y < canvas.getHeight(); ++y) {
        for (int x = 0; x < canvas.getWidth(); ++x) {
            // Convert pixel coordinates to normalized device coordinates
            glm::vec2 ndc = canvas.getNormalizedCoordinates(x, y);

            // Create a ray from the camera to the pixel in normalized device coordinates
            Ray ray = camera.getRayForViewportCoordinates(ndc.x, ndc.y); // Assuming this function exists

            // Initialize the pixel color
            color_t pixelColor(0,0,0,0); 

            // Check for intersections with each object
            for (const auto& object : objects) {
                auto hitDistance = object->testRayHit(ray);
                if (hitDistance.value_or(0.0f)>camera.getDistance()) {
                    // Example: Set the pixel color based on the object's color
                    pixelColor = object->getColor();
                    break; // Stop after the first hit
                }
            }

            // Set the pixel color on the canvas
            canvas.setPixel(x, y, pixelColor); // Assuming setPixel exists
        }
    }
}
