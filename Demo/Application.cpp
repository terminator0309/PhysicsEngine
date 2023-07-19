#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(100, 100), "Demo");

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.Closed == sf::Event::Closed)
				window.close();
		}
	}
}