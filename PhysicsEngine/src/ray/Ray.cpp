#include "ray/Ray.hpp"

namespace pe {
	Ray::Ray(pe::Vector2f origin, pe::Vector2f direction) {
		m_Origin = origin;
		m_Direction = direction.normalize();
	}

	pe::Vector2f Ray::getOrigin() {
		return m_Origin;
	}

	pe::Vector2f Ray::getDirection() {
		return m_Direction;
	}
}