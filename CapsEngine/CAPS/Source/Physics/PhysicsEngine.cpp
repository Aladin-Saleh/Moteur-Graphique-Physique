#include "PhysicsEngine.hpp"

namespace Ge
{
	bool PhysicsEngine::Initialize(Vector3 gravity)
	{
		m_pCollisionCongifuration = new btDefaultCollisionConfiguration();
		m_pCollisionDispatcher = new btCollisionDispatcher(m_pCollisionCongifuration);
		m_pBroadphaseInterface = new btDbvtBroadphase();
		m_pSequentialConstraintSolver = new btSequentialImpulseConstraintSolver();

		m_pDynamicWorld = new btDiscreteDynamicsWorld(
			m_pCollisionDispatcher,
			m_pBroadphaseInterface,
			m_pSequentialConstraintSolver,
			m_pCollisionCongifuration);

		m_pDynamicWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
		m_gravity = gravity;
		Debug::Info("Initialisation du moteur physique");
		
		return true;
	}

	void PhysicsEngine::Update(float deltaTime)
	{
		m_pDynamicWorld->stepSimulation(deltaTime, 1);
	}

	void PhysicsEngine::Release()
	{
		for (CShape * cs : m_collisionShape)
		{
			delete(cs);
		}
		m_collisionShape.clear();
		m_mapCollisionShape.clear();
		for (RBody * rb : m_rigidBody)
		{
			m_pDynamicWorld->removeRigidBody(rb->GetBody());
			delete(rb);
		}
		m_rigidBody.clear();
		m_mapRigidBody.clear();
		delete(m_pCollisionCongifuration);
		delete(m_pCollisionDispatcher);
		delete(m_pBroadphaseInterface);
		delete(m_pSequentialConstraintSolver);
		delete(m_pDynamicWorld);
		Debug::Info("Liberation du moteur physique");
	}

	RigidBody * PhysicsEngine::AllocateRigidbody(CollisionShape * cShape, bool inertie, std::string name)
	{
		CShape * cs = m_mapCollisionShape[cShape];
		if (cs)
		{	
			RBody * rb = new RBody(m_pDynamicWorld, cs, cs->getIsInertieAvailable() ? inertie : false);
			m_rigidBody.push_back(rb);
			m_mapRigidBody[(RigidBody *)rb] = rb;
			rb->setName(name);
			rb->SetGravity(m_gravity);
			return rb;
		}
		Debug::Warn("AllocateRigidbody CollisionShape nullptr");
		return nullptr;
	}

	void PhysicsEngine::AddRigidbody(RigidBody * body)
	{
		RBody * rb = m_mapRigidBody[body];
		if (rb)
		{
			m_pDynamicWorld->addRigidBody(rb->GetBody());				
			return;
		}
		Debug::Warn("AddRigidbody nullptr rigidbody");
	}

	void PhysicsEngine::ReleaseRigidbody(RigidBody * pBody)
	{
		RBody * rb = m_mapRigidBody[pBody];
		if (pBody)
		{
			for (int i = 0; i < m_rigidBody.size(); i++)
			{
				if (m_rigidBody[i] == rb)
				{
					m_rigidBody.erase(m_rigidBody.begin() + i);
					m_mapRigidBody.erase(pBody);
					m_pDynamicWorld->removeRigidBody(rb->m_pBody);
					delete(rb);
					return;

				}
			}
		}
	}

	CollisionSphereShape * PhysicsEngine::CreateSphereCollisionShape(float radius, float mass)
	{
		CSphereShape * cs = new CSphereShape(radius, mass);
		m_collisionShape.push_back((CShape *)cs);
		m_mapCollisionShape[(CShape *)cs] = cs;
		return cs;
	}

	CollisionBoxShape * PhysicsEngine::CreateBoxCollisionShape(Vector3 halfExtends, float mass)
	{
		CBoxShape * cs = new CBoxShape(halfExtends, mass);
		m_collisionShape.push_back((CShape *)cs);
		m_mapCollisionShape[(CShape *)cs] = cs;
		return cs;
	}

	CollisionCapsuleShape * PhysicsEngine::CreateCapsuleCollisionShape(float radius, float height, float mass)
	{
		CCapsuleShape * cs = new CCapsuleShape(radius, height, mass);
		m_collisionShape.push_back((CShape *)cs);
		m_mapCollisionShape[(CShape *)cs] = cs;
		return cs;
	}

	CollisionVertexShape * PhysicsEngine::CreateVertexCollisionShape(ShapeBuffer * sb, float mass)
	{
		if (sb)
		{
			CVertexShape * cs = new CVertexShape(mass, sb);
			m_collisionShape.push_back((CShape *)cs);
			m_mapCollisionShape[(CShape *)cs] = cs;
			return cs;
		}
		Debug::Warn("CollisionVertexShape ShapeBuffer nullptr");
		return nullptr;
	}

	void PhysicsEngine::ReleaseCollisionShape(CollisionShape * cShape)
	{
		CShape * cs = m_mapCollisionShape[cShape];
		if (cShape)
		{
			for (int i = 0; i < m_collisionShape.size(); i++)
			{
				if (m_collisionShape[i] == cs)
				{
					m_collisionShape.erase(m_collisionShape.begin() + i);
					m_mapCollisionShape.erase(cShape);
					delete(cs);
					return;

				}
			}
		}
	}
	std::vector<RBody*> PhysicsEngine::getRigidBody()
	{
		return m_rigidBody;
	}
}