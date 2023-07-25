#pragma once

#include <vector>

#include "Collision.hpp"

namespace pe {
    class Solver {
        int a;
        public:
            virtual void solve(std::vector<Collision>& ) = 0;
    };
}


// NON IMPULSE BASED COLLISION RESOLUTION (circle v circle)
/*
void Solver::solve(Collision* collision) {
    Object* a = collision->obj_a;
    Object* b = collision->obj_b;

    Vector2f velocity_a = a->velocity;
    Vector2f velocity_b = b->velocity;

    Vector2f center_a = a->transform->position;
    Vector2f center_b = b->transform->position;

    Vector2f vectorab = (center_b - center_a);
    Vector2f unitVectorab = vectorab.normalize();

    Vector2f axInitialVelocity = unitVectorab * (velocity_a.dot(unitVectorab));
    Vector2f bxInitialVelocity = (Vector2f() - unitVectorab) * velocity_b.dot(Vector2f() - unitVectorab);

    Vector2f ayInitialVelocity = velocity_a - axInitialVelocity;
    Vector2f byInitialVelocity = velocity_b - bxInitialVelocity;

    Vector2f bxFinalVelocity = axInitialVelocity;
    Vector2f axFinalVelocity = bxInitialVelocity;

    Vector2f ayFinalVelocity = ayInitialVelocity;
    Vector2f byFinalVelocity = byInitialVelocity;

    a->velocity = axFinalVelocity + ayFinalVelocity;
    b->velocity = bxFinalVelocity + byFinalVelocity;

}
*/