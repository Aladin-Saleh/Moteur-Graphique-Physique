#include "RBody.hpp"

namespace Ge
{
	RBody::RBody(btDynamicsWorld* world, CShape * cshape, bool inertie) : GObject()
	{
		m_pWorld = world;
		m_pShape = cshape;
		m_pMotionState = new btDefaultMotionState();

		Vector3 inertia;
		if (inertie)
		{
			inertia = m_pShape->GetInertia();
		}

		m_pBody = new btRigidBody(m_pShape->GetMass(), m_pMotionState, m_pShape->GetShape(), btVector3(inertia.x, inertia.y, inertia.z));
	}

	void RBody::Translate(Vector3 translate)
	{
		m_pBody->translate(btVector3(translate.x, translate.y, translate.z));
	}

	void RBody::setPosition(Vector3 pos)
	{
		GObject::setPosition(pos);
		btTransform initialTransform;
		btQuaternion rotation = m_pBody->getWorldTransform().getRotation();

		initialTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
		initialTransform.setRotation(rotation);

		m_pBody->setWorldTransform(initialTransform);
		m_pMotionState->setWorldTransform(initialTransform);
	}

	void RBody::setRotation(Vector4 rot)
	{
		GObject::setRotation(rot);
		btTransform initialTransform;
		btVector3   position = m_pBody->getWorldTransform().getOrigin();

		initialTransform.setOrigin(position);
		initialTransform.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));

		m_pBody->setWorldTransform(initialTransform);
		m_pMotionState->setWorldTransform(initialTransform);
	}

	Vector4 RBody::getRotation()
	{
		btQuaternion rotation = m_pBody->getWorldTransform().getRotation();
		GObject::setRotation(Vector4(rotation.x(), rotation.y(), rotation.z(), rotation.w()));
		return m_transform.rot;
	}

	void RBody::setEulerAngles(Vector3 eul)
	{
		GObject::setEulerAngles(eul);
		btTransform initialTransform;
		Vector4 rotation = ConversionAngle::FromEulerDeg(eul);

		initialTransform.setOrigin(m_pBody->getWorldTransform().getOrigin());
		initialTransform.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));

		m_pBody->setWorldTransform(initialTransform);
		m_pMotionState->setWorldTransform(initialTransform);
	}

	Vector3 RBody::getEulerAngles()
	{	
		btQuaternion rotation = m_pBody->getWorldTransform().getRotation();
		GObject::setEulerAngles(ConversionAngle::ToEulerDeg(Vector4(rotation.x(), rotation.y(), rotation.z(), rotation.w())));
		return m_transform.eul;
	}


	void RBody::SetMass(float mass)
	{
		if (m_pShape)
		{
			m_pShape->SetMass(mass);
			Vector3 inertia = m_pShape->GetInertia();
			m_pBody->setMassProps(mass, btVector3(inertia.x, inertia.y, inertia.z));
		}
	}

	void RBody::SetGravity(Vector3 gravity)
	{
		m_pBody->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
		m_gravity[0] = gravity.x;
		m_gravity[1] = gravity.x;
		m_gravity[2] = gravity.x;
	}

	void RBody::SetRestitution(float coef)
	{
		m_pBody->setRestitution(coef);
	}

	void RBody::SetLinearVelocity(Vector3 velocity)
	{
		m_pBody->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
	}

	Vector3 RBody::GetLinearVelocity()
	{
		btVector3 vel = m_pBody->getLinearVelocity();
		return Vector3(vel.x(), vel.y(), vel.z());
	}

	Vector3 RBody::getPosition()
	{
		btVector3 pos = m_pBody->getWorldTransform().getOrigin();
		GObject::setPosition(Vector3(pos.x(), pos.y(), pos.z()));
		return m_transform.pos;;
	}

	void RBody::ApplyImpulse(Vector3 impulse, Vector3 real_pos)
	{
		m_pBody->applyImpulse(btVector3(impulse.x, impulse.y, impulse.z), btVector3(real_pos.x, real_pos.y, real_pos.z));
	}

	void RBody::SetSleepingThreshold(float linear, float angular)
	{
		m_pBody->setSleepingThresholds(btScalar(linear), btScalar(angular));
	}

	void RBody::SetActiveCollision(bool activeCol)
	{
		m_activeCollision = activeCol;
	}

	bool RBody::GetActiveCollision() const
	{
		return m_activeCollision;
	}

	void RBody::forceActivationState(int newState)
	{
		m_pBody->forceActivationState(newState);
	}

	void RBody::OnGUI()
	{
		Vector3 vel = RBody::GetLinearVelocity();
		m_velocity[0] = vel.x;
		m_velocity[1] = vel.y;
		m_velocity[2] = vel.z;

		GObject::OnGUI();
		ImGui::TextColored(ImVec4(0.2f, 1, 0.2f, 1), "RigidBody\n");
		if (ImGui::DragFloat3("Gravity",m_gravity,0.2f))
		{
			SetGravity(Vector3(m_gravity[0], m_gravity[1], m_gravity[2]));
		}
		if (ImGui::DragFloat3("Velocity", m_velocity,0.2f))
		{
			vel.x = m_velocity[0];
			vel.y = m_velocity[1];
			vel.z = m_velocity[2];
			RBody::SetLinearVelocity(vel);
		}
		if (ImGui::Combo("ActivationState", &style_idx, "ACTIVE_TAG\0ISLAND_SLEEPING\0WANTS_DEACTIVATION\0DISABLE_DEACTIVATION\0DISABLE_SIMULATION\0"))
		{
			switch (style_idx)
			{
			case 0: m_pBody->forceActivationState(1); break;
			case 1: m_pBody->forceActivationState(2); break;
			case 2: m_pBody->forceActivationState(3); break;
			case 3: m_pBody->forceActivationState(4); break;
			case 4: m_pBody->forceActivationState(5); break;
			}
		}
	}

	RBody::~RBody()
	{
		delete m_pMotionState;
		delete m_pBody;
	}
}