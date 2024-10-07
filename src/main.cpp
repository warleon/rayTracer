#include <Canvas.hpp>
#include <Camera.hpp>
#include <object/primitives.hpp>
#include <Renderer.hpp>
#include <object/OBJLoader.hpp>
#include <light/primitives.hpp>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const glm::vec2& vec) {
    os << "vec2(" << vec.x << ", " << vec.y << ")";
    return os;
}
std::ostream& operator<<(std::ostream& os, const glm::vec3& vec) {
    os << "vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

int main() {
    // Create a canvas with dimensions 256x256
    Canvas canvas(64, 64);

    Ray cameraRay(glm::vec3(-0.02f, 0.11f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f)); // Camera facing +Z
    float tiltAngle = 0.0f ;                // Example tilt angle 15
    float width = 0.15f;                    // Viewport width
    float height = 0.15f;                    // Viewport height
    float distance = 0.4f;                 // Distance to the viewport

    Camera camera(cameraRay, tiltAngle, width, height, distance);

    // Access the right and up vectors
    glm::vec3 right = camera.getRight();
    glm::vec3 up = camera.getUp();
    glm::vec3 front = camera.getFront();

    glm::vec2 norm = canvas.getNormalizedCoordinates(0,0);
    Ray ray = camera.getRayForViewportCoordinates(norm.x,norm.y);

    Scene scene;
    Renderer renderer(canvas,camera,scene);
    OBJLoader loader;
    AmbientLight alight(glm::vec3(0.0f,0.2f,0.0f));
    DirectionalLight dlight(glm::vec3(1.0f,0.0f,0.0f),glm::vec3(-1.0f,-1.0f,1.0f));
    PointLight plight(glm::vec3(0.0f,0.0f,1.0f),cameraRay.getOrigin() + glm::vec3(0.0f,0.4f,0.0f));
    renderer.getScene().addLight(&alight);
    renderer.getScene().addLight(&dlight);
    renderer.getScene().addLight(&plight);

    //Sphere sphere(color_t(0,0,255,255),glm::vec3(0,0,5),1);
    //renderer.getScene().addObject(&sphere);
    Mesh mesh(material_t(color_t(255,255,255,255)));
    std::cout <<"loading objects into the renderer"<<std::endl;
    loader.load("data/bunny.obj",&mesh);
    std::cout <<"LOADED:"<<mesh.getTriangles().size()<<std::endl;
    renderer.getScene().addObject(&mesh);
    std::cout <<"Rendering scene"<<std::endl;
    renderer.render();

    // Export the canvas to a PNG file
    renderer.getCanvas().exportImage("output_canvas.png");
    return 0;
}
