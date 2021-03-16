#include "CBoxShape.hpp"

namespace Ge
{
	CBoxShape::CBoxShape(Vector3 halfExtents, float mass) : CShape(mass)
	{
		m_halfExtents = halfExtents;
		m_pShape = new btBoxShape(btVector3(halfExtents.x, halfExtents.y, halfExtents.z));
	}
}