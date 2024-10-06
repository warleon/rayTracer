#pragma once
#include <glm/glm.hpp>
#include <optional>
#include "Ray.hpp"
#include "Color.hpp"


class Object {
public:
    // Constructor to initialize the color
    Object(const color_t& color);

    // Virtual destructor
    virtual ~Object() = default;

    // Pure virtual function to test ray intersection
    virtual std::optional<float> testRayHit(const Ray& ray) const = 0;

    // Getter for color
    color_t getColor() const;

protected:
    color_t color; // RGBA color member
};
