#include "collider/BoxCollider.hpp"
#include "Algo.hpp"

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

		std::vector<pe::Vector2f> vertices = { pe::Vector2f(min.x, min.y), pe::Vector2f(min.x, max.y),
											   pe::Vector2f(max.x, min.y), pe::Vector2f(max.x, max.y) };

		if(not algo::compare(transform->rotation, 0.0f))
			for (auto &vertex : vertices) {
				// TODO: rotate points about transform->position
				vertex = algo::PointRotator(vertex, transform->rotation, transform->position);
			}

		return vertices;
	}

	pe::Vector2f BoxCollider::findSupportPoint(Transform* transform, pe::Vector2f direction) {
		std::vector<pe::Vector2f> vertices = this->getVertices(transform);

		float maxDotProduct = INT_MIN;
		pe::Vector2f supportPoint = vertices[0];

		for (auto& vertex : vertices) {
			float dotProduct = vertex.dot(direction);

			if (dotProduct > maxDotProduct) {
				maxDotProduct = dotProduct;
				supportPoint = vertex;
			}
		}

		return supportPoint;
	}

}