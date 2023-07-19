#pragma once

#include "Algo.hpp"

namespace pe {
    class Transform {
        public:
        pe::Vector2f position;

        Transform(pe::Vector2f);
    };

    class CircleCollider;

    class Collider {
        public:
        virtual bool testCollision(Transform* tranform, Collider* otherCollider, Transform* otherTransform) = 0;
        virtual bool testCollision(Transform* tranform, CircleCollider* otherCollider, Transform* otherTransform) = 0;
    };

    class CircleCollider : public Collider {
        float radius;

        public:
        CircleCollider(float);

        float getRadius();

        bool testCollision(Transform* transform, Collider* otherCollider, Transform* otherTransform) override;

        bool testCollision(Transform* transform, CircleCollider* otherCollider, Transform* otherTransform) override;
    };
}