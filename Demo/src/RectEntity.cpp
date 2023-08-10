#include "RectEntity.hpp"
#include "collider/BoxCollider.hpp"
#include "Util.hpp"

namespace game {
	RectEntity::RectEntity(float width, float height, sf::Vector2f position, sf::Vector2f vel) {
		m_object = new pe::Object();
		m_object->transform = new pe::Transform(pe::Vector2f(position.x, position.y));
		m_object->transform->rotation = 0;

		pe::Vector2f min = { position.x - width / 2, position.y - height / 2 };
		pe::Vector2f max = { position.x + width / 2, position.y + height / 2 };

		m_object->collider = new pe::BoxCollider(min, max);
		m_object->velocity = pe::Vector2f(vel.x, vel.y);

		m_rect = new sf::RectangleShape(sf::Vector2f(width, height));
		m_rect->setPosition(position);
	}

	void RectEntity::update() {
		auto position = m_object->transform->position;
		m_rect->setPosition(sf::Vector2f(position.x - m_rect->getSize().x/2, position.y - m_rect->getSize().y/2));
	}

	sf::RectangleShape* RectEntity::getShape() {
		return m_rect;
	}

	RectEntity::~RectEntity() {
		delete m_rect;
	}


}