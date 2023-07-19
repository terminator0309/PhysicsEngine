#pragma once

#include <cmath>

#include "Vector.hpp"

namespace pe {
    namespace algo {
        // returns squared distance between two points
        float distance2(const pe::Vector2f& point_a, const pe::Vector2f& point_b);

        // returns real distance between two points
        float distance(const pe::Vector2f& point_a, const pe::Vector2f& point_b);

        bool checkCircleCircleCollision(float radius1, pe::Vector2f& center1, float radius2, pe::Vector2f& center2);
    }
}