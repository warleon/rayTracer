#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Canvas.hpp"
#include "Camera.hpp"
#include "Object.hpp"

class Renderer {
public:
    // Constructor that takes a Canvas and Camera
    Renderer(const Canvas& canvas, const Camera& camera);

    // Method to add an object to the renderer
    void addObject(Object* object);

    // Method to render the scene
    void render();

    // Getter for Canvas
    const Canvas& getCanvas() const {
        return canvas;
    }

    // Setter for Canvas
    void setCanvas(const Canvas& newCanvas) {
        canvas = newCanvas;
    }

    // Getter for Camera
    const Camera& getCamera() const {
        return camera;
    }

    // Setter for Camera
    void setCamera(const Camera& newCamera) {
        camera = newCamera;
    }
    std::vector<Object*>& getObjects(){
        return objects;
    }

private:
    Canvas canvas;                        // Canvas for rendering
    Camera camera;                        // Camera for viewing
    std::vector<Object*> objects; // Collection of objects to render
};
