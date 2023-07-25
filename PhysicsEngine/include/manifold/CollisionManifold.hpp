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

		pe::Vector2f getNormal();

		std::vector<pe::Vector2f> getCollisionPoints();
		
		pe::Vector2f getDepth();
		
		bool getIsColliding();
		
		void addCollisionPoint(pe::Vector2f);
	};
}