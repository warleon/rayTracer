#pragma once

#include "Ray.hpp"
#include <glm/glm.hpp>


class Camera {
public:
    // Constructor to initialize the camera with a Ray, tilt angle, width, height, and distance
    Camera(const Ray& ray, float tiltAngle, float width, float height, float distance);

    // Setters
    void setRay(const Ray& ray);
    void setTiltAngle(float tiltAngle);
    void setDistance(float distance);
    void setWidth(float width);
    void setHeight(float height);

    // Getters
    Ray getRay() const;
    glm::vec3 getFront() const;
    glm::vec3 getUp() const;
    glm::vec3 getRight() const;
    float getDistance() const;
    float getWidth() const;
    float getHeight() const;

    // Function to create a Ray that points to the given (x, y) coordinates on the viewport
    Ray getRayForViewportCoordinates(float x, float y) const;

private:
    Ray ray;          // Ray representing the camera's position and direction
    glm::vec3 up;     // Up vector orthogonal to the direction
    glm::vec3 right;  // Right vector orthogonal to both the direction and up
    float distance;   // Distance from the camera to the view plane
    float width;      // Width of the view plane
    float height;     // Height of the view plane
    float tiltAngle;  // Tilt angle of the camera

    // Function to calculate the up and right vectors based on the direction and tilt angle
    void calculateCameraAxes();
};