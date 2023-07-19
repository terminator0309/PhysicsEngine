#pragma once

#include <vector>

#include "Collision.hpp"

namespace pe {
    class Solver {
        public:
        // only solves circle-circle collisions for now
            void solve(Collision* );

            void solve(std::vector<Collision>& );
    };
}