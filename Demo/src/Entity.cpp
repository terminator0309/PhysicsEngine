#include "Entity.hpp"

namespace game {

        pe::Object* Entity::getObject() {
            return m_object;
        }

        Entity::~Entity() {
            delete m_object;
        }

}