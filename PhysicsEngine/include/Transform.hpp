#pragma once

#include "Vector.hpp"

namespace pe {
    class Transform {
    public:
        pe::Vector2f position;
        float rotation;

        Transform(pe::Vector2f );
    };
}