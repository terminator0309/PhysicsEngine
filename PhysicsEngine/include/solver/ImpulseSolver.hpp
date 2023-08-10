#pragma once

#include "Solver.hpp"

namespace pe {
	class ImpulseSolver : public Solver {
	public:
		void solve(std::vector<Collision>&) override;

	private:
		void seperateCollidingObjects(Object* a, Object* b, pe::Vector2f normal);
		void solveCollision(Collision&);
	};
}