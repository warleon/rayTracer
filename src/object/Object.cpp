#include "Object.hpp"

Object::Object(const material_t& mat) : material(mat) {}
color_t Object::getColorAt(const glm::vec3& point) const {
    return material.baseColor;
}