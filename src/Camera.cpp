#include <Camera.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp> // For calculating angles

Camera::Camera(const Ray& ray, float tiltAngle, float width, float height, float distance)
    : ray(ray), tiltAngle(tiltAngle), width(width), height(height), distance(distance) {
    calculateCameraAxes();  // Calculate the initial up and right vectors based on the ray's direction and tilt angle
}

void Camera::setRay(const Ray& ray) {
    this->ray = ray;
    calculateCameraAxes();  // Recalculate the up and right vectors when the ray changes
}

void Camera::setTiltAngle(float tiltAngle) {
    this->tiltAngle = tiltAngle;
    calculateCameraAxes();  // Recalculate the up and right vectors when the tilt angle changes
}

void Camera::setDistance(float distance) {
    this->distance = distance;
}

void Camera::setWidth(float width) {
    this->width = width;
}

void Camera::setHeight(float height) {
    this->height = height;
}

Ray Camera::getRay() const {
    return ray;
}

glm::vec3 Camera::getFront() const {
    return ray.getDirection();
}

glm::vec3 Camera::getUp() const {
    return up;
}

glm::vec3 Camera::getRight() const {
    return right;
}

float Camera::getDistance() const {
    return distance;
}

float Camera::getWidth() const {
    return width;
}

float Camera::getHeight() const {
    return height;
}

Ray Camera::getRayForViewportCoordinates(float x, float y) const {
    glm::vec3 origin = ray.getOrigin();
    glm::vec3 viewportCenter = origin + (ray.getDirection() * distance);

    // Calculate target position in the viewport
    glm::vec3 target = viewportCenter + right * (x * width/2.0f) + up * (y * height/2.0f);
    glm::vec3 direction = glm::normalize(target - origin);

    return Ray(origin, direction);
}

void Camera::calculateCameraAxes() {
    glm::vec3 front= ray.getDirection();
    // Normalize the direction vector
    glm::vec3 normalizedDirection = glm::normalize(front);

    // Define the initial up vector (world +Y axis)
    glm::vec3 initialUp(0.0f, 1.0f, 0.0f);

    // Calculate the right vector as the cross product of the direction and the initial up
    right = -glm::normalize(glm::cross(normalizedDirection, initialUp));

    // Calculate the new up vector by rotating the initial up vector around the right vector by the tilt angle
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(tiltAngle), front);
    
    // Apply the rotation to the initial up vector
    up = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(initialUp, 0.0f)));

    // Ensure the up vector is orthogonal to the direction vector
    right = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(right, 0.0f))); 
}
