#pragma once

#include <glm/glm.hpp>

class Ray {
public:
    // Constructor to initialize the Ray with an origin point and a direction vector
    Ray(const glm::vec3& origin, const glm::vec3& direction);

    // Setters
    void setOrigin(const glm::vec3& origin);
    void setDirection(const glm::vec3& direction);

    // Getters
    glm::vec3 getOrigin() const;
    glm::vec3 getDirection() const;

private:
    glm::vec3 origin;      // The starting point of the Ray
    glm::vec3 direction;   // The normalized direction of the Ray
};