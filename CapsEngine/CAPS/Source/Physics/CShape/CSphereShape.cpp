#include "CSphereShape.hpp"

namespace Ge
{
	CSphereShape::CSphereShape(float radius, float mass) : CShape(mass)
	{
		m_radius = radius;
		m_pShape = new btSphereShape(m_radius);
	}
}
