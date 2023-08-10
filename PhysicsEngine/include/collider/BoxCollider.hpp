#pragma once

#include "Collider.hpp"

#include <vector>

namespace pe {
	
	/// <summary>
	/// Oriented bounding box, does rotates with the object
	/// </summary>
	class BoxCollider : public Collider{
		pe::Vector2f m_Size;

	public:
		BoxCollider(pe::Vector2f&, pe::Vector2f&);
		
		pe::Vector2f getMin(Transform*);
		
		pe::Vector2f getMax(Transform*);

		std::string getName() override;
		
		std::vector<pe::Vector2f> getVertices(Transform* );

		pe::Vector2f findSupportPoint(Transform* , pe::Vector2f );

		CollisionManifold testCollision(Transform* transform, Collider* otherCollider, Transform* otherTransform) override;
		CollisionManifold testCollision(Transform* transform, CircleCollider* otherCollider, Transform* otherTransform) override;
		CollisionManifold testCollision(Transform* transform, BoxCollider* otherCollider, Transform* otherTransform) override;

	};
}