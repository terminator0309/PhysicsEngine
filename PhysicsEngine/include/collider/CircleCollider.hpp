#pragma once

#include "Collider.hpp"

namespace pe {
    class CircleCollider : public Collider {
        float radius;

    public:
        CircleCollider(float);

        float getRadius();

        bool testCollision(Transform* transform, Collider* otherCollider, Transform* otherTransform) override;

        bool testCollision(Transform* transform, CircleCollider* otherCollider, Transform* otherTransform) override;
    };
}