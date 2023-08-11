#include "RectEntity.hpp"
#include "collider/BoxCollider.hpp"
#include "Util.hpp"
#include "Algo.hpp"

namespace game {
	RectEntity::RectEntity(float width, float height, sf::Vector2f position, sf::Vector2f vel) {
		m_object = new pe::Object();
		m_object->transform = new pe::Transform(pe::Vector2f(position.x, position.y));
		m_object->transform->rotation = 0;

		pe::Vector2f min = { position.x - width / 2, position.y - height / 2 };
		pe::Vector2f max = { position.x + width / 2, position.y + height / 2 };

		m_object->collider = new pe::BoxCollider(min, max);
		m_object->velocity = pe::Vector2f(vel.x, vel.y);
		m_object->setInertia(pe::algo::getBoxInertia(m_object->getMass(), width, height));

		m_rect = new sf::RectangleShape(sf::Vector2f(width, height));
		m_rect->setOrigin({width / 2, height / 2});
		m_rect->setFillColor(sf::Color::Green);
	}

	void RectEntity::setMass(float mass) {
		auto size = m_rect->getSize();

		m_object->setMass(mass);
		m_object->setInertia(pe::algo::getBoxInertia(m_object->getMass(), size.x, size.y));
	}

	void RectEntity::update() {
		m_rect->setPosition(util::convert(m_object->transform->position));
		m_rect->setRotation(m_object->transform->rotation);
	}

	sf::RectangleShape* RectEntity::getShape() {
		return m_rect;
	}

	RectEntity::~RectEntity() {
		delete m_rect;
	}


}