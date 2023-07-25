#include "CircleEntity.hpp"
#include "collider/CircleCollider.hpp"

namespace game {

        CircleEntity::CircleEntity(pe::Vector2f center, float radius, pe::Vector2f vel) {
            m_object = new pe::Object();
            m_object->transform = new pe::Transform(pe::Vector2f(center));
            m_object->collider = new pe::CircleCollider(radius);
            m_object->velocity = vel;

            m_circle = new sf::CircleShape(radius);
            m_circle->setPosition(util::convert(m_object->transform->position - radius));
            m_circle->setFillColor(sf::Color::Cyan);
        }

        void  CircleEntity::update() {
            m_circle->setPosition(util::convert(m_object->transform->position-m_circle->getRadius()));
        }

        sf::CircleShape* CircleEntity::getShape() {
            return m_circle;
        }

        CircleEntity::~CircleEntity() {
            delete m_circle;
        }

}