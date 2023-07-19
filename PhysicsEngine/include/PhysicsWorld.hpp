#pragma once
#include<vector>
#include<algorithm>

#include "Object.hpp"
#include "Collider.hpp"
#include "Solver.hpp"

namespace pe{
    class PhysicsWorld 
    {
        std::vector<Object* > m_objects;
        pe::Vector2f m_gravity = pe::Vector2f(0.0f, 9.8f);
        std::vector<Solver* > solvers;

        int m_WindowHeight;
        int m_WindowWidth;

        public:

            PhysicsWorld();

            PhysicsWorld(int , int );

            void AddObject(Object* );

            void RemoveObject(Object*);

            void Step(float );

            void ResolveCollision();

            void Solve(std::vector<Collision>& );

            ~PhysicsWorld();

    };
}