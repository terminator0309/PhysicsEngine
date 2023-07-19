#pragma once
#include "Vector.hpp"
#include "Random.hpp"
#include <iostream>
#include "Collider.hpp"

namespace pe{

    class Object {
        public:
        pe::Vector2f velocity;
        pe::Vector2f force;
        float mass;

        Collider* collider;
        Transform* transform;

        Object();
        Object(Object&);
        ~Object();
    };
}