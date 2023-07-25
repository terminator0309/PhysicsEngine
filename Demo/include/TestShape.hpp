#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

namespace game {
	class TestShape {
		sf::VertexArray points;
	public:
		sf::Vector2f center;
		float radius = 300;

		TestShape() {
			points = sf::VertexArray(sf::LineStrip, 41);
		}

		void updateCircle() {
			points.resize(41);
			float degree = 0;
			
			for (int i = 0; i < 10; i++) {
				float angleRadian = (3.14159f * degree) / 180.0f;

				float x = radius * (float)std::cos(angleRadian);
				float y = radius * (float)std::sin(angleRadian);

				points[i].position = sf::Vector2f(x, y) + center;
				points[i + 10].position = sf::Vector2f(-y, x) + center;
				points[i + 20].position = sf::Vector2f(-x, -y) + center;
				points[i + 30].position = sf::Vector2f(y, -x) + center;
				
				degree += 9;
			}

			points[40].position = points[0].position;
		}

		void draw(sf::RenderTarget& target) {
			target.draw(points);
		}
	};
}