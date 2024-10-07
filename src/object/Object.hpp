#pragma once
#include <glm/glm.hpp>
#include <optional>
#include <Ray.hpp>
#include <Material.hpp>


class Object {
public:
    // Constructor to initialize the color
    Object(const material_t& mat);

    // Virtual destructor
    virtual ~Object() = default;

    // Pure virtual function to test ray intersection
    virtual std::optional<float> testRayHit(const Ray& ray) const = 0;


    // Abstract method to get the normal vector at a given point on the surface
    virtual glm::vec3 getNormalAt(const glm::vec3& point) const = 0;

    // Return the color of the object at the given point on its surface
    virtual color_t getColorAt(const glm::vec3& point) const;

protected:
    material_t material;  // Material that contains the base color

};
