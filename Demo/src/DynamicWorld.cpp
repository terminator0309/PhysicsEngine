#include "DynamicWorld.hpp"

namespace game {

        void DynamicWorld::addEntity(Entity* entity) {
            pw.AddObject(entity->getObject());
            entities.push_back(entity);
        }

        void DynamicWorld::removeEntity(Entity* entity) {
            pw.RemoveObject(entity->getObject());

            auto itr = std::find(entities.begin(), entities.end(), entity);
            if (itr == entities.end())
                return;

            entities.erase(itr);
        }

        void DynamicWorld::update(float dt) {
            pw.Step(dt);
            for (Entity* entity : entities) {
                entity->update();
            }
        }

        void DynamicWorld::draw(sf::RenderWindow& window) {
            for (Entity* entity : entities) {
                window.draw(*entity->getShape());
            }
        }

        DynamicWorld::~DynamicWorld() {
            for (Entity* entity : entities) {
                delete entity;
            }
        }
}