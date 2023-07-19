#include "PhysicsWorld.hpp"

namespace pe {

        PhysicsWorld::PhysicsWorld() {
            m_WindowHeight = 100;
            m_WindowWidth = 100;

            solvers.push_back(new Solver());
        }

        PhysicsWorld::PhysicsWorld(int height, int width) {
            m_WindowHeight = height;
            m_WindowWidth = width;

            solvers.push_back(new Solver());
        }

        void PhysicsWorld::AddObject(Object* obj) {
            m_objects.push_back(obj);
        }

        void PhysicsWorld::RemoveObject(Object* obj) {
            auto itr = std::find(m_objects.begin(), m_objects.end(), obj);
            if (itr == m_objects.end())
                return;

            m_objects.erase(itr);
        }

        void PhysicsWorld::Step(float dt) {
            for (Object* object : m_objects) {
                object->force += m_gravity * object->mass;
                object->velocity += (object->force / object->mass) * dt;
                object->transform->position += object->velocity * dt;

                // Reset the force
                object->force = pe::Vector2f();
            }

            ResolveCollision();
        }

        void PhysicsWorld::ResolveCollision() {
            std::vector<Collision> collisions;

            for (Object* a : m_objects) {
                for (Object* b : m_objects) {
                    if (a == b)
                        break;

                    bool hasCollision = a->collider->testCollision(a->transform, b->collider, b->transform);

                    if (hasCollision) {
                        Collision collision(a, b);
                        collisions.push_back(collision);
                    }
                }
            }

            Solve(collisions);
        }

        void PhysicsWorld::Solve(std::vector<Collision>& collisions) {
            for (Solver* solver : solvers) {
                solver->solve(collisions);
            }
        }

        PhysicsWorld::~PhysicsWorld() {
            for (Solver* solver : solvers) {
                delete solver;
            }
        }
}