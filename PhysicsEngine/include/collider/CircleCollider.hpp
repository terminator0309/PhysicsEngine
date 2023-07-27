#pragma once

#include "Collider.hpp"

namespace pe {
    class CircleCollider : public Collider {
        float radius;

    public:
        CircleCollider(float);

        float getRadius();

        Vector2f findSupportPoint(Transform*, Vector2f) override;

        CollisionManifold testCollision(Transform* transform, Collider* otherCollider, Transform* otherTransform) override;

        CollisionManifold testCollision(Transform* transform, CircleCollider* otherCollider, Transform* otherTransform) override;
    };
}