#include "CCapsuleShape.hpp"

namespace Ge
{
	CCapsuleShape::CCapsuleShape(float radius, float height, float mass) : CShape(mass)
	{
		m_height = height;
		m_radius = radius;
		m_pShape = new btCapsuleShape(radius, height);
	}
}
