#pragma once

#include <SFML/Graphics.hpp>

#include "DynamicWorld.hpp"
#include "CircleEntity.hpp"

namespace game{
   
    class Demo {

        sf::ContextSettings getSettings();

        bool isWindowClosed(const sf::Event& );

        void handleWindowClose(sf::RenderWindow& );

        public:

            void run();

    };
}





