#include "Collision.hpp"

namespace pe {
        Collision::Collision(pe::Object* a, pe::Object* b, CollisionManifold &m)
        {
            obj_a = a;
            obj_b = b;
            manifold = m;
        }
}