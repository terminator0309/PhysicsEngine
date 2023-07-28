#pragma once

#include "Entity.hpp"

namespace game {
	class RectEntity : public Entity {
	public:
		sf::RectangleShape* m_rect;

		RectEntity(float, float, sf::Vector2f, sf::Vector2f);

		void setColor(int) override;

		void update() override;

		sf::RectangleShape* getShape();

		~RectEntity();
	};
}