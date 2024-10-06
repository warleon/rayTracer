#include "Ray.hpp"

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
    : origin(origin), direction(glm::normalize(direction)) {}

void Ray::setOrigin(const glm::vec3& origin) {
    this->origin = origin;
}

void Ray::setDirection(const glm::vec3& direction) {
    this->direction = glm::normalize(direction);
}

glm::vec3 Ray::getOrigin() const {
    return origin;
}

glm::vec3 Ray::getDirection() const {
    return direction;
}
