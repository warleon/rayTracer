#pragma once
#include <glm/glm.hpp>
#include <optional>
#include <cmath>
#include <array>
#include "Object.hpp"
#include "BareTriangle.hpp"

class Triangle : public Object, public BareTriangle {
    Triangle(const material_t& mat,const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2):Object(mat),BareTriangle(v0,v1,v2){}
};
