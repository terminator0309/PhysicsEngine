#include "collider/LineCollider.hpp"

namespace pe {
	LineCollider::LineCollider(pe::Vector2f start, pe::Vector2f end) {
		m_Start = start;
		m_End = end;
	}

	pe::Vector2f LineCollider::getStart() {
		return m_Start;
	}

	pe::Vector2f LineCollider::getEnd() {
		return m_End;
	}
}

