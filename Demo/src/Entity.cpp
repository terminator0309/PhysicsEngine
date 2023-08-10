#include "Entity.hpp"

namespace game {

        pe::Object* Entity::getObject() {
            return m_object;
        }

        void Entity::setMass(float mass) {
            m_object->setMass(mass);
        }

        Entity::~Entity() {
            delete m_object;
        }

}