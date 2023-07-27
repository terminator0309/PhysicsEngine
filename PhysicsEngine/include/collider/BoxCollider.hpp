#pragma once

#include "Collider.hpp"

#include <vector>

namespace pe {
	
	/// <summary>
	/// Oriented bounding box, does rotates with the object
	/// </summary>
	class BoxCollider {
		pe::Vector2f m_Size;

	public:
		BoxCollider(pe::Vector2f&, pe::Vector2f&);
		
		pe::Vector2f getMin(Transform*);
		
		pe::Vector2f getMax(Transform*);
		
		std::vector<pe::Vector2f> getVertices(Transform* );

		pe::Vector2f findSupportPoint(Transform* , pe::Vector2f );
	};
}