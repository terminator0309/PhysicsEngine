#pragma once

#include "Vector.hpp"

namespace pe {
	class RaycastResult {
		pe::Vector2f m_Point;
		pe::Vector2f m_Normal;
		float m_T;
		bool m_Hit;

	public:
		RaycastResult();
		void init(pe::Vector2f point, pe::Vector2f normal, float t, bool hit);
		static void reset(RaycastResult& result);
	};
}