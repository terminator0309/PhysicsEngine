#include "Transform.hpp"

namespace pe {
	Transform::Transform(pe::Vector2f p) : position(p), rotation(0) {}
	Transform::Transform(pe::Vector2f p, float r) : position(p), rotation(r) {}
}