#include "PhysicsWorld.hpp"
#include "manifold/CollisionManifold.hpp"
#include "solver/ImpulseSolver.hpp"

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
                if (object->transform->position._x - 100 <= 0 or object->transform->position._x +100 >= m_WorldWidth)
                    object->velocity._x *= -object->cor;

                if (object->transform->position._y - 100 <= 0 or object->transform->position._y + 100 >= m_WorldHeight)
                    object->velocity._y *= -object->cor;
                
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

                    if (manifold.getIsColliding()) 
                        collisions.emplace_back(a, b, manifold);
                }
            }

            return collisions;
        }
        /*
        void PhysicsWorld::applyImpulse(Object* a, Object* b, CollisionManifold* m) {

            float inverseMassA = a->getInverseMass();
            float inverseMassB = b->getInverseMass();
            float inverseMassSum = inverseMassA + inverseMassB;

            float corA = a->cor;
            float corB = b->cor;

            if (inverseMassSum == 0.0f)
                return;

            auto relativeVelocity = b->velocity - a->velocity;
            auto relativeNormal = m->getNormal().normalize();

            // Moving away from each other, do nothing
            if (relativeVelocity.dot(relativeNormal) > 0.0f)
                return;

            float minCor = std::min(corA, corB);
            float numerator = -(1+minCor) * relativeVelocity.dot(relativeNormal);
            float j = numerator / inverseMassSum;

            if (m->getCollisionPoints().size() > 0 and j != 0.0f)
                j /= (float)m->getCollisionPoints().size();

            auto impulse = relativeNormal * j;

            a->velocity += impulse * inverseMassA * -1;
            b->velocity += impulse * inverseMassB * 1;
        }
        */

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