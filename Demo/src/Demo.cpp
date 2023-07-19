#include "Demo.hpp"

namespace game {
    struct WindowSize {
        static const int height = 600;
        static const int width = 800;
    } WINDOW;

    sf::ContextSettings Demo::getSettings() {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        return settings;
    }

    bool Demo::isWindowClosed(const sf::Event& event) {
        return event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    }

    void Demo::handleWindowClose(sf::RenderWindow& window) {
        window.close();
        return;
    }


    void Demo::run() {

        sf::RenderWindow window(sf::VideoMode(WINDOW.width, WINDOW.height), "DEMO", sf::Style::Default, this->getSettings());

        pe::util::Random::init();

        game::DynamicWorld dw;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (isWindowClosed(event))
                    handleWindowClose(window);

                if (event.type == event.MouseButtonReleased and event.mouseButton.button == sf::Mouse::Left) {
                    float randomRadius = pe::util::Random::getRandom(50);

                    float randomXPosition = pe::util::Random::getRandom(randomRadius, WINDOW.width - randomRadius);
                    float randomYPosition = pe::util::Random::getRandom(randomRadius, WINDOW.height - randomRadius);

                    pe::Vector2f circleCenter = pe::Vector2f(randomXPosition, randomYPosition);

                    dw.addEntity(new game::CircleEntity(circleCenter, randomRadius));
                }
            }


            window.clear();

            dw.update(0.005f);
            dw.draw(window);

            window.display();
        }
    }
}