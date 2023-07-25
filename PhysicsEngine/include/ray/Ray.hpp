#pragma once

#include "Vector.hpp"

namespace pe {
	class Ray {
		pe::Vector2f m_Origin;
		pe::Vector2f m_Direction;

	public:
		Ray(pe::Vector2f origin, pe::Vector2f direction);

		pe::Vector2f getOrigin();
		pe::Vector2f getDirection();
	};
}