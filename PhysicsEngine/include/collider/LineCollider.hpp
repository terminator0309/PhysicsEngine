#pragma once

#include "Collider.hpp"

namespace pe {
	class LineCollider {
		pe::Vector2f m_Start;
		pe::Vector2f m_End;

	public:
		LineCollider(pe::Vector2f, pe::Vector2f);
		pe::Vector2f getStart();
		pe::Vector2f getEnd();
	};
}