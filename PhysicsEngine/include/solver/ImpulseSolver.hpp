#pragma once

#include "Solver.hpp"

namespace pe {
	class ImpulseSolver : public Solver {
	public:
		void solve(std::vector<Collision>&) override;

	private:
		void seperateCollidingObjects(Collision& );
		void solveCollision(Collision&);
		void solveCollisionWithRotation(Collision& );
	};
}