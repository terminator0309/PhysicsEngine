#include "CircleEntity.hpp"

namespace game {

        CircleEntity::CircleEntity(pe::Vector2f center, float radius) {
            m_object = new pe::Object();
            m_object->transform = new pe::Transform(pe::Vector2f(center - radius));
            m_object->collider = new pe::CircleCollider(radius);

            m_circle = new sf::CircleShape(radius);
            m_circle->setPosition(util::convert(m_object->transform->position));
        }

        void  CircleEntity::update() {
            m_circle->setPosition(util::convert(m_object->transform->position));
        }

        sf::CircleShape* CircleEntity::getShape() {
            return m_circle;
        }

        CircleEntity::~CircleEntity() {
            delete m_circle;
        }

}