#include "DynamicWorld.hpp"

namespace game {
        DynamicWorld::DynamicWorld(int width, int height) {
            pw = std::make_unique<pe::PhysicsWorld>(width, height);
        }

        void DynamicWorld::addEntity(Entity* entity) {
            pw->AddObject(entity->getObject());
            entities.push_back(entity);
        }

        void DynamicWorld::removeEntity(Entity* entity) {
            pw->RemoveObject(entity->getObject());

            auto itr = std::find(entities.begin(), entities.end(), entity);
            if (itr == entities.end())
                return;

            entities.erase(itr);
        }

        void DynamicWorld::setGravity(pe::Vector2f gravity) {
            pw->setGravity(gravity);
        }

        void DynamicWorld::update(float dt) {
            pw->Step(dt);
            for (Entity* entity : entities) {
                entity->update();
            }
        }

        void DynamicWorld::draw(sf::RenderWindow& window) {
            for (Entity* entity : entities) {
                window.draw(*entity->getShape());
            }
            
            for (auto point : pw->collisionPoints) {
                auto tempRect = sf::RectangleShape({ 10, 10 });
                tempRect.setPosition({ point.x-5, point.y-5 });
                tempRect.setFillColor(sf::Color::Red);

                window.draw(tempRect);
            }
        }

        DynamicWorld::~DynamicWorld() {
            
        }
}