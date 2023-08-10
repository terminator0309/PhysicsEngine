#pragma once

#include "Collider.hpp"
#include <vector>

namespace pe {

	/// <summary>
	/// Axis Aligned Bounding Box, doesn't rotates with the object
	/// </summary>
	class AABBCollider : public Collider {
		pe::Vector2f m_Size;     // width and height of the box

	public:
		AABBCollider(pe::Vector2f&, pe::Vector2f& );
		AABBCollider(float, float);

		pe::Vector2f getMin(Transform* );
		pe::Vector2f getMax(Transform* );
		std::vector<pe::Vector2f> getVertices(Transform*);

		std::string getName() ;
		pe::Vector2f findSupportPoint(Transform*, pe::Vector2f) ;
		CollisionManifold testCollision(Transform*, Collider*, Transform*) ;
		CollisionManifold testCollision(Transform*, CircleCollider*, Transform*) ;
		CollisionManifold testCollision(Transform*, BoxCollider*, Transform*) ;
	};
}