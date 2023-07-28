#pragma once

#include <SFML/Graphics.hpp>

#include "Object.hpp"

namespace game{
    class Entity  {
        protected:
        pe::Object* m_object;
        

        public:
        virtual void update() = 0;
        virtual sf::Shape* getShape() = 0;
        virtual void setColor(int) = 0;

        pe::Object* getObject();

        virtual ~Entity();
    };
}