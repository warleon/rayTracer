#include "Sphere.hpp"
Sphere::Sphere(const material_t& mat, const glm::vec3& center, float radius)
    : Object(mat), center(center), radius(radius) {}

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

// Get the normal vector at a point on the sphere surface
glm::vec3 Sphere::getNormalAt(const glm::vec3& point) const {
    return glm::normalize(point - center);  // Normalized vector from center to the point
}