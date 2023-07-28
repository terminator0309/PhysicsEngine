#include "Algo.hpp"
#include "collider/CircleCollider.hpp"
#include "math/GJK.hpp"

namespace pe {
        CircleCollider::CircleCollider(float r) {
            radius = r;
        };

        float CircleCollider::getRadius() {
            return radius;
        }

        pe::Vector2f CircleCollider::findSupportPoint(Transform* transform, Vector2f direction) {
            Vector2f center = transform->position;
            return direction * radius + center;
        }

        CollisionManifold CircleCollider::testCollision(Transform* transform, Collider* otherCollider, Transform* otherTransform) {
            return otherCollider->testCollision(otherTransform, this, transform);
        }

        CollisionManifold CircleCollider::testCollision(Transform* transform, CircleCollider* otherCollider, Transform* otherTransform) {
            return pe::GJK(this, transform, otherCollider, otherTransform);
        }

        std::string CircleCollider::getName() {
            return "Circle";
        }
}