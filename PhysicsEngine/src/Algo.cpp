#include "Algo.hpp"

namespace pe {
    namespace algo {
        // returns squared distance between two points
        float distance2(const pe::Vector2f& point_a, const pe::Vector2f& point_b) {
            return (float)std::pow(std::abs(point_a._x - point_b._x), 2) + (float)std::pow(std::abs(point_a._y - point_b._y), 2);
        }

        // returns real distance between two points
        float distance(const pe::Vector2f& point_a, const pe::Vector2f& point_b) {
            return std::sqrt(distance2(point_a, point_b));
        }

        bool checkCircleCircleCollision(float radius1, pe::Vector2f& center1, float radius2, pe::Vector2f& center2) {
            return std::pow(radius1 + radius2, 2) >= distance2(center1 + radius1, center2 + radius2);
        }
    }
}