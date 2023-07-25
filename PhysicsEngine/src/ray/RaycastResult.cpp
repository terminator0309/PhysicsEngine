#include "ray/RaycastResult.hpp"

namespace pe {
	RaycastResult::RaycastResult() {
		m_T = -1;
		m_Hit = false;
	}

	void RaycastResult::init(pe::Vector2f point, pe::Vector2f normal, float t, bool hit) {
		m_Point = point;
		m_Normal = normal;
		m_T = t;
		m_Hit = hit;
	}

	void RaycastResult::reset(RaycastResult& result) {
		result = RaycastResult::RaycastResult();
	}

}