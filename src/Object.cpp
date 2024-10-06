#include "Object.hpp"

Object::Object(const color_t& color) : color(color) {}
color_t Object::getColor() const {
        return color;
}