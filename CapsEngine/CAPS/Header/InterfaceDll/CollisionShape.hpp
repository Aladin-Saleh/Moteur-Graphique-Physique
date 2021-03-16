#ifndef __CAPS_INTERFACE_COLLISION_SHAPE__
#define __CAPS_INTERFACE_COLLISION_SHAPE__

#include "Vector3.hpp"

class CollisionShape
{
public:
	virtual void SetMass(float mass) = 0;
	virtual Vector3 GetInertia() const = 0;
	virtual float GetMass() const = 0;
	virtual CollisionShape * GetCollisionShape() = 0;
};

#endif // !__CAPS_INTERFACE_COLLISION_SHAPE__
