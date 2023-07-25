#include "manifold/CollisionManifold.hpp"

namespace pe {
	CollisionManifold::CollisionManifold() {
		depth = 0;
		isColliding = false;
	}

	CollisionManifold::CollisionManifold(pe::Vector2f normal, float depth)
	{
		this->normal = normal;
		this->depth = depth;
		this->isColliding = true;
	}

	std::vector<pe::Vector2f> CollisionManifold::getCollisionPoints() {
		return collisionPoints;
	}

	void CollisionManifold::addCollisionPoint(pe::Vector2f point) {
		collisionPoints.push_back(point);
	}

	pe::Vector2f CollisionManifold::getNormal() {
		return normal;
	}

	pe::Vector2f CollisionManifold::getDepth() {
		return depth;
	}

	bool CollisionManifold::getIsColliding() {
		return isColliding;
	}
}