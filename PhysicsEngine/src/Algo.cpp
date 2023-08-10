#include "Algo.hpp"

#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

namespace pe {

    bool Vector2f::operator==(Vector2f&  other) {
        return algo::compare(this->x, other.x) and pe::algo::compare(y, other.y);
    }

    namespace algo {

        bool compare(float x, float y, float epsilon) {
            return std::abs(x - y) <= epsilon * std::fmaxf(1.0f, std::fmaxf(std::abs(x), std::abs(y)));
        }

        bool compare(float x, float y) {
            return compare(x, y, FLOAT_MIN);
        }

        bool compare(Vector2f a, Vector2f b) {
            return compare(a.x, b.x) and compare(a.y, b.y);
        }

        float degreeToRadian(float& degree) {
            return degree * PIE / 180;
        }

        float radianToDegree(float& radian) {
            return radian * 180 / PIE;
        }

        float getDistanceSq( pe::Vector2f&  point_a, pe::Vector2f&  point_b) {
            return (point_a - point_b).getSquare();
        }

        float distance( pe::Vector2f&  point_a, pe::Vector2f&  point_b) {
            return std::sqrt(getDistanceSq(point_a, point_b));
        }

        pe::Vector2f PointRotator(pe::Vector2f  point, float angleDegree, pe::Vector2f center = pe::Vector2f()) {
            pe::Vector2f shiftedPoint = point - center;

            float angleRadian = degreeToRadian(angleDegree);
            float cos = std::cos(angleRadian);
            float sin = std::sin(angleRadian);

            float rotatedX = shiftedPoint.x * cos - shiftedPoint.y * sin;
            float rotatedY = shiftedPoint.x * sin + shiftedPoint.y * cos;

            return pe::Vector2f(rotatedX, rotatedY) + center;
        }

        bool checkCircleCircleCollision(pe::CircleCollider* circleA, pe::Transform* transformA, pe::CircleCollider* circleB, pe::Transform* transformB) {
            return std::pow(circleA->getRadius() + circleB->getRadius(), 2) >= getDistanceSq(transformA->position, transformB->position);
        }

        bool checkPointLineCollision(pe::Vector2f&  point, pe::LineCollider* line) {
            auto lineStart = line->getStart();
            auto lineEnd = line->getEnd();

            float dy = (lineEnd.y - lineStart.y);
            float dx = (lineEnd.x - lineStart.x);

            // Case where slope is inf and line is vertical 
            if (dx == 0.0f)
                return compare(point.x, lineStart.x);

            float slope = dy / dx;
            float yIntercept = (lineStart.y * lineEnd.x) - (lineEnd.y * lineStart.x);

            return point.y == slope * point.x + yIntercept;
        }

        bool checkPointCircleCollision(pe::Vector2f&  point, pe::CircleCollider* circle, pe::Transform* transform) {
            auto center = transform->position;
            auto radius = circle->getRadius();

            return getDistanceSq(point, center) == radius * radius;
        } 

        bool checkPointAABBCollision(pe::Vector2f&  point, pe::AABBCollider* aabb, pe::Transform* transform) {
            auto min = aabb->getMin(transform);
            auto max = aabb->getMax(transform);

            return min.x <= point.x and point.x <= max.x and 
                   min.y <= point.y and point.y <= max.y;
        }

        bool checkPointBoxCollision(pe::Vector2f& point, pe::BoxCollider* box, pe::Transform* transform) {
            auto center = transform->position;
            auto theta = transform->rotation;

            auto min = box->getMin(transform);
            auto max = box->getMax(transform);

            pe::Vector2f rotatedPoint = PointRotator(point, -theta, center);

            return min.x <= rotatedPoint.x and rotatedPoint.x <= max.x and
                   min.y <= rotatedPoint.y and rotatedPoint.y <= max.y;;
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
            unitVector.x = (unitVector.x != 0) ? 1.0f / unitVector.x : FLOAT_MIN;
            unitVector.y = (unitVector.y != 0) ? 1.0f / unitVector.y : FLOAT_MIN;

            min = (min - lineStart) * unitVector;
            max = (max - lineStart) * unitVector;

            float tmin = std::max(std::min(min.x, max.x), std::min(min.y, max.y));
            float tmax = std::min(std::max(min.x, max.x), std::max(min.y, max.y));

            if (tmax < 0 or tmin > tmax)
                return false;
            
            float t = (tmin < 0.0f) ? tmax : tmin;
            return t > 0.0f and t * t < getDistanceSq(lineStart, lineEnd);
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
            unitVector.x = (unitVector.x != 0) ? 1.0f / unitVector.x : FLOAT_MIN;
            unitVector.y = (unitVector.y != 0) ? 1.0f / unitVector.y : FLOAT_MIN;

            min = (min - ray.getOrigin()) * unitVector;
            max = (max - ray.getOrigin()) * unitVector;

            float tmin = std::max(std::min(min.x, max.x), std::min(min.y, max.y));
            float tmax = std::min(std::max(min.x, max.x), std::max(min.y, max.y));

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

            if (closestPointToCircle.x < min.x)
                closestPointToCircle.x = min.x;
            else if(closestPointToCircle.x > max.x)
                closestPointToCircle.x = max.x;

            if (closestPointToCircle.y < min.y)
                closestPointToCircle.y = min.y;
            else if (closestPointToCircle.x > max.y)
                closestPointToCircle.y = max.y;

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

            if (closestPointToCircle.x < min.x)
                closestPointToCircle.x = min.x;
            else if (closestPointToCircle.x > max.x)
                closestPointToCircle.x = max.x;

            if (closestPointToCircle.y < min.y)
                closestPointToCircle.y = min.y;
            else if (closestPointToCircle.x > max.y)
                closestPointToCircle.y = max.y;

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

            return interval_b.x <= interval_a.y and interval_a.x <= interval_b.y;
        }

        bool overlapOnAxis(pe::AABBCollider* aabb, pe::Transform* transformA, pe::BoxCollider* box, pe::Transform* transformB, pe::Vector2f axis) {
            pe::Vector2f interval_a = getInterval(aabb, transformA, axis);
            pe::Vector2f interval_b = getInterval(box, transformB, axis);

            return interval_b.x <= interval_a.y and interval_a.x <= interval_b.y;
        }

        bool overlapOnAxis(pe::BoxCollider* boxA, pe::Transform* transformA, pe::BoxCollider* boxB, pe::Transform* transformB, pe::Vector2f axis) {
            pe::Vector2f interval_a = getInterval(boxA, transformA, axis);
            pe::Vector2f interval_b = getInterval(boxB, transformB, axis);

            return interval_b.x <= interval_a.y and interval_a.x <= interval_b.y;
        }

        Vector2f getInterval(pe::AABBCollider* aabb, pe::Transform* transform, pe::Vector2f axis) {
            pe::Vector2f result;

            std::vector<pe::Vector2f> vertices = aabb->getVertices(transform); 

            // Initializing
            // Assuming x to be the min and y to be the max
            result.x = result.y = vertices[0].dot(axis);

            for (auto &vertex : vertices) {
                float project = vertex.dot(axis);

                if (project < result.x)
                    result.x = project;
                if (project > result.y)
                    result.y = project;
            }

            return result;
        }

        Vector2f getInterval(pe::BoxCollider* box, pe::Transform* transform, pe::Vector2f axis) {
            pe::Vector2f result;

            std::vector<pe::Vector2f> vertices = box->getVertices(transform);

            // Initializing
            // Assuming x to be the min and y to be the max
            result.x = result.y = vertices[0].dot(axis);

            for (auto& vertex : vertices) {
                float project = vertex.dot(axis);

                if (project < result.x)
                    result.x = project;
                if (project > result.y)
                    result.y = project;
            }

            return result;
        }

        /**************************************************************/
        // CONTACT POINTS
        /**************************************************************/

        std::vector<pe::Vector2f> findContactPoints(CircleCollider* circleA, Transform* transformA, 
                                                    CircleCollider* circleB, Transform* transformB) {
           
            auto radiusA = circleA->getRadius();
            auto centerA = transformA->position;

            auto radiusB = circleB->getRadius();
            auto centerB = transformB->position;

            auto ab = centerB - centerA;
            auto normal = ab.normalize();

            auto contactPoint = centerA + normal * radiusA;
            return { contactPoint };
        }

        Vector2f getClosestPointOnLineSegment(Vector2f targetPoint, Vector2f pointA, Vector2f pointB) {
            auto ab = pointB - pointA;
            auto ap = targetPoint - pointA;

            float projection = ap.dot(ab);
            float abLengthSq = ab.getSquare();
            float d = projection / abLengthSq;

            if (d <= 0.0f)
                return pointA;
            if (d >= 1.0f)
                return pointB;

            return pointA + ab * d;
        }

        std::vector<pe::Vector2f> findContactPoints(CircleCollider* circle, Transform* transformCircle,
                                                    BoxCollider* box,       Transform* transformBox)
        {
            Vector2f circleCenter = transformCircle->position;
            float radius = circle->getRadius();

            auto boxVertices = box->getVertices(transformBox);

            Vector2f closestContactPoint;
            float minDistanceSq = FLT_MAX;

            for (size_t i = 0; i < boxVertices.size(); i++) {
                Vector2f pointA = boxVertices[i];
                Vector2f pointB = boxVertices[(i + 1) % boxVertices.size()];

                Vector2f closestPoint = getClosestPointOnLineSegment(circleCenter, pointA, pointB);
                float distanceSq = getDistanceSq(closestPoint, circleCenter);

                if (distanceSq < minDistanceSq) {
                    minDistanceSq = distanceSq;
                    closestContactPoint = closestPoint;
                }
            }

            return { closestContactPoint };
        }

        std::vector<pe::Vector2f> findContactPoints(CircleCollider* circle, Transform* transformCircle,
                                                    AABBCollider* box, Transform* transformBox)
        {
            Vector2f circleCenter = transformCircle->position;
            float radius = circle->getRadius();

            auto boxVertices = box->getVertices(transformBox);

            Vector2f closestContactPoint;
            float minDistanceSq = FLT_MAX;

            for (size_t i = 0; i < boxVertices.size(); i++) {
                Vector2f pointA = boxVertices[i];
                Vector2f pointB = boxVertices[(i + 1) % boxVertices.size()];

                Vector2f closestPoint = getClosestPointOnLineSegment(circleCenter, pointA, pointB);
                float distanceSq = getDistanceSq(closestPoint, circleCenter);

                if (distanceSq < minDistanceSq) {
                    minDistanceSq = distanceSq;
                    closestContactPoint = closestPoint;
                }
            }

            return { closestContactPoint };
        }

        std::vector<pe::Vector2f> findContactPoints(BoxCollider* boxA, Transform* transformA,
            BoxCollider* boxB, Transform* transformB) {

            auto boxAVertices = boxA->getVertices(transformA);
            auto boxBVertices = boxB->getVertices(transformB);

            float minDistanceSq = FLT_MAX;
            std::vector<pe::Vector2f> contactPoints(1, pe::Vector2f(FLT_MIN));

            for (size_t i = 0; i < boxAVertices.size(); i++) {
                auto pointA = boxAVertices[i];

                for (size_t j = 0; j < boxBVertices.size(); j++) {
                    auto pointBa = boxBVertices[j];
                    auto pointBb = boxBVertices[(j + 1) % boxBVertices.size()];

                    auto closestPoint = getClosestPointOnLineSegment(pointA, pointBa, pointBb);

                    float distanceSq = getDistanceSq(pointA, closestPoint);

                    if (compare(distanceSq, minDistanceSq)) {
                        if (not compare(closestPoint, contactPoints[0])) {
                            if (contactPoints.size() == 1) contactPoints.push_back(closestPoint);
                            else contactPoints[1] = closestPoint;
                        }
                    }
                    else if (distanceSq < minDistanceSq) {
                        minDistanceSq = distanceSq;
                        contactPoints[0] = closestPoint;
                    }
                }
            }

            for (size_t i = 0; i < boxBVertices.size(); i++) {
                auto pointB = boxBVertices[i];

                for (size_t j = 0; j < boxAVertices.size(); j++) {
                    auto pointAa = boxAVertices[j];
                    auto pointAb = boxAVertices[(j + 1) % boxAVertices.size()];

                    auto closestPoint = getClosestPointOnLineSegment(pointB, pointAa, pointAb);

                    float distanceSq = getDistanceSq(pointB, closestPoint);

                    if (compare(distanceSq, minDistanceSq)) {
                        if (not compare(closestPoint, contactPoints[0])) {
                            if (contactPoints.size() == 1) contactPoints.push_back(closestPoint);
                            else contactPoints[1] = closestPoint;
                        }
                    }
                    else if (distanceSq < minDistanceSq) {
                        minDistanceSq = distanceSq;
                        contactPoints[0] = closestPoint;
                    }
                }
            }

            return contactPoints;
        }
    }


        
    
}