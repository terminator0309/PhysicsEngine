#pragma once


#include "Entity.hpp"
#include "PhysicsWorld.hpp"

namespace game {
    class DynamicWorld {
        public:
            std::unique_ptr<pe::PhysicsWorld> pw;
        
        std::vector<Entity* > entities;

        DynamicWorld(int, int);

        void addEntity(Entity* );

        void removeEntity(Entity* );

        void setGravity(pe::Vector2f);

        void update(float);

        void draw(sf::RenderWindow& );

        ~DynamicWorld();

    };
}