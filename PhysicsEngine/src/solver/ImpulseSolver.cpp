#include "solver/ImpulseSolver.hpp"
#include "Algo.hpp"

#include <iostream>

namespace pe {
	void ImpulseSolver::solve(std::vector<Collision>& collisions) {
        for (auto& collision : collisions) {
            seperateCollidingObjects(collision);
			this->solveCollisionWithRotation(collision);
        }
	}

    void ImpulseSolver::seperateCollidingObjects(Collision& collision) {
        Object* a = collision.obj_a;
        Object* b = collision.obj_b;
        auto normal = collision.manifold.getNormal();

        float depth = normal.length();
        auto unitNormal = normal.normalize();

        auto seperationNormal = unitNormal * depth;

        if (a->getStatic()) {
            b->transform->position += seperationNormal;
        }
        else if (b->getStatic()) {
            a->transform->position -= seperationNormal;
        }
        else {
            a->transform->position -= normal / 2;
            b->transform->position += normal / 2;
        }
    }

	void ImpulseSolver::solveCollision(Collision& collision) {

        auto a = collision.obj_a;
        auto b = collision.obj_b;
        auto m = &collision.manifold;

        float inverseMassA = a->getInverseMass();
        float inverseMassB = b->getInverseMass();
        float inverseMassSum = inverseMassA + inverseMassB;

        float corA = a->cor;
        float corB = b->cor;

        if (inverseMassSum == 0.0f)
            return;

        auto relativeVelocity = b->velocity - a->velocity;
        auto relativeNormal = m->getNormal().normalize();

        // Moving away from each other, do nothing
        if (relativeVelocity.dot(relativeNormal) > 0.0f)
            return;

        float minCor = std::min(corA, corB);
        float numerator = -(1 + minCor) * relativeVelocity.dot(relativeNormal);
        float j = numerator / inverseMassSum;

        //if (m->getCollisionPoints().size() > 0 and j != 0.0f)
            //j /= (float)m->getCollisionPoints().size();

        auto impulse = relativeNormal * j;

        a->velocity += impulse * inverseMassA * -1;
        b->velocity += impulse * inverseMassB * 1;
	}

    void ImpulseSolver::solveCollisionWithRotation(Collision& collision) {
        Object* a = collision.obj_a;
        Object* b = collision.obj_b;
        auto normal = collision.manifold.getNormal().normalize();
        auto contactPoints = collision.manifold.getCollisionPoints();

        auto positionA = a->getPosition();
        auto positionB = b->getPosition();

        auto inverseMassA = a->getInverseMass();
        auto inverseMassB = b->getInverseMass();

        auto inverseInertiaA = a->getInverseInertia();
        auto inverseInertiaB = b->getInverseInertia();

        float e = std::min(a->cor, b->cor);

        Vector2f impulses[2];

        for (size_t i = 0; i < contactPoints.size(); i++) {
            Vector2f ra = contactPoints[i] - positionA;
            Vector2f rb = contactPoints[i] - positionB;
            
            // ra and rb perpendicular
            auto ra_L = Vector2f(-ra.y, ra.x);
            auto rb_L = Vector2f(-rb.y, rb.x);

            auto angularLinearVelA = ra_L * algo::degreeToRadian(a->angularVelocity);
            auto angularLinearVelB = rb_L * algo::degreeToRadian(b->angularVelocity);

            auto relativeVel = (b->velocity + angularLinearVelB) -
                               (a->velocity + angularLinearVelA);

            auto contactVelocityMag = relativeVel.dot(normal);

            if (contactVelocityMag > 0.0f)
                continue;

            float numerator = -(1 + e) * contactVelocityMag;
            float denominator = (inverseMassA + inverseMassB) +
                                ra_L.dot(normal) * ra_L.dot(normal) * inverseInertiaA +
                                rb_L.dot(normal) * rb_L.dot(normal) * inverseInertiaB;

            float j = numerator / denominator;
            j /= (float)contactPoints.size();


            auto impulse = normal * j;
            impulses[i] = impulse;
        }

        for (size_t i = 0; i < contactPoints.size(); i++) {
            auto impulse = impulses[i];

            Vector2f ra = contactPoints[i] - positionA;
            Vector2f rb = contactPoints[i] - positionB;

            a->velocity += -impulse * inverseMassA;
            b->velocity += impulse * inverseMassB;

            a->angularVelocity += algo::radianToDegree( - ra.cross(impulse) * inverseInertiaA);
            b->angularVelocity += algo::radianToDegree(rb.cross(impulse) * inverseInertiaB);

        }
    }

}