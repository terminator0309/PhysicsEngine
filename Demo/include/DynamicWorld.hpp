#pragma once


#include "Entity.hpp"
#include "PhysicsWorld.hpp"

namespace game {
    class DynamicWorld {
        public:
        pe::PhysicsWorld pw;
        std::vector<Entity* > entities;

        void addEntity(Entity* );

        void removeEntity(Entity* );

        void update(float);

        void draw(sf::RenderWindow& );

        ~DynamicWorld();

    };
}