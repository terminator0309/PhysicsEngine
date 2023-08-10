#include "Algo.hpp"
#include "collider/CircleCollider.hpp"
#include "math/GJK.hpp"

namespace pe {
        CircleCollider::CircleCollider(float r) {
            radius = r;
            std::cout << "Object created of type: " << this->getName() << std::endl;
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
            auto manifold = pe::GJK(otherCollider, otherTransform, this, transform);

            if (manifold.getIsColliding()) {
                auto point = algo::findContactPoints(this, transform, otherCollider, otherTransform)[0];
                manifold.addCollisionPoint(point);
            }

            return manifold;
        }
        
        CollisionManifold CircleCollider::testCollision(Transform* transform, BoxCollider* otherCollider, Transform* otherTransform) {
            auto manifold = pe::GJK(otherCollider, otherTransform, this, transform);

            if (manifold.getIsColliding()) {
                auto point = algo::findContactPoints(this, transform, otherCollider, otherTransform)[0];
                manifold.addCollisionPoint(point);
            }

            return manifold;
        }
        

        std::string CircleCollider::getName() {
            return "Circle";
        }
}