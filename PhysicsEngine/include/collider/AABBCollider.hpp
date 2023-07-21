#pragma once

#include "Collider.hpp"

namespace pe {

	/// <summary>
	/// Axis Aligned Bounding Box, doesn't rotates with the object
	/// </summary>
	class AABBCollider {
		pe::Vector2f m_Size;     // width and height of the box

	public:
		AABBCollider(pe::Vector2f&, pe::Vector2f& );
		pe::Vector2f getMin(Transform* );
		pe::Vector2f getMax(Transform* );
	};
}