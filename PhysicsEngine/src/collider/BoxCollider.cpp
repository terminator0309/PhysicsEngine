#include "collider/BoxCollider.hpp"
#include "Algo.hpp"
#include "math/GJK.hpp"

namespace pe {

	BoxCollider::BoxCollider(pe::Vector2f& min, pe::Vector2f& max) {
		m_Size = max - min;
		std::cout << "Object created of type: " << this->getName() << std::endl;
	}

	pe::Vector2f BoxCollider::getMin(Transform* transform) {
		return transform->position - (m_Size * 0.5f);
	}

	pe::Vector2f BoxCollider::getMax(Transform* transform) {
		return transform->position + (m_Size * 0.5f);
	}

	std::vector<pe::Vector2f> BoxCollider::getVertices(Transform* transform) {
		pe::Vector2f min = getMin(transform);
		pe::Vector2f max = getMax(transform);

		std::vector<pe::Vector2f> vertices = { pe::Vector2f(min.x, min.y), pe::Vector2f(min.x, max.y),
											   pe::Vector2f(max.x, max.y), pe::Vector2f(max.x, min.y) };

		if(not algo::compare(transform->rotation, 0.0f))
			for (auto &vertex : vertices) {
				vertex = algo::PointRotator(vertex, transform->rotation, transform->position);
			}

		return vertices;
	}

	pe::Vector2f BoxCollider::findSupportPoint(Transform* transform, pe::Vector2f direction) {
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

	CollisionManifold BoxCollider::testCollision(Transform* transform, Collider* otherCollider, Transform* otherTransform) {
		return otherCollider->testCollision(otherTransform, this, transform);
	}

	CollisionManifold BoxCollider::testCollision(Transform* transform, CircleCollider* otherCollider, Transform* otherTransform) {
		auto manifold = pe::GJK(otherCollider, otherTransform, this, transform);

		if (manifold.getIsColliding()) {
			auto point = algo::findContactPoints(otherCollider, otherTransform, this, transform)[0];
			manifold.addCollisionPoint(point);
		}

		return manifold;
	}

	CollisionManifold BoxCollider::testCollision(Transform* transform, BoxCollider* otherCollider, Transform* otherTransform) {
		auto manifold = pe::GJK(otherCollider, otherTransform, this, transform);

		if (manifold.getIsColliding()) {
			auto points = algo::findContactPoints(otherCollider, otherTransform, this, transform);

			for(auto& point: points)
				manifold.addCollisionPoint(point);
		}

		return manifold;
	}

	std::string BoxCollider::getName() {
		return "BOX";
	}

}