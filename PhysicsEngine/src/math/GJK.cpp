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

#include "math/GJK.hpp"
#include <iostream>

namespace pe {

// Calculates (ab X ac) X ab
Vector2f getPerpendicularVectorTowardsC(Vector2f a, Vector2f b, Vector2f c) {
	// b is the first point
	// a is the second point (the latest one)
	auto ab = b - a;
	auto ac = c - a;

	float abXac = (ab.x * ac.y - ab.y * ac.x);

	return Vector2f(-abXac * ab.y,
					 abXac * ab.x);
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
	Vector2f ao = -a;

	// Normal to ab side pointing outside triangle
	Vector2f normalAB = -getPerpendicularVectorTowardsC(a, b, c);

	// Normal to ac side pointing outside triangle
	Vector2f normalAC = -getPerpendicularVectorTowardsC(a, c, b);

	if (SameDirection(normalAB, ao))
		return Line(points = { a, b }, direction = normalAB);

	if (SameDirection(normalAC, ao))
		return Line(points = { a, c }, direction = normalAC);
		
	return true;
}

Vector2f minkiSupportPoint(Collider* colliderA, Transform* transformA, Collider* colliderB, Transform* transformB, Vector2f direction) {
	return colliderA->findSupportPoint(transformA, direction) -
		    colliderB->findSupportPoint(transformB, -direction) ;
}

bool NextSimplex(Simplex& points, Vector2f& direction) {
	// Line
	if (points.size() == 2)
		return Line(points, direction);

	// Triangle
	else
		return Triangle(points, direction);
}

// Expanding Polytope Algorithm
// \returns normal of the collision
Vector2f EPA(Simplex& simplex, Collider* colliderA, Transform* transformA,
	Collider* colliderB, Transform* transformB) {

	int minIndex = 0;
	float minDistance = FLT_MAX;
	Vector2f minNormal;
	std::vector<Vector2f> simplexPoints;

	// copying simplex points
	for (int i = 0; i < simplex.size(); i++)
		simplexPoints.push_back(simplex[i]);


	while (minDistance == FLT_MAX) {
		for (size_t i = 0; i < simplexPoints.size(); i++) {
			int j = (i + 1) % simplexPoints.size();

			Vector2f vertexI = simplexPoints[i];
			Vector2f vertexJ = simplexPoints[j];

			auto ij = vertexJ - vertexI;
			Vector2f normal = Vector2f(ij.y, -ij.x).normalize();
			float distance = normal.dot(vertexI);

			if (distance < 0) {
				distance *= -1;
				normal = normal * -1;
			}

			if (distance < minDistance) {
				minDistance = distance;
				minNormal = normal;
				minIndex = j;
			}
		}

		auto supportPoint = minkiSupportPoint(colliderA, transformA, colliderB, transformB, minNormal);
		float sDistance = minNormal.dot(supportPoint);

		// If we found a new support point in the direction of normal
		// We add it to the list and try again
		if (std::abs(sDistance - minDistance) > 0.001) {
			minDistance = FLT_MAX;
			simplexPoints.insert(simplexPoints.begin() + minIndex, supportPoint);
		}
	}

	return minNormal * (minDistance + 0.001f);
}

CollisionManifold GJK(Collider* colliderA, Transform* transformA, 
					  Collider* colliderB, Transform* transformB) {
	
	// Initial direction
	Vector2f direction(1, 0);

	auto supportPoint = minkiSupportPoint(colliderA, transformA, colliderB, transformB, direction);

	Simplex points;
	points.push_front(supportPoint);

	direction = -supportPoint;

	while (true) {
		direction = direction.normalize();
		supportPoint = minkiSupportPoint(colliderA, transformA, colliderB, transformB, direction);

		// Point doesn't passed the origin
		// No collision
		if (supportPoint.dot(direction) <= 0)
		{
			return CollisionManifold();
		}

		points.push_front(supportPoint);

		if (NextSimplex(points, direction)) {
			Vector2f collisionNormal = EPA(points, colliderA, transformA, colliderB, transformB);

			auto manifold = CollisionManifold(collisionNormal, 0);
			manifold.addCollisionPoint(Vector2f());
			manifold.addCollisionPoint(Vector2f());

			return manifold;
		}
	}	
}



}