#include "collider/AABBCollider.hpp"
#include "math/GJK.hpp"
#include "collider/CircleCollider.hpp"

namespace pe {

	/// <summary>
	/// Creates a AABBCollider which covers a rectangle from min point to max point
	/// </summary>
	/// <param name="min">Top-left coordinates of AABB box</param>
	/// <param name="max">Bottom-right coordinates of AABB box</param>
	AABBCollider::AABBCollider(pe::Vector2f& min, pe::Vector2f& max) {
		m_Size = max - min;
	}

	AABBCollider::AABBCollider(float width, float height) {
		m_Size = Vector2f(width, height);
	}

	pe::Vector2f AABBCollider::getMin(Transform* transform) {
		return transform->position - (m_Size * 0.5f);
	}

	pe::Vector2f AABBCollider::getMax(Transform* transform) {
		return transform->position + (m_Size * 0.5f);
	}

	std::vector<pe::Vector2f> AABBCollider::getVertices(Transform* transform) {
		pe::Vector2f min = getMin(transform);
		pe::Vector2f max = getMax(transform);

		std::vector<pe::Vector2f> vertices = { pe::Vector2f(min.x, min.y), pe::Vector2f(min.x, max.y),
											   pe::Vector2f(max.x, min.y), pe::Vector2f(max.x, max.y) };

		return vertices;
	}

	pe::Vector2f AABBCollider::findSupportPoint(Transform* transform, pe::Vector2f direction) {
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

	CollisionManifold AABBCollider::testCollision(Transform* transform, Collider* otherCollider, Transform* otherTransform) {
		return otherCollider->testCollision(otherTransform, this, transform);
	}

	CollisionManifold AABBCollider::testCollision(Transform* transform, CircleCollider* otherCollider, Transform* otherTransform) {
		return pe::GJK(otherCollider, otherTransform, this, transform);
	}

	CollisionManifold AABBCollider::testCollision(Transform* transform, AABBCollider* otherCollider, Transform* otherTransform) {
		return pe::GJK(otherCollider, otherTransform, this, transform);
	}

	std::string AABBCollider::getName() {
		return "AABB";
	}
}