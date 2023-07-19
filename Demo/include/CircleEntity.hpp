#pragma once

#include "Entity.hpp"
#include "Util.hpp"

namespace game {
    class CircleEntity : public Entity {
        public:
        sf::CircleShape *m_circle;  
        
        CircleEntity(pe::Vector2f , float );

        void update() override;

        sf::CircleShape* getShape();

        ~CircleEntity();
    
    };
}