#pragma once
#include <vector>
#include <glm/glm.hpp>

#include <Canvas.hpp>
#include <Camera.hpp>
#include <Scene.hpp>
#include <object/Object.hpp>

class Renderer {
public:
    // Constructor that takes a Canvas and Camera
    Renderer(const Canvas& canvas, const Camera& camera,const Scene& scene);

    // Method to render the scene
    void render();

    // Getter for Canvas
    const Canvas& getCanvas() const;

    // Setter for Canvas
    void setCanvas(const Canvas& newCanvas);

    // Getter for Camera
    const Camera& getCamera() const;

    // Setter for Camera
    void setCamera(const Camera& newCamera);

    Scene& getScene();

    void setScene(const Scene& newScene);
private:
    Canvas canvas;                        // Canvas for rendering
    Camera camera;                        // Camera for viewing
    Scene scene;
};
