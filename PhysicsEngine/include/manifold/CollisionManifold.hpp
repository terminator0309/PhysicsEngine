#pragma once

#include <vector>

#include "Vector.hpp"

namespace pe {
	class CollisionManifold {
		pe::Vector2f normal;
		std::vector<pe::Vector2f> collisionPoints;
		float depth;
		bool isColliding;

	public:
		CollisionManifold();

		CollisionManifold(pe::Vector2f , float );

		CollisionManifold(const CollisionManifold& otherManifold);

		pe::Vector2f getNormal();

		std::vector<pe::Vector2f> getCollisionPoints();
		
		float getDepth();
		
		bool getIsColliding();
		
		void addCollisionPoint(pe::Vector2f);

	};
}