#pragma once

#include "Object.hpp"

namespace pe {
    class Collision {
        public:
        Object* obj_a;
        Object* obj_b;

        Collision(pe::Object*, pe::Object*);
        
    };
}