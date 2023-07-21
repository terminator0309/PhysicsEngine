#include "Algo.hpp"

#include <cmath>

namespace pe {

    bool Vector2f::operator==(Vector2f& other) {
        return algo::compare(this->_x, other._x) and pe::algo::compare(_y, other._y);
    }

    namespace algo {

        bool compare(float& x, float& y, float epsilon) {
            return std::abs(x - y) <= epsilon * std::fmaxf(1.0f, std::fmaxf(std::abs(x), std::abs(y)));
        }

        bool compare(float& x, float& y) {
            return compare(x, y, FLOAT_MIN);
        }

        float degreeToRadian(float degree) {
            return degree * PIE / 180;
        }

        float radianToDegree(float radian) {
            return radian * 180 / PIE;
        }

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

        bool checkPointBoxCollision(pe::Vector2f& point, pe::Vector2f& min, pe::Vector2f& max, float theta, pe::Vector2f& center) {
            pe::Vector2f rotatedPoint = PointRotator(point, theta, center);
            return checkPointAABBCollision(rotatedPoint, min, max);
        }

        bool checkLineCircleCollision(pe::Vector2f& lineStart, pe::Vector2f& lineEnd, float& radius, pe::Vector2f& center) {
            if (checkPointCircleCollision(lineStart, radius, center) or checkPointCircleCollision(lineEnd, radius, center))
                return true;

            pe::Vector2f AB = lineEnd - lineStart;

            // Project Circle center on the line
            // This will be the closest point to circle
            // Then check whether this point is in the circle

            pe::Vector2f AC = center - lineStart;

            float t = (AC.dot(AB)) / (AB.dot(AB));

            // Not on the line segment
            if (t < 0.0f or t > 1.0f)
                return false;

            pe::Vector2f closestPoint = lineStart + lineEnd * 0.5f;

            return checkPointCircleCollision(closestPoint, radius, center);
        }

    }
    
}