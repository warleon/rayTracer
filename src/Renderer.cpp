#include <Renderer.hpp>
// Constructor that takes a Canvas and Camera
Renderer::Renderer(const Canvas& canvas, const Camera& camera, const Scene& scene)
    : canvas(canvas), camera(camera),scene(scene) {}

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
            for (const auto& object : scene.getObjects()) {
                auto hitDistance = object->testRayHit(ray);
                if (hitDistance.value_or(0.0f)>camera.getDistance()) {
                    glm::vec3 point = ray.getPointAt(hitDistance.value());
                    glm::vec3 intensity(0.0f);
                    for (const auto& light : scene.getLights()) {
                        intensity += light->getIlluminationAt(point,object->getNormalAt(point));
                    }
                    
                    pixelColor = object->getColorAt(point) * intensity;

                    break; // Stop after the first hit
                }
            }

            // Set the pixel color on the canvas
            canvas.setPixel(x, y, pixelColor); // Assuming setPixel exists
        }
    }
}

// Getter for Canvas
const Canvas& Renderer::getCanvas() const {
    return canvas;
}

// Setter for Canvas
void Renderer::setCanvas(const Canvas& newCanvas) {
    canvas = newCanvas;
}

// Getter for Camera
const Camera& Renderer::getCamera() const {
    return camera;
}

// Setter for Camera
void Renderer::setCamera(const Camera& newCamera) {
    camera = newCamera;
}

Scene& Renderer::getScene() {
    return scene;
}

void Renderer::setScene(const Scene& newScene){
    scene = newScene;
}