#ifndef __CAPS_INTERFACE_RIGID_BODY__
#define __CAPS_INTERFACE_RIGID_BODY__

#include "CollisionBoxShape.hpp"
#include "Vector4.hpp"
#include "GraphicsObject.hpp"

class RigidBody : public virtual GraphicsObject
{
public:
	virtual void Translate(Vector3 translate) = 0;
	virtual void SetMass(float mass) = 0;
	virtual void SetGravity(Vector3 gravity) = 0;
	virtual void SetRestitution(float coef) = 0;
	virtual void SetLinearVelocity(Vector3 velocity) = 0;
	virtual Vector3 GetLinearVelocity() = 0;
	virtual void SetSleepingThreshold(float linear, float angular) = 0;
	virtual void ApplyImpulse(Vector3 impulse, Vector3 real_pos) = 0;
	virtual void SetActiveCollision(bool activeCol) =  0;
	virtual bool GetActiveCollision() const = 0;
	virtual void forceActivationState(int newState) = 0;
};

#endif //!__CAPS_INTERFACE_RIGID_BODY__