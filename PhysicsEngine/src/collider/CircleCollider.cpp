#include "Algo.hpp"
#include "collider/CircleCollider.hpp"

namespace pe {
        CircleCollider::CircleCollider(float r) {
            radius = r;
        };

        float CircleCollider::getRadius() {
            return radius;
        }

        bool CircleCollider::testCollision(Transform* transform, Collider* otherCollider, Transform* otherTransform) {
            return otherCollider->testCollision(otherTransform, this, transform);
        }

        bool CircleCollider::testCollision(Transform* transform, CircleCollider* otherCollider, Transform* otherTransform) {
            return algo::checkCircleCircleCollision(this->getRadius(), transform->position, otherCollider->getRadius(), otherTransform->position);
        }
}