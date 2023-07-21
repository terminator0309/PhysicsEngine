#include "collider/AABBCollider.hpp"

namespace pe {

	/// <summary>
	/// Creates a AABBCollider which covers a rectangle from min point to max point
	/// </summary>
	/// <param name="min">Top-left coordinates of AABB box</param>
	/// <param name="max">Bottom-right coordinates of AABB box</param>
	AABBCollider::AABBCollider(pe::Vector2f& min, pe::Vector2f& max) {
		m_Size = max - min;
	}

	pe::Vector2f AABBCollider::getMin(Transform* transform) {
		return transform->position - (m_Size * 0.5f);
	}

	pe::Vector2f AABBCollider::getMax(Transform* transform) {
		return transform->position + (m_Size * 0.5f);
	}
}