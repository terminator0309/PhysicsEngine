#pragma once

#include "Util.hpp"

namespace game {
    namespace util {
        sf::Vector2f convert(pe::Vector2f& other) {
            return sf::Vector2f(other._x, other._y);
        }
    }
}