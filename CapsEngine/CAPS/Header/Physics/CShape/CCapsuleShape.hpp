#ifndef __CAPS_COLLISION_CAPSULE_SHAPE__
#define __CAPS_COLLISION_CAPSULE_SHAPE__

#include "CollisionCapsuleShape.hpp"
#include "CShape.hpp"
namespace Ge
{
	class CCapsuleShape : public CShape, public CollisionCapsuleShape
	{
	public:
		CCapsuleShape(float radius, float height, float mass);
	protected:
		float m_radius;
		float m_height;
	};
}

#endif //!__CAPS_COLLISION_CAPSULE_SHAPE__