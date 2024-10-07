#pragma once
#include <Color.hpp>

typedef struct Material {
    color_t baseColor;  // RGBA color

    Material(const color_t& color) : baseColor(color) {}
} material_t;
