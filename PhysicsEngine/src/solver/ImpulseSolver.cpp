#include "solver/ImpulseSolver.hpp"

namespace pe {
	void ImpulseSolver::solve(std::vector<Collision>& collisions) {
		for (auto& collision : collisions)
			this->solveCollision(collision);
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

        if (m->getCollisionPoints().size() > 0 and j != 0.0f)
            j /= (float)m->getCollisionPoints().size();

        auto impulse = relativeNormal * j;

        a->velocity += impulse * inverseMassA * -1;
        b->velocity += impulse * inverseMassB * 1;
	}

}