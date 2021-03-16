#ifndef __CAPS_COLLISION_SPHERE_SHAPE__
#define __CAPS_COLLISION_SPHERE_SHAPE__

#include "CollisionSphereShape.hpp"
#include "CShape.hpp"

namespace Ge
{
	class CSphereShape : public CShape, public CollisionSphereShape
	{
	public:
		CSphereShape(float radius, float mass);
	protected:
		float m_radius;
	};
}

#endif //!__CAPS_COLLISION_SPHERE_SHAPE__