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
        float inertia;
        float inverseInertia;

    public:
        pe::Vector2f velocity;
        float angularVelocity;
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

        void setInertia(float);
        float getInertia();
        float getInverseInertia();

        Vector2f getPosition();
        void setPosition(Vector2f);
        float getRotation();
        void setRotation(float);

        bool getStatic();

        ~Object();
    };
}