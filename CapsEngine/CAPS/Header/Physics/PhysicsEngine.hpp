#ifndef __CAPS_PHYSICS_ENGINE__
#define __CAPS_PHYSICS_ENGINE__

//#include "Bullet3/src/btBulletDynamicsCommon.h"
#include "btBulletDynamicsCommon.h"
#include "Debug.hpp"
#include "RBody.hpp"
#include <vector>
#include "CBoxShape.hpp"
#include "CSphereShape.hpp"
#include "CCapsuleShape.hpp"
#include "CVertexShape.hpp"
#include "I_PhysicsEngine.hpp"
#include <map>

namespace Ge
{
	class PhysicsEngine : public I_PhysicsEngine
	{
	private:
		friend class GameEngine;
		bool Initialize(Vector3 gravity);
		void Update(float deltaTime);
		void Release();
	public:		
		RigidBody * AllocateRigidbody(CollisionShape * cShape, bool hasInertia = true, std::string name = "RigidBody");
		void AddRigidbody(RigidBody* body);
		void ReleaseRigidbody(RigidBody * pBody);
		CollisionSphereShape * CreateSphereCollisionShape(float radius, float mass);
		CollisionBoxShape * CreateBoxCollisionShape(Vector3 halfExtends, float mass);
		CollisionCapsuleShape * CreateCapsuleCollisionShape(float radius, float height, float mass);
		CollisionVertexShape * CreateVertexCollisionShape(ShapeBuffer * sb, float mass);
		void ReleaseCollisionShape(CollisionShape * cShape);
		std::vector<RBody *> getRigidBody();
	private:
		btDynamicsWorld * m_pDynamicWorld;
		btBroadphaseInterface * m_pBroadphaseInterface;
		btCollisionDispatcher * m_pCollisionDispatcher;
		btDefaultCollisionConfiguration * m_pCollisionCongifuration;
		btSequentialImpulseConstraintSolver * m_pSequentialConstraintSolver;
		std::vector<RBody *> m_rigidBody;
		std::vector<CShape *> m_collisionShape;
		std::map<RigidBody *, RBody *> m_mapRigidBody;
		std::map<CollisionShape*, CShape *> m_mapCollisionShape;
		Vector3 m_gravity;
	};
}

#endif //!__CAPS_PHYSICS_ENGINE__