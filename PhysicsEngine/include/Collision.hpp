#pragma once

#include "Object.hpp"
#include "manifold/CollisionManifold.hpp"

namespace pe {
    class Collision {
        public:
        Object* obj_a;
        Object* obj_b;

        CollisionManifold manifold;

        Collision();
        Collision(pe::Object*, pe::Object*, CollisionManifold& );
        
    };
}