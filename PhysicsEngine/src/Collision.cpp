#include "Collision.hpp"

namespace pe {
        Collision::Collision(pe::Object* a, pe::Object* b)
        {
            obj_a = a;
            obj_b = b;
        }
}