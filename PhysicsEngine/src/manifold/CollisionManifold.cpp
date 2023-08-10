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
		this->collisionPoints.clear();
	}

	CollisionManifold::CollisionManifold(const CollisionManifold& otherManifold) {
		this->normal = otherManifold.normal;
		this->depth = otherManifold.depth;
		this->isColliding = otherManifold.isColliding;

		if (otherManifold.collisionPoints.size() == 0)
			return;

		for (auto point : otherManifold.collisionPoints) {
			this->addCollisionPoint(point);
		}
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

	float CollisionManifold::getDepth() {
		return depth;
	}

	bool CollisionManifold::getIsColliding() {
		return isColliding;
	}
}