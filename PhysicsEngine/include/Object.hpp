#pragma once

#include <iostream>

#include "Vector.hpp"
#include "Random.hpp"
#include "collider/Collider.hpp"

namespace pe{

    class Object {

        // 0 inverseMass denotes inf mass obj 
        float mass;
        float inverseMass;
        bool isStatic;
        
    public:
        pe::Vector2f velocity;
        pe::Vector2f force;

        // Coefficient of restitution
        float cor = 1.0f;

        Collider* collider;
        Transform* transform;

        Object();
        Object(Object&);

        void setMass(float);
        float getMass();
        float getInverseMass();
        bool getStatic();

        ~Object();
    };
}