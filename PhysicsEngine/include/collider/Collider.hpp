#pragma once

#include "Transform.hpp"
#include "manifold/CollisionManifold.hpp"

namespace pe {
    
    class CircleCollider;

    class Collider {
        public:
        virtual CollisionManifold testCollision(Transform* tranform, Collider* otherCollider, Transform* otherTransform) = 0;
        virtual CollisionManifold testCollision(Transform* tranform, CircleCollider* otherCollider, Transform* otherTransform) = 0;
    };

    
}