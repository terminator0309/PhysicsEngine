#include "Algo.hpp"

#include <cmath>

namespace pe {
    namespace algo {

        float distance2(const pe::Vector2f& point_a, const pe::Vector2f& point_b) {
            return (point_a - point_b).getSquare();
        }

        float distance(const pe::Vector2f& point_a, const pe::Vector2f& point_b) {
            return std::sqrt(distance2(point_a, point_b));
        }

        pe::Vector2f PointRotator(pe::Vector2f& point, float angleDegree, pe::Vector2f center = pe::Vector2f()) {
            pe::Vector2f shiftedPoint = point - center;

            float angleRadian = degreeToRadian(angleDegree);
            float cos = std::cos(angleRadian);
            float sin = std::sin(angleRadian);

            float rotatedX = shiftedPoint._x * cos - shiftedPoint._y * sin;
            float rotatedY = shiftedPoint._x * sin + shiftedPoint._y * cos;

            return pe::Vector2f(rotatedX, rotatedY) + center;
        }

        bool checkCircleCircleCollision(float radius1, pe::Vector2f& center1, float radius2, pe::Vector2f& center2) {
            return std::pow(radius1 + radius2, 2) >= distance2(center1 + radius1, center2 + radius2);
        }

        bool checkPointLineCollision(pe::Vector2f& point, pe::Vector2f& lineStart, pe::Vector2f& lineEnd) {
            float slope = (lineEnd._y - lineStart._y) / (lineEnd._x - lineStart._x);
            float yIntercept = (lineStart._y * lineEnd._x) - (lineEnd._y * lineStart._x);

            return point._y == slope * point._x + yIntercept;
        }

        bool checkPointCircleCollision(pe::Vector2f& point, float& radius, pe::Vector2f& center) {
            return distance2(point, center) == radius * radius;
        } 

        bool checkPointAABBCollision(pe::Vector2f& point, pe::Vector2f& min, pe::Vector2f& max) {
            return min._x <= point._x and point._x <= max._x and 
                   min._y <= point._y and point._y <= max._y;
        }

    }
}