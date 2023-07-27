/*
* 
* GJK (Gilbert Johnson Keerthi) algorithm
*  - checks whether two convex shapes collide
* 
* 
* STEP 1: Minkowski SUM / DIFF
*	A and B = { a +/- b | a E A, b E B}
*	Taking every possible point of A and adding it to B
* 
*	If we take Minkowski diff of two shapes then the resultant shape 
*	must contain origin in it.
* 
*	The Resultant shape will also be convex if subtracted shapes where convex.
* 
* 
* STEP 2: Finding the triangle(SIMPLEX) that encloses the origin
*	SIMPLEX: shape that is guaranteed to enclose a point in k-dimensional space
* 
*	Step 2.1: Selecting points to create the simplex
*		A support function will map direction to point on the shape
*		Summing up the two support of the shape gives support point on the minkowski shape.
*		
*		SUPPORT POINT FOR CIRCLE
*			Always be the direction vector multiplied by the radius and shifted with the center
*			s(d->) = C + r * d->
*		
*		SUPPORT POINT FOR POLYGONS
*			support point can be found by iterating through all the vertices of polygon and 
*			performing a dot product with the direction,
*			vertex with highest dot product is the furthest point in the direction.
* 
*			for all vertex in vertices:
*				find max vertex . (d->)
* 
*		Step 2.1.1: Selecting direction to compute support point and then later on simplex
*			Start with a random direction and find the support point
*			
*			Next direction will be towards the origin from the first support point we previously foudn
*			
*			We check whether this new point is past the origin, if not shape do not collide
*			
*			Third direction we choose will be the normal to the line formed by 
*			the previous two points in the direction of origin (selecting the normal which is facing the origin)
*			
*	
* 
*	QUESTIONs TO BE ANSWERED:
*		how do we know if a point "passed" the origin?
*		how do we know the next direction once we have two points?
*		how do we check if our triangle contains the origins?
*		how do we pick a new direction if triangle doesn't contains the origin?
* 
*		
*		First ans: check dot product from origin to new point, if dot product is < zero, we are not passed the origin
*		
*		Second ans: vector triple product, lets say we have a line AB, (AB-> X AO->) X AB->, gives us the vector
*			pointing in the direction of origin
* 
*		Third and fourth ans: voronai regions, origin can be in Rab, Rabc, Rac region only, check by eliminating Rab and Rac
*			If the Rab contains the origin, we find the next support point in this direction
* 
*/

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

// Calculates (ab X ac) X ab
Vector2f getPerpendicularVectorTowardsC(Vector2f a, Vector2f b, Vector2f c) {
	// b is the first point
	// a is the second point (the latest one)
	auto ab = b - a;
	auto ac = c - a;

	float abXac = (ab._x * ac._y - ab._y * ac._x);

	return Vector2f(-abXac * ab._y,
					 abXac * ab._x);
}

bool SameDirection(Vector2f& direction, Vector2f& a) {
	return direction.dot(a) > 0;
}

bool Line(Simplex& points, Vector2f& direction) {
	Vector2f a = points[0];
	Vector2f b = points[1];

	Vector2f ab = b - a;
	Vector2f ao = -a;

	// 'a' point made passed the origin
	if (SameDirection(ab, ao))
		direction = getPerpendicularVectorTowardsC(a, b, Vector2f::ORIGIN);

	else {
	// If not in same direction, and this is furthest we can go
	// since direction is now 'ao' and furthest point in this direction 
	// is 'a', we will repeat the same point and supportPoint vector
	// will have -ve dot product with the direction
		points = { a };
		direction = ao;
	}

	return false;
}

bool Triangle(Simplex& points, Vector2f& direction) {
	Vector2f a = points[0];
	Vector2f b = points[1];
	Vector2f c = points[2];

	Vector2f ab = b - a;
	Vector2f ac = c - a;

	// Normal to ab side pointing outside triangle
	Vector2f normalAB = -getPerpendicularVectorTowardsC(a, b, c);

	// Normal to ac side pointing outside triangle
	Vector2f normalAC = -getPerpendicularVectorTowardsC(a, c, b);

	if (SameDirection(normalAB, Vector2f::ORIGIN))
		return Line(points = { a, b }, direction = normalAB);
	if (SameDirection(normalAC, Vector2f::ORIGIN))
		return Line(points = { a, c }, direction = normalAC);
		
	return true;
}

Vector2f minkiSupportPoint(Collider* colliderA, Transform* transformA, Collider* colliderB, Transform* transformB, Vector2f direction) {
	return colliderA->findSupportPoint(transformA, direction)
		   - colliderB->findSupportPoint(transformB, -direction);
}

bool NextSimples(Simplex& points, Vector2f& direction) {
	// Line
	if (points.size() == 2)
		return Line(points, direction);

	// Triangle
	else
		return Triangle(points, direction);
}

bool GJK(Collider* colliderA, Transform* transformA, Collider* colliderB, Transform* transformB) {

	// Initial direction
	Vector2f direction(1, 0);

	Vector2f supportPoint = minkiSupportPoint(colliderA, transformA, colliderB, transformB, direction);
	
	Simplex points;
	points.push_front(supportPoint);

	direction = -supportPoint;

	while (true) {
		supportPoint = minkiSupportPoint(colliderA, transformA, colliderB, transformB, direction);

		// Point doesn't passed the origin
		// No collision
		if (supportPoint.dot(direction) <= 0)
			return false;

		points.push_front(supportPoint);

		if (NextSimples(points, direction))
			return true;
	}	
	
}

}