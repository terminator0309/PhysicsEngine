#include "collider/BoxCollider.hpp"

namespace pe {

	BoxCollider::BoxCollider(pe::Vector2f& min, pe::Vector2f& max) {
		m_Size = max - min;
	}

	pe::Vector2f BoxCollider::getMin(Transform* transform) {
		return transform->position - (m_Size * 0.5f);
	}

	pe::Vector2f BoxCollider::getMax(Transform* transform) {
		return transform->position + (m_Size * 0.5f);
	}

	std::vector<pe::Vector2f> BoxCollider::getVertices(Transform* transform) {
		pe::Vector2f min = getMin(transform);
		pe::Vector2f max = getMax(transform);

		std::vector<pe::Vector2f> vertices = { pe::Vector2f(min._x, min._y), pe::Vector2f(min._x, max._y),
											   pe::Vector2f(max._x, min._y), pe::Vector2f(max._x, max._y) };

		if(transform->rotation != 0.0f)
			for (auto vertex : vertices) {
				// TODO: rotate points about transform->position
				// PointRotator(vertex, transform->position, transform->rotation)
			}

		return vertices;
	}

}