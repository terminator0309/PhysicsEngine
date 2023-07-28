#pragma once

#include "collider/Collider.hpp"

#include <array>


namespace pe {
	class Simplex {
	private:
		std::array<Vector2f, 3> m_points;
		int m_size;

	public:
		Simplex()
			: m_points({ 0,0,0 })
			, m_size(0)
		{};

		Simplex& operator=(std::initializer_list<Vector2f> list) {
			for (auto v = list.begin(); v != list.end(); v++)
				m_points[std::distance(list.begin(), v)] = *v;

			m_size = list.size();

			return *this;
		}

		void push_front(Vector2f point) {
			m_points = { point, m_points[0], m_points[1] };
			m_size = std::min(m_size + 1, 3);
		}

		Vector2f& operator[](int i) {
			return m_points[i];
		}

		int size() {
			return m_size;
		}
	};


	/*
	// Calculates (ab X ac) X ab
	Vector2f getPerpendicularVectorTowardsC(Vector2f a, Vector2f b, Vector2f c);
	bool SameDirection(Vector2f& direction, Vector2f& a);
	bool Line(Simplex& points, Vector2f& direction);
	bool Triangle(Simplex& points, Vector2f& direction);
	Vector2f minkiSupportPoint(Collider* colliderA, Transform* transformA, Collider* colliderB, Transform* transformB, Vector2f direction);
	bool NextSimples(Simplex& points, Vector2f& direction);
	*/
	CollisionManifold GJK(Collider* colliderA, Transform* transformA, Collider* colliderB, Transform* transformB);

}