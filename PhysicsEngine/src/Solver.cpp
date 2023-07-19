#include "Solver.hpp"

namespace pe {
        void Solver::solve(Collision* collision) {
            Object* a = collision->obj_a;
            Object* b = collision->obj_b;

            Vector2f velocity_a = a->velocity;
            Vector2f velocity_b = b->velocity;

            a->velocity = (velocity_a * (a->mass - b->mass) + velocity_b * 2 * b->mass) / (a->mass + b->mass);
            b->velocity = (velocity_b * (b->mass - a->mass) + velocity_a * 2 * a->mass) / (a->mass + b->mass);
        }

        void Solver::solve(std::vector<Collision>& collisions) {
            for (Collision& collision : collisions) {
                this->solve(&collision);
            }
        }
}