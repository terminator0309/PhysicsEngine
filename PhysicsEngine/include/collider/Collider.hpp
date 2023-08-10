#pragma once

#include "Transform.hpp"
#include "manifold/CollisionManifold.hpp"

#include <string>
#include <iostream>

namespace pe {
    
    class BoxCollider;
    class CircleCollider;

    class Collider {
        public:

        virtual std::string getName() = 0;
        // Points which are furthest in the given direction
        virtual Vector2f findSupportPoint(Transform*, Vector2f) = 0;

        virtual CollisionManifold testCollision(Transform* tranform, Collider* otherCollider, Transform* otherTransform) = 0;

        virtual CollisionManifold testCollision(Transform* tranform, CircleCollider* otherCollider, Transform* otherTransform) = 0;

        virtual CollisionManifold testCollision(Transform* tranform, BoxCollider* otherCollider, Transform* otherTransform) = 0;
    };

    
}