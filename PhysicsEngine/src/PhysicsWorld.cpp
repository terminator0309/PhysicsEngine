#include "PhysicsWorld.hpp"
#include "manifold/CollisionManifold.hpp"
#include "solver/ImpulseSolver.hpp"

#include <set>

namespace pe {

        PhysicsWorld::PhysicsWorld() {
            m_WorldHeight = 100;
            m_WorldWidth = 100;

            solvers.push_back(new ImpulseSolver());
        }

        PhysicsWorld::PhysicsWorld(int width, int height) {
            m_WorldHeight = height;
            m_WorldWidth = width;

            solvers.push_back(new ImpulseSolver());
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

        void PhysicsWorld::setGravity(pe::Vector2f gravity) {
            m_gravity = gravity;
        }

        void PhysicsWorld::Step(float dt) {
            for (Object* object : m_objects) {
                object->force += m_gravity * object->getMass();
                object->velocity += (object->force / object->getMass()) * dt;
                object->transform->position += object->velocity * dt;

                // Reset the force
                object->force = pe::Vector2f();

                // TEMP
                // Bouncing of the boundary
                if (object->transform->position.x - 100 <= 0 or object->transform->position.x +100 >= m_WorldWidth)
                    object->velocity.x *= -object->cor;

                if (object->transform->position.y - 100 <= 0 or object->transform->position.y + 100 >= m_WorldHeight)
                    object->velocity.y *= -object->cor;
                
            }

            auto collisions = ResolveCollision();
            Solve(collisions);

        }

        std::vector<Collision> PhysicsWorld::ResolveCollision() {
            std::vector<Collision> collisions;
            std::set<pe::Object* > temp;

            for (Object* a : m_objects) {
                for (Object* b : m_objects) {
                    if (a == b)
                        break;

                    CollisionManifold manifold = a->collider->testCollision(a->transform, b->collider, b->transform);

                    if (manifold.getIsColliding()) {
                        collisions.emplace_back(a, b, manifold);
                        temp.insert(a);
                        temp.insert(b);
                    }
                }
            }

            for (Object* obj : m_objects) {
                if (temp.find(obj) == temp.end())
                    obj->color = 0;
                else
                    obj->color = 1;
            }

            return collisions;
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