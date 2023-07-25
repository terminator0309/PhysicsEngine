#include "Algo.hpp"

#include <cmath>
#include <algorithm>
#include <vector>

namespace pe {

    bool Vector2f::operator==(Vector2f&  other) {
        return algo::compare(this->_x, other._x) and pe::algo::compare(_y, other._y);
    }

    namespace algo {

        bool compare(float x, float y, float epsilon) {
            return std::abs(x - y) <= epsilon * std::fmaxf(1.0f, std::fmaxf(std::abs(x), std::abs(y)));
        }

        bool compare(float x, float y) {
            return compare(x, y, FLOAT_MIN);
        }

        float degreeToRadian(float& degree) {
            return degree * PIE / 180;
        }

        float radianToDegree(float& radian) {
            return radian * 180 / PIE;
        }

        float distance2( pe::Vector2f&  point_a, pe::Vector2f&  point_b) {
            return (point_a - point_b).getSquare();
        }

        float distance( pe::Vector2f&  point_a, pe::Vector2f&  point_b) {
            return std::sqrt(distance2(point_a, point_b));
        }

        pe::Vector2f PointRotator(pe::Vector2f  point, float angleDegree, pe::Vector2f center = pe::Vector2f()) {
            pe::Vector2f shiftedPoint = point - center;

            float angleRadian = degreeToRadian(angleDegree);
            float cos = std::cos(angleRadian);
            float sin = std::sin(angleRadian);

            float rotatedX = shiftedPoint._x * cos - shiftedPoint._y * sin;
            float rotatedY = shiftedPoint._x * sin + shiftedPoint._y * cos;

            return pe::Vector2f(rotatedX, rotatedY) + center;
        }

        bool checkCircleCircleCollision(pe::CircleCollider* circleA, pe::Transform* transformA, pe::CircleCollider* circleB, pe::Transform* transformB) {
            return std::pow(circleA->getRadius() + circleB->getRadius(), 2) >= distance2(transformA->position, transformB->position);
        }

        bool checkPointLineCollision(pe::Vector2f&  point, pe::LineCollider* line) {
            auto lineStart = line->getStart();
            auto lineEnd = line->getEnd();

            float dy = (lineEnd._y - lineStart._y);
            float dx = (lineEnd._x - lineStart._x);

            // Case where slope is inf and line is vertical 
            if (dx == 0.0f)
                return compare(point._x, lineStart._x);

            float slope = dy / dx;
            float yIntercept = (lineStart._y * lineEnd._x) - (lineEnd._y * lineStart._x);

            return point._y == slope * point._x + yIntercept;
        }

        bool checkPointCircleCollision(pe::Vector2f&  point, pe::CircleCollider* circle, pe::Transform* transform) {
            auto center = transform->position;
            auto radius = circle->getRadius();

            return distance2(point, center) == radius * radius;
        } 

        bool checkPointAABBCollision(pe::Vector2f&  point, pe::AABBCollider* aabb, pe::Transform* transform) {
            auto min = aabb->getMin(transform);
            auto max = aabb->getMax(transform);

            return min._x <= point._x and point._x <= max._x and 
                   min._y <= point._y and point._y <= max._y;
        }

        bool checkPointBoxCollision(pe::Vector2f& point, pe::BoxCollider* box, pe::Transform* transform) {
            auto center = transform->position;
            auto theta = transform->rotation;

            auto min = box->getMin(transform);
            auto max = box->getMax(transform);

            pe::Vector2f rotatedPoint = PointRotator(point, -theta, center);

            return min._x <= rotatedPoint._x and rotatedPoint._x <= max._x and
                   min._y <= rotatedPoint._y and rotatedPoint._y <= max._y;;
        }

        bool checkLineCircleCollision(pe::LineCollider* line, pe::CircleCollider* circle, pe::Transform* transform) {
            auto lineStart = line->getStart();
            auto lineEnd = line->getEnd();

            auto center = transform->position;

            if (checkPointCircleCollision(lineStart, circle, transform) or checkPointCircleCollision(lineEnd, circle, transform))
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

            return checkPointCircleCollision(closestPoint, circle, transform);
        }

        bool checkLineAABBCollision(pe::LineCollider* line, pe::AABBCollider* aabb, pe::Transform* transform) {

            auto lineStart = line->getStart();
            auto lineEnd = line->getEnd();

            auto min = aabb->getMin(transform);
            auto max = aabb->getMax(transform);

            if (checkPointAABBCollision(lineStart, aabb, transform) or checkPointAABBCollision(lineEnd, aabb, transform))
                return true;

            pe::Vector2f unitVector = (lineEnd - lineStart).normalize();

            // Inversing unit vector
            unitVector._x = (unitVector._x != 0) ? 1.0f / unitVector._x : FLOAT_MIN;
            unitVector._y = (unitVector._y != 0) ? 1.0f / unitVector._y : FLOAT_MIN;

            min = (min - lineStart) * unitVector;
            max = (max - lineStart) * unitVector;

            float tmin = std::max(std::min(min._x, max._x), std::min(min._y, max._y));
            float tmax = std::min(std::max(min._x, max._x), std::max(min._y, max._y));

            if (tmax < 0 or tmin > tmax)
                return false;
            
            float t = (tmin < 0.0f) ? tmax : tmin;
            return t > 0.0f and t * t < distance2(lineStart, lineEnd);
        }

        bool checkLineBoxCollision(pe::LineCollider* line, pe::BoxCollider* box, pe::Transform* transform) {

            auto lineStart = line->getStart();
            auto lineEnd = line->getEnd();

            auto theta = transform->rotation;
            auto center = transform->position;

            auto min = box->getMin(transform);
            auto max = box->getMax(transform);

            auto rotatedStart = PointRotator(lineStart, -theta, center);
            auto rotatedEnd = PointRotator(lineEnd, -theta, center);

            // After rotating the line, it becomes a regular aabb line collision check
            AABBCollider tempAABB(min, max);
            return checkLineAABBCollision(line, &tempAABB, transform);
        }

        bool raycastCircle(pe::CircleCollider*circle, pe::Transform* transform, Ray ray, RaycastResult& result) {
            auto radius = circle->getRadius();
            auto center = transform->position;
            
            RaycastResult::reset(result);

            // Origin to circle vector
            auto OC = center - ray.getOrigin();
            float r2 = radius * radius;
            float OC2 = OC.getSquare();

            // Projecting the OC vector in the direction of ray
            float a = OC.dot(ray.getDirection());
            float b2 = OC2 - (a * a);

            if (r2 - b2 < 0.0f)
                return false;

            float f = std::sqrt(r2 - b2);
            float t = 0;

            if (OC2 < r2)
                t = a + f;
            else
                t = a - f;

            auto point = ray.getOrigin() + ray.getDirection() * t;
            auto normal = (point - center).normalize();

            result.init(point, normal, t, true);
            return true;
        }

        bool raycastAABB(pe::AABBCollider* aabb, pe::Transform* transform, Ray ray, RaycastResult &result) {
            auto min = aabb->getMin(transform);
            auto max = aabb->getMax(transform);
            
            RaycastResult::reset(result);

            pe::Vector2f unitVector = ray.getDirection();

            // Inversing unit vector
            unitVector._x = (unitVector._x != 0) ? 1.0f / unitVector._x : FLOAT_MIN;
            unitVector._y = (unitVector._y != 0) ? 1.0f / unitVector._y : FLOAT_MIN;

            min = (min - ray.getOrigin()) * unitVector;
            max = (max - ray.getOrigin()) * unitVector;

            float tmin = std::max(std::min(min._x, max._x), std::min(min._y, max._y));
            float tmax = std::min(std::max(min._x, max._x), std::max(min._y, max._y));

            if (tmax < 0 or tmin > tmax)
                return false;

            float t = (tmin < 0.0f) ? tmax : tmin;
            bool hit = t > 0.0f; 
            auto point = ray.getOrigin() + ray.getDirection() * t;
            auto normal = (ray.getOrigin() - point).normalize();

            result.init(point, normal, t, hit);
            return hit;
        }

        bool raycastBox(pe::BoxCollider* box, pe::Transform* transform, Ray ray, RaycastResult& result) {
            auto min = box->getMin(transform);
            auto max = box->getMax(transform);

            auto theta = transform->rotation;
            auto center = transform->position;

            RaycastResult::reset(result);

            pe::Vector2f xAxis(1, 0);
            pe::Vector2f yAxis(0, 1);

            xAxis = PointRotator(xAxis, -theta);
            yAxis = PointRotator(yAxis, -theta);

            pe::Vector2f halfSize = (max - min) / 2;

            pe::Vector2f p = center - ray.getOrigin();
            pe::Vector2f f (xAxis.dot(ray.getDirection()), yAxis.dot(ray.getDirection()));
            pe::Vector2f e (xAxis.dot(p), yAxis.dot(p));

            float tArr[] = {0,0,0,0};

            for (int i = 0; i < 2; i++) {
                if (compare(f.get(i), 0.0f)) {

                    if (-e.get(i) - halfSize.get(i) > 0 or -e.get(i) + halfSize.get(i) < 0)
                        return false;

                    // Avoiding divide by zero
                    f.set(i, FLOAT_MIN);
                }

                tArr[i * 2] = (e.get(i) + halfSize.get(i)) / f.get(i); // tmax 
                tArr[i*2+1] = (e.get(i) - halfSize.get(i)) / f.get(i); // tmin
            }

            float tmin = std::max(std::min(tArr[0], tArr[1]), std::min(tArr[2], tArr[3])); 
            float tmax = std::min(std::max(tArr[0], tArr[1]), std::max(tArr[2], tArr[3]));

            if (tmax < 0 or tmin > tmax)
                return false;

            float t = (tmin < 0.0f) ? tmax : tmin;
            bool hit = t > 0.0f;
            auto point = ray.getOrigin() + ray.getDirection() * t;
            auto normal = (ray.getOrigin() - point).normalize();

            result.init(point, normal, t, hit);
            return hit;
        }

        bool checkAABBCircleCollision(pe::AABBCollider* aabb, pe::Transform* transformAABB, pe::CircleCollider* circle, pe::Transform* transformCircle) {
            return checkCircleAABBCollision(circle, transformCircle, aabb, transformAABB);
        }

        bool checkCircleAABBCollision(pe::CircleCollider* circle, pe::Transform* transformCircle, pe::AABBCollider* aabb, pe::Transform* transformAABB) {
            auto center = transformCircle->position;
            auto radius = circle->getRadius();

            auto min = aabb->getMin(transformAABB);
            auto max = aabb->getMax(transformAABB);

            pe::Vector2f closestPointToCircle = center;

            if (closestPointToCircle._x < min._x)
                closestPointToCircle._x = min._x;
            else if(closestPointToCircle._x > max._x)
                closestPointToCircle._x = max._x;

            if (closestPointToCircle._y < min._y)
                closestPointToCircle._y = min._y;
            else if (closestPointToCircle._x > max._y)
                closestPointToCircle._y = max._y;

            pe::Vector2f circleToAABB = center - closestPointToCircle;
            return circleToAABB.getSquare() <= radius * radius;
        }

        bool checkBoxCircleCollision(pe::BoxCollider* box, pe::Transform* transformBox, pe::CircleCollider* circle, pe::Transform* transformCircle) {
            return checkCircleBoxCollision( circle, transformCircle, box, transformBox);
        }

        bool checkCircleBoxCollision(pe::CircleCollider* circle, pe::Transform* transformCircle, pe::BoxCollider* box, pe::Transform* transformBox) {
            auto center = transformCircle->position;
            auto radius = circle->getRadius();

            auto boxCenter = transformBox->position;
            auto min = box->getMin(transformBox);
            auto max = box->getMax(transformBox);
            auto theta = transformBox->rotation;
            
            pe::Vector2f localMin(0.0f);
            pe::Vector2f localMax = max - min;
            pe::Vector2f halfSize = localMax / 2;

            pe::Vector2f r = center - boxCenter;
            r = PointRotator(r, -theta);

            pe::Vector2f localCircleCenter = r + halfSize;

            pe::Vector2f closestPointToCircle = center;

            if (closestPointToCircle._x < min._x)
                closestPointToCircle._x = min._x;
            else if (closestPointToCircle._x > max._x)
                closestPointToCircle._x = max._x;

            if (closestPointToCircle._y < min._y)
                closestPointToCircle._y = min._y;
            else if (closestPointToCircle._x > max._y)
                closestPointToCircle._y = max._y;

            pe::Vector2f circleToBox = center - closestPointToCircle;
            return circleToBox.getSquare() <= radius * radius;
        }

        bool checkAABBAABBCollision(pe::AABBCollider* aabbA, pe::Transform* transformA, pe::AABBCollider* aabbB, pe::Transform* transformB) {
            // Boxes are axis aligned so need to check on x and y axis only
            std::vector<pe::Vector2f> axesToTest = { pe::Vector2f(1, 0), pe::Vector2f(0, 1) };

            for (auto& axis : axesToTest) {
                if (not overlapOnAxis(aabbA, transformA, aabbB, transformB, axis))
                    return false;
            }

            return true;
        }

        bool checkBoxAABBCollision(pe::BoxCollider* box, pe::Transform* transformB, pe::AABBCollider* aabb, pe::Transform* transformA) {
            return checkAABBBoxCollision(aabb, transformA, box, transformB);
                
        }
        bool checkAABBBoxCollision(pe::AABBCollider* aabb, pe::Transform* transformA, pe::BoxCollider* box, pe::Transform* transformB) {
            std::vector<pe::Vector2f> axesToTest = { pe::Vector2f(1, 0), 
                                                     pe::Vector2f(0, 1),
                                                     PointRotator(pe::Vector2f(1, 0), transformB->rotation),
                                                     PointRotator(pe::Vector2f(0, 1), transformB->rotation)};

            for (auto& axis : axesToTest) {
                if (not overlapOnAxis(aabb, transformA, box, transformB, axis))
                    return false;
            }

            return true;
        }

        bool checkBoxBoxCollision(pe::BoxCollider* boxA, pe::Transform* transformA, pe::BoxCollider* boxB, pe::Transform* transformB) {
            std::vector<pe::Vector2f> axesToTest = { PointRotator(pe::Vector2f(1, 0), transformA->rotation),
                                                     PointRotator(pe::Vector2f(0, 1), transformA->rotation),
                                                     PointRotator(pe::Vector2f(1, 0), transformB->rotation),
                                                     PointRotator(pe::Vector2f(0, 1), transformB->rotation) };

            for (auto& axis : axesToTest) {
                if (not overlapOnAxis(boxA, transformA, boxB, transformB, axis))
                    return false;
            }

            return true;
        }

        bool overlapOnAxis(pe::AABBCollider* aabbA, pe::Transform* transformA, pe::AABBCollider* aabbB, pe::Transform* transformB, pe::Vector2f axis) {
            pe::Vector2f interval_a = getInterval(aabbA, transformA, axis);
            pe::Vector2f interval_b = getInterval(aabbB, transformB, axis);

            return interval_b._x <= interval_a._y and interval_a._x <= interval_b._y;
        }

        bool overlapOnAxis(pe::AABBCollider* aabb, pe::Transform* transformA, pe::BoxCollider* box, pe::Transform* transformB, pe::Vector2f axis) {
            pe::Vector2f interval_a = getInterval(aabb, transformA, axis);
            pe::Vector2f interval_b = getInterval(box, transformB, axis);

            return interval_b._x <= interval_a._y and interval_a._x <= interval_b._y;
        }

        bool overlapOnAxis(pe::BoxCollider* boxA, pe::Transform* transformA, pe::BoxCollider* boxB, pe::Transform* transformB, pe::Vector2f axis) {
            pe::Vector2f interval_a = getInterval(boxA, transformA, axis);
            pe::Vector2f interval_b = getInterval(boxB, transformB, axis);

            return interval_b._x <= interval_a._y and interval_a._x <= interval_b._y;
        }

        Vector2f getInterval(pe::AABBCollider* aabb, pe::Transform* transform, pe::Vector2f axis) {
            pe::Vector2f result;

            std::vector<pe::Vector2f> vertices = aabb->getVertices(transform); 

            // Initializing
            // Assuming x to be the min and y to be the max
            result._x = result._y = vertices[0].dot(axis);

            for (auto &vertex : vertices) {
                float project = vertex.dot(axis);

                if (project < result._x)
                    result._x = project;
                if (project > result._y)
                    result._y = project;
            }

            return result;
        }

        Vector2f getInterval(pe::BoxCollider* box, pe::Transform* transform, pe::Vector2f axis) {
            pe::Vector2f result;

            std::vector<pe::Vector2f> vertices = box->getVertices(transform);

            // Initializing
            // Assuming x to be the min and y to be the max
            result._x = result._y = vertices[0].dot(axis);

            for (auto& vertex : vertices) {
                float project = vertex.dot(axis);

                if (project < result._x)
                    result._x = project;
                if (project > result._y)
                    result._y = project;
            }

            return result;
        }
    }
    
}