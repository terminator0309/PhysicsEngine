#pragma once

#include "Transform.hpp"

namespace pe {
    
    class CircleCollider;

    class Collider {
        public:
        virtual bool testCollision(Transform* tranform, Collider* otherCollider, Transform* otherTransform) = 0;
        virtual bool testCollision(Transform* tranform, CircleCollider* otherCollider, Transform* otherTransform) = 0;
    };

    
}