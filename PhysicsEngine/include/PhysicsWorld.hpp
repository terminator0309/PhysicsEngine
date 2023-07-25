#pragma once
#include<vector>
#include<algorithm>

#include "Object.hpp"
#include "collider/Collider.hpp"
#include "solver/Solver.hpp"

namespace pe{
    class PhysicsWorld 
    {
        std::vector<Object* > m_objects;
        pe::Vector2f m_gravity = pe::Vector2f(0.0f, 9.8f);
        std::vector<Solver* > solvers;

        int m_WorldHeight;
        int m_WorldWidth;

        public:

            PhysicsWorld();

            PhysicsWorld(int , int );

            void AddObject(Object* );

            void RemoveObject(Object*);

            void setGravity(pe::Vector2f);

            void Step(float );

            ~PhysicsWorld();

        private:

            std::vector<Collision> ResolveCollision();

            void Solve(std::vector<Collision>& );

            //void applyImpulse(Object* , Object* , CollisionManifold* );


    };
}