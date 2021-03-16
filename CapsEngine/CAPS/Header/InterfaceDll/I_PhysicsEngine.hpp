#ifndef __CAPS_INTERFACE_PHYSICS_ENGINE__
#define __CAPS_INTERFACE_PHYSICS_ENGINE__

#include "CollisionShape.hpp"
#include "CollisionBoxShape.hpp"
#include "CollisionSphereShape.hpp"
#include "CollisionCapsuleShape.hpp"
#include "CollisionVertexShape.hpp"
#include "RigidBody.hpp"
#include "Vector3.hpp"

class I_PhysicsEngine
{
public:
	virtual RigidBody * AllocateRigidbody(CollisionShape * cShape, bool hasInertia = true, std::string name = "RigidBody") = 0;
	virtual void AddRigidbody(RigidBody* body) = 0;
	virtual void ReleaseRigidbody(RigidBody * pBody) = 0;
	virtual CollisionBoxShape * CreateBoxCollisionShape(Vector3 halfExtends, float mass) = 0;
	virtual CollisionSphereShape * CreateSphereCollisionShape(float radius, float mass) = 0;
	virtual CollisionCapsuleShape * CreateCapsuleCollisionShape(float radius, float height, float mass) = 0;
	virtual CollisionVertexShape * CreateVertexCollisionShape(ShapeBuffer * sb, float mass) = 0;
	virtual void ReleaseCollisionShape(CollisionShape * cShape) = 0;
};

#endif //!__CAPS_INTERFACE_PHYSICS_ENGINE__