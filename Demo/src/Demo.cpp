#include "Demo.hpp"
#include "RectEntity.hpp"

namespace game {
    struct WindowSize {
        static const int height = 800;
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
        sf::RectangleShape shape({ 200, 200 });
        
        game::DynamicWorld dw(WINDOW.width, WINDOW.height);
        dw.setGravity(pe::Vector2f(0, 2.0f));

        CircleEntity circle1(pe::Vector2f(380, 300), 30, pe::Vector2f(4, 7));
        CircleEntity circle2(pe::Vector2f(400, 410), 30, pe::Vector2f(-4, -5));
        RectEntity rect1(50, 50, sf::Vector2f(600,200), sf::Vector2f());
        RectEntity rect2(50, 50, sf::Vector2f(600, 200), sf::Vector2f());

        RectEntity platform(600, 100, sf::Vector2f(400, 600), {});
        platform.setMass(0.0f);

        dw.addEntity(&circle1);
        //dw.addEntity(&rect);
        dw.addEntity(&circle2);
        dw.addEntity(&platform);

        bool play = true;

        sf::Clock clock;
        float lastTime = 0;
        int fps = 0;

        sf::Font font;
        if (not font.loadFromFile("F:/C++/Game/font.ttf")) {
            std::cout << "cannot load font\n";
            return;
        }

        sf::Text fpsWindowText;
        fpsWindowText.setFont(font);
        fpsWindowText.setCharacterSize(24);
        fpsWindowText.setPosition(10, 10);
        fpsWindowText.setFillColor(sf::Color::Green);

        

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (isWindowClosed(event))
                    handleWindowClose(window);
                
                // SPACE pauses simulation
                if (event.type == event.KeyPressed and sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    play = !play;
                
                // RIGHT CLICK adds a circle
                if (event.type == event.MouseButtonReleased and event.mouseButton.button == sf::Mouse::Right) {
                    dw.addEntity(new CircleEntity({ (float)event.mouseButton.x, (float)event.mouseButton.y }, 30, {}));
                }

                // RIGHT CLICK adds a circle
                if (event.type == event.MouseButtonReleased and event.mouseButton.button == sf::Mouse::Left) {
                    dw.addEntity(new RectEntity(50, 50, { (float)event.mouseButton.x, (float)event.mouseButton.y }, sf::Vector2f()));
                }
            }


            window.clear();

            if(play)
                dw.update(0.015f);

            dw.draw(window);

            // FPS

            float elapsedTime = clock.getElapsedTime().asSeconds();
            if (elapsedTime > 1) {
                clock.restart();
                fpsWindowText.setString(std::to_string(fps));
                fps = 0;
            }
            window.draw(fpsWindowText);

            window.display();
            fps++;
        }
    }
}