#include "Sphere.hpp"
Sphere::Sphere(const color_t& color, const glm::vec3& center, float radius)
    : Object(color), center(center), radius(radius) {}

std::optional<float> Sphere::testRayHit(const Ray& ray) const  {
    // Implement ray-sphere intersection logic
    glm::vec3 origin = ray.getOrigin(), direction  = ray.getDirection();

    glm::vec3 oc = origin - center;
    float a = glm::dot(direction, direction);
    float b = 2.0f * glm::dot(oc, direction);
    float c = glm::dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return std::nullopt; // No hit
    } else {
        return (-b - glm::sqrt(discriminant)) / (2.0f * a); // Return distance to hit point
    }
}