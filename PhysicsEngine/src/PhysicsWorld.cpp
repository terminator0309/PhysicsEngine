#include "PhysicsWorld.hpp"
#include "manifold/CollisionManifold.hpp"
#include "solver/ImpulseSolver.hpp"
#include "Algo.hpp"

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
            // TEMP
            collisionPoints.clear();

            for (Object* object : m_objects) {
                object->force += m_gravity * object->getMass();
                object->velocity += (object->force * object->getInverseMass()) * dt;

                object->transform->position += object->velocity * dt;

                // Reset the force
                object->force = pe::Vector2f();
                
            }

            auto collisions = ResolveCollision();
            Solve(collisions);

        }

        std::vector<Collision> PhysicsWorld::ResolveCollision() {
            std::vector<Collision> collisions;

            for (Object* a : m_objects) {
                for (Object* b : m_objects) {
                    if (a == b)
                        break;

                    CollisionManifold manifold = a->collider->testCollision(a->transform, b->collider, b->transform);

                    if (manifold.getIsColliding()) {
                        collisions.emplace_back(a, b, manifold);

                        for(auto &point: manifold.getCollisionPoints())
                            collisionPoints.push_back(point);
                    }
                }
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