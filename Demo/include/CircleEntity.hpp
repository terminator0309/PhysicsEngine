#pragma once

#include "Entity.hpp"
#include "Util.hpp"

namespace game {
    
    class CircleEntity : public Entity {
        public:
        sf::CircleShape *m_circle;  
        
        CircleEntity(pe::Vector2f , float , pe::Vector2f);

        void setColor(int) override;

        void update() override;

        sf::CircleShape* getShape();

        ~CircleEntity();
    
    };
}